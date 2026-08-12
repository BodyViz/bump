#==============================================================================
#                                   Unit tests
#==============================================================================
# One executable per suite, named after its directory. Each is independently
# buildable, runnable, debuggable and installed.
#
# gtest_discover_tests still exposes every TEST_F individually on top of that,
# so `ctest -R` and `ctest -j` keep working at single-test granularity.

include(GoogleTest)

set(CMAKE_INSTALL_RPATH "${BUMP_RUNTIME_INSTALL_RPATH}")
set(CMAKE_FOLDER "bump/tests")

set(BUMP_TEST_SUITES
    bumpCryptographicHashTests
    bumpEnvironmentTests
    bumpFileInfoTests
    bumpFileSystemTests
    bumpNotificationTests
    bumpStringTests
    bumpTextFileReaderTests
    bumpUuidTests
)

# FileInfo and FileSystem assert platform-specific behaviour and each carry a
# partner translation unit, mirroring the library's own _win/_unix split. On
# Windows the _win variants deliberately expect bump::NotImplementedError from
# the stubbed permission APIs, so a green Windows run proves "the stubs still
# throw", not "permissions work".
if(WIN32)
    set(_bump_test_platform win)
else()
    set(_bump_test_platform unix)
endif()

# Sources are relative to each suite's own directory.
set(bumpCryptographicHashTests_SOURCES CryptographicHashTest.cpp)
set(bumpEnvironmentTests_SOURCES EnvironmentTest.cpp)
set(bumpFileInfoTests_SOURCES
    FileInfoTest.cpp
    FileInfoTest_${_bump_test_platform}.cpp
)
set(bumpFileSystemTests_SOURCES
    FileSystemTest.cpp
    FileSystemTest_${_bump_test_platform}.cpp
)
set(bumpNotificationTests_SOURCES NotificationTest.cpp)
set(bumpStringTests_SOURCES StringTest.cpp)
set(bumpTextFileReaderTests_SOURCES TextFileReaderTest.cpp)
set(bumpUuidTests_SOURCES UuidTest.cpp)

# The three suites whose fixtures create a "unittest" tree in the working
# directory, chdir into it, and delete it wholesale in TearDown. The other five
# never touch the filesystem.
set(BUMP_FILESYSTEM_SUITES
    bumpFileInfoTests
    bumpFileSystemTests
    bumpTextFileReaderTests
)

foreach(suite IN LISTS BUMP_TEST_SUITES)
    list(TRANSFORM ${suite}_SOURCES PREPEND "${suite}/"
         OUTPUT_VARIABLE _bump_suite_sources)

    add_executable(${suite} ${_bump_suite_sources})

    target_link_libraries(${suite} PRIVATE
        Bump::bump
        GTest::gtest
        GTest::gtest_main
    )

    # FileInfoTest.h and FileSystemTest.h are included as "FileInfoTest.h" from
    # their sibling partner translation units.
    target_include_directories(${suite} PRIVATE "${suite}")

    target_compile_options(${suite} PRIVATE
        "$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra>"
        "$<$<CXX_COMPILER_ID:AppleClang,Clang>:-Wshorten-64-to-32;-Wimplicit-int-conversion>"
        "$<$<CXX_COMPILER_ID:MSVC>:/W4;/utf-8;/permissive-;/EHsc;/bigobj>"
        "$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<BOOL:${BUMP_WIN32_USE_MP}>>:/MP>"
    )

    #--------------------------------------------------------------------------
    # CTest registration
    #--------------------------------------------------------------------------
    # A scratch directory per suite, which removes cross-suite collision
    # outright.

    set(_bump_suite_scratch "${CMAKE_CURRENT_BINARY_DIR}/test-scratch/${suite}")
    file(MAKE_DIRECTORY "${_bump_suite_scratch}")

    if("${suite}" IN_LIST BUMP_FILESYSTEM_SUITES)
        set(_bump_suite_properties PROPERTIES RESOURCE_LOCK "${suite}")
    else()
        set(_bump_suite_properties)
    endif()

    # PRE_TEST rather than the default POST_BUILD: POST_BUILD runs the binary at
    # build time to enumerate tests, which fails for a shared build before the
    # loader path is set and is wrong when cross-compiling x86_64 on arm64.
    gtest_discover_tests(${suite}
        DISCOVERY_MODE PRE_TEST
        WORKING_DIRECTORY "${_bump_suite_scratch}"
        XML_OUTPUT_DIR "${CMAKE_BINARY_DIR}/test-results"
        ${_bump_suite_properties}
    )
endforeach()

# TextFileReaderTest deliberately passes 2.999 to int parameters to verify that
# a float argument truncates. The narrowing is the thing under test, so the
# diagnostic is disabled rather than the tests rewritten. MSVC's equivalent is
# C4244, which /W4 reports at the same five call sites.
#
# Per-suite executables narrow this to the one suite that needs it -- a single
# binary had to set it for every test translation unit -- but it is still target
# scope, so it covers all tests in the file and not just those five lines.
target_compile_options(bumpTextFileReaderTests PRIVATE
    "$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wno-literal-conversion>"
    "$<$<CXX_COMPILER_ID:MSVC>:/wd4244>"
)

install(TARGETS ${BUMP_TEST_SUITES}
    RUNTIME DESTINATION "${BUMP_RUNTIME_INSTALL_DIR}/tests"
)

# Windows has no RPATH, so the DLLs have to sit beside the executables. The union
# over the whole group, not one representative: a suite that grows a dependency
# the others lack is then still covered.
if(WIN32 AND BUILD_SHARED_LIBS)
    set(_bump_suite_dlls "")
    foreach(suite IN LISTS BUMP_TEST_SUITES)
        list(APPEND _bump_suite_dlls "$<TARGET_RUNTIME_DLLS:${suite}>")
    endforeach()

    install(FILES "$<REMOVE_DUPLICATES:${_bump_suite_dlls}>"
        DESTINATION "${BUMP_RUNTIME_INSTALL_DIR}/tests")
endif()

#==============================================================================
#                          Exported symbol policy
#==============================================================================
# Apple only: MSVC exports through __declspec, where CXX_VISIBILITY_PRESET does
# nothing, so there is no policy to assert. The check reads Mach-O symbol
# classes, which is also why it is not written against ELF here.

if(APPLE AND BUMP_HIDE_PRIVATE_SYMBOLS)
    get_target_property(_bump_target_type bump TYPE)
    add_test(NAME symbol-visibility
        COMMAND "${CMAKE_COMMAND}"
                "-DLIBRARY=$<TARGET_FILE:bump>"
                "-DTYPE=${_bump_target_type}"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/CheckSymbolVisibility.cmake"
    )
    unset(_bump_target_type)
endif()

#==============================================================================
#                              Installed package
#==============================================================================
# package-test/ consumes an *installed* Bump through find_package, so it cannot
# be an add_subdirectory of the build that produces that install -- but it can
# be driven. A fixture stages an install inside the build tree, then ctest
# --build-and-test configures, builds and runs package-test against it.
#
# Nothing but the stage prefix is handed to the consumer. Every usage
# requirement, including where Boost lives, has to arrive through the package.

set(BUMP_PACKAGE_STAGE "${PROJECT_BINARY_DIR}/package-stage")

# Empty when the build expressed no linkage preference, which is a value the
# generated config has to be able to represent. Derived from the same input the
# root CMakeLists reads rather than from what it recorded, so the test still
# checks the mapping instead of restating it.
if(NOT DEFINED Boost_USE_STATIC_LIBS)
    set(_bump_expect_boost_static "")
elseif(Boost_USE_STATIC_LIBS)
    set(_bump_expect_boost_static ON)
else()
    set(_bump_expect_boost_static OFF)
endif()

add_test(NAME package-config-boost-linkage
    COMMAND "${CMAKE_COMMAND}"
            "-DCONFIG_FILE=${PROJECT_BINARY_DIR}/BumpConfig.cmake"
            "-DEXPECTED=${_bump_expect_boost_static}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/CheckPackageConfig.cmake"
)

add_test(NAME package-install
    COMMAND "${CMAKE_COMMAND}" --install "${PROJECT_BINARY_DIR}"
            --prefix "${BUMP_PACKAGE_STAGE}" --config $<CONFIG>
)

# The consumer has to be generated the same way bump was, or an x64 package gets
# consumed by a Win32 build and the failure reads as a link error.
set(_bump_consume_generator --build-generator "${CMAKE_GENERATOR}")
if(CMAKE_GENERATOR_PLATFORM)
    list(APPEND _bump_consume_generator
         --build-generator-platform "${CMAKE_GENERATOR_PLATFORM}")
endif()
if(CMAKE_GENERATOR_TOOLSET)
    list(APPEND _bump_consume_generator
         --build-generator-toolset "${CMAKE_GENERATOR_TOOLSET}")
endif()

# The stage prefix is the only thing about *bump* the consumer is told. The
# architecture and deployment target are not usage requirements a package should
# carry -- a consumer picks its own ABI and has to match its dependencies -- so
# the test states them exactly as a real consumer would, and only when this build
# stated them itself.
set(_bump_abi_options "")
foreach(var IN ITEMS CMAKE_OSX_ARCHITECTURES CMAKE_OSX_DEPLOYMENT_TARGET)
    if(${var})
        list(APPEND _bump_abi_options "-D${var}=${${var}}")
    endif()
endforeach()
set(_bump_consume_options
    "-DCMAKE_PREFIX_PATH=${BUMP_PACKAGE_STAGE}" ${_bump_abi_options})

# --build-noclean because the clean step runs before the solution exists, which
# under the Visual Studio generator reports MSB1009 on a first configure.
add_test(NAME package-consume
    COMMAND "${CMAKE_CTEST_COMMAND}"
            --build-and-test "${CMAKE_CURRENT_SOURCE_DIR}/package-test"
                             "${CMAKE_CURRENT_BINARY_DIR}/package-consume/$<CONFIG>"
            ${_bump_consume_generator}
            --build-config $<CONFIG>
            --build-noclean
            --build-options ${_bump_consume_options}
            --test-command "${CMAKE_CTEST_COMMAND}" -C $<CONFIG> --output-on-failure
)

# A multi-config consumer resolves the imported target for every configuration
# it offers at generate time, not just the one it builds, so a package that ships
# fewer configurations than the consumer offers has to resolve through
# MAP_IMPORTED_CONFIG_* or the generate step fails outright.
#
# Its own single-config prefix rather than the shared stage, which accumulates
# whatever configurations have been run and so would make this order-dependent.
#
# It builds the configuration the package does ship. Building one it does not is
# not a thing any mapping can rescue -- there is no compatible artifact to link,
# and under MSVC the linker says so with an _ITERATOR_DEBUG_LEVEL mismatch. The
# mapping itself is asserted by package-test's per-configuration checks, which
# read generate-time resolution and so cover configurations nothing builds.
set(BUMP_FALLBACK_STAGE "${PROJECT_BINARY_DIR}/package-stage-single/$<CONFIG>")

add_test(NAME package-install-single
    COMMAND "${CMAKE_COMMAND}" --install "${PROJECT_BINARY_DIR}"
            --prefix "${BUMP_FALLBACK_STAGE}" --config $<CONFIG>
)

# Every standard configuration, stated rather than left to the generator: Ninja
# Multi-Config offers Debug, Release and RelWithDebInfo while Visual Studio adds
# MinSizeRel, so a mapping that fails only for MinSizeRel is invisible here
# otherwise. $<SEMICOLON> keeps the list one argument through add_test.
add_test(NAME package-consume-fallback
    COMMAND "${CMAKE_CTEST_COMMAND}"
            --build-and-test "${CMAKE_CURRENT_SOURCE_DIR}/package-test"
                             "${CMAKE_CURRENT_BINARY_DIR}/package-fallback/$<CONFIG>"
            ${_bump_consume_generator}
            --build-config $<CONFIG>
            --build-noclean
            --build-options "-DCMAKE_PREFIX_PATH=${BUMP_FALLBACK_STAGE}"
                            "-DCMAKE_CONFIGURATION_TYPES=Debug$<SEMICOLON>Release$<SEMICOLON>RelWithDebInfo$<SEMICOLON>MinSizeRel"
                            ${_bump_abi_options}
            --test-command "${CMAKE_CTEST_COMMAND}" -C $<CONFIG> --output-on-failure
)

# FIXTURES_REQUIRED pulls the matching install in automatically, so `ctest -R
# package-consume` stages its own prefix. RESOURCE_LOCK keeps two configurations
# from installing into one prefix at once under ctest -j; package-consume's is
# shared deliberately, since Debug and Release accumulating there is part of what
# package-test asserts.
set_tests_properties(package-install PROPERTIES
    FIXTURES_SETUP BumpPackage
    RESOURCE_LOCK BumpPackageStage
)
set_tests_properties(package-consume PROPERTIES
    FIXTURES_REQUIRED BumpPackage
    RESOURCE_LOCK BumpPackageStage
)
set_tests_properties(package-install-single PROPERTIES
    FIXTURES_SETUP BumpPackageSingle
)
set_tests_properties(package-consume-fallback PROPERTIES
    FIXTURES_REQUIRED BumpPackageSingle
)

# An installed example, launched from somewhere other than its own directory.
# The only thing that proves INSTALL_RPATH resolves: a shared build aborts here
# with "no LC_RPATH's found" if it is wrong.
# A static build still exercises the install and the launch.
if(BUMP_BUILD_EXAMPLES)
    add_test(NAME installed-example-runs
        COMMAND "${BUMP_PACKAGE_STAGE}/${BUMP_RUNTIME_INSTALL_DIR}/examples/$<TARGET_FILE_NAME:bumpUuids>"
    )
    set_tests_properties(installed-example-runs PROPERTIES
        FIXTURES_REQUIRED BumpPackage
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    )
endif()
