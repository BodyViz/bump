#==============================================================================
#                                   Unit tests
#==============================================================================
# One executable per suite, named after its directory. Each is independently
# buildable, runnable, debuggable and installed.
#
# gtest_discover_tests still exposes every TEST_F individually on top of that, so
# `ctest -R` and `ctest -j` keep working at single-test granularity.

include(GoogleTest)

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

    # INSTALL_RPATH so the installed copy can still find a shared bump; see the
    # Installed runtime paths section in the top-level CMakeLists.
    set_target_properties(${suite} PROPERTIES
        FOLDER "bump/tests"
        INSTALL_RPATH "${BUMP_RUNTIME_INSTALL_RPATH}"
    )

    target_compile_options(${suite} PRIVATE
        "$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra>"
        "$<$<CXX_COMPILER_ID:MSVC>:/W4;/utf-8;/permissive-;/EHsc;/bigobj>"
        "$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<BOOL:${BUMP_WIN32_USE_MP}>>:/MP>"
    )

    # Put bump.dll beside the executable on Windows so a suite can be launched
    # straight from the build tree or a debugger. Expands to nothing on non-DLL
    # platforms, so this needs no if(WIN32) guard.
    add_custom_command(TARGET ${suite} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy -t
                "$<TARGET_FILE_DIR:${suite}>" "$<TARGET_RUNTIME_DLLS:${suite}>"
        COMMAND_EXPAND_LISTS
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

# TextFileReaderTest deliberately passes 2.999 to int parameters to verify that a
# float argument truncates. The narrowing is the thing under test, so the
# diagnostic is disabled rather than the tests rewritten. MSVC's equivalent is
# C4244, which /W4 reports for the same five call sites.
#
# Per-suite executables let this apply to the one suite that needs it; with a
# single binary it had to be set for every test translation unit.
target_compile_options(bumpTextFileReaderTests PRIVATE
    "$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wno-literal-conversion>"
    "$<$<CXX_COMPILER_ID:MSVC>:/wd4244>"
)

# CryptographicHashTest calls setData(data, strlen(data)) eight times, and
# strlen returns size_t while the parameter is int. Same root cause as the
# String.cpp sites and suppressed for the same reason; see the note in
# src/CMakeLists.txt. Widening CryptographicHash::setData removes this.
target_compile_options(bumpCryptographicHashTests PRIVATE
    "$<$<CXX_COMPILER_ID:MSVC>:/wd4267>"
)

install(TARGETS ${BUMP_TEST_SUITES}
    RUNTIME DESTINATION "${BUMP_RUNTIME_INSTALL_DIR}/tests"
)

# package-test/ is deliberately not added here. It is a standalone project that
# consumes an installed Bump through find_package, so it cannot be configured
# from inside the build that produces that install. See its CMakeLists.txt.
