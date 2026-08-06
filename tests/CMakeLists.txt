#==============================================================================
#                                   Unit tests
#==============================================================================
# One executable for all suites.
#
# gtest_discover_tests exposes every TEST_F individually, so `ctest -R`
# and `ctest -j` work at test granularity and the aggregate target is redundant
# by construction. main() comes from GTest::gtest_main.

include(GoogleTest)

set(BUMP_TEST_SOURCES
    bumpCryptographicHashTests/CryptographicHashTest.cpp
    bumpEnvironmentTests/EnvironmentTest.cpp
    bumpFileInfoTests/FileInfoTest.cpp
    bumpFileSystemTests/FileSystemTest.cpp
    bumpNotificationTests/NotificationTest.cpp
    bumpStringTests/StringTest.cpp
    bumpTextFileReaderTests/TextFileReaderTest.cpp
    bumpUuidTests/UuidTest.cpp
)

# FileInfo and FileSystem assert platform-specific behaviour. On Windows the
# _win variants deliberately expect bump::NotImplementedError from the stubbed
# permission APIs, so a green Windows run proves "the stubs still throw", not
# "permissions work".
if(WIN32)
    list(APPEND BUMP_TEST_SOURCES
        bumpFileInfoTests/FileInfoTest_win.cpp
        bumpFileSystemTests/FileSystemTest_win.cpp
    )
else()
    list(APPEND BUMP_TEST_SOURCES
        bumpFileInfoTests/FileInfoTest_unix.cpp
        bumpFileSystemTests/FileSystemTest_unix.cpp
    )
endif()

add_executable(bumpTests ${BUMP_TEST_SOURCES})

target_link_libraries(bumpTests PRIVATE
    Bump::bump
    GTest::gtest
    GTest::gtest_main
)

# FileInfoTest.h and FileSystemTest.h are included as "FileInfoTest.h" from
# their sibling _unix/_win translation units.
target_include_directories(bumpTests PRIVATE
    bumpFileInfoTests
    bumpFileSystemTests
)

set_target_properties(bumpTests PROPERTIES FOLDER "bump/tests")

target_compile_options(bumpTests PRIVATE
    "$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra>"
    "$<$<CXX_COMPILER_ID:MSVC>:/W4;/utf-8;/permissive-;/EHsc;/bigobj>"
    "$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<BOOL:${BUMP_WIN32_USE_MP}>>:/MP>"

    # TextFileReaderTest deliberately passes 2.999 to int parameters to verify
    # that a float argument truncates. The narrowing is the thing under test, so
    # the diagnostic is disabled rather than the tests rewritten. MSVC's
    # equivalent is C4244, which /W4 reports for the same five call sites.
    "$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wno-literal-conversion>"
    "$<$<CXX_COMPILER_ID:MSVC>:/wd4244>"
)

# Put bump.dll beside the test executable on Windows so it can be launched from
# the build tree or a debugger. Empty on non-DLL platforms, so no guard needed.
add_custom_command(TARGET bumpTests POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy -t
            "$<TARGET_FILE_DIR:bumpTests>" "$<TARGET_RUNTIME_DLLS:bumpTests>"
    COMMAND_EXPAND_LISTS
)

#------------------------------------------------------------------------------
# CTest registration
#------------------------------------------------------------------------------
# Two discovery calls, partitioned by whether the test touches the shared
# "unittest" directory tree in the working directory. Three suites do --
# FileSystemTest, FileInfoTest and TextFileReaderTest -- and each one's SetUp
# creates that tree while its TearDown removes it wholesale, so any two of them
# running concurrently will delete files out from under each other.
#
# RESOURCE_LOCK serialises exactly those three; every other suite is filesystem
# free (grep for '"unittest' to confirm) and stays fully parallel.
#
# Keep this list in step with reality: omitting a suite that touches the tree
# produces intermittent failures under `ctest -j` that pass when run serially.

set(BUMP_TEST_SCRATCH_DIR "${CMAKE_CURRENT_BINARY_DIR}/test-scratch")
file(MAKE_DIRECTORY "${BUMP_TEST_SCRATCH_DIR}")

# PRE_TEST rather than the default POST_BUILD: POST_BUILD runs the binary at
# build time to enumerate tests, which fails for a shared build before the
# loader path is set and is wrong when cross-compiling x86_64 on arm64.
set(BUMP_DISCOVERY_ARGS
    DISCOVERY_MODE PRE_TEST
    WORKING_DIRECTORY "${BUMP_TEST_SCRATCH_DIR}"
    XML_OUTPUT_DIR "${CMAKE_BINARY_DIR}/test-results"
)

# Negative gtest filter syntax is -a:b, a single leading dash for the whole
# exclusion list. Getting it wrong silently duplicates or drops tests, so the
# check is that `ctest -N` reports exactly 215: 88 locked plus 127 parallel. The
# FileInfo/FileSystem _unix and _win variants are mutually exclusive and happen
# to hold 29 tests each, so both platforms total the same.
set(BUMP_FS_SUITES "FileSystemTest.*:FileInfoTest.*:TextFileReaderTest.*")

gtest_discover_tests(bumpTests ${BUMP_DISCOVERY_ARGS}
    TEST_FILTER "${BUMP_FS_SUITES}"
    PROPERTIES RESOURCE_LOCK bump_filesystem
)

gtest_discover_tests(bumpTests ${BUMP_DISCOVERY_ARGS}
    TEST_FILTER "-${BUMP_FS_SUITES}"
)

install(TARGETS bumpTests
    RUNTIME DESTINATION "${CMAKE_INSTALL_DATADIR}/bump/tests"
)
