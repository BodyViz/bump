#==============================================================================
#                          Bump package test
#==============================================================================
# A standalone project, deliberately NOT added by tests/CMakeLists.txt: it tests
# an *installed* Bump, which by definition does not exist while bump is being
# built. Point it at a prefix and nothing else:
#
#     cmake -S tests/package-test -B /tmp/pkg -DCMAKE_PREFIX_PATH=<prefix>
#     cmake --build /tmp/pkg && /tmp/pkg/bump_smoke
#
# The absence of things is the point. No include directories, no -D, no
# CMAKE_CXX_STANDARD, no Boost hint. Every one of those has to arrive through
# the imported target, or the package is not self-describing and the consumer is
# back to knowing bump's internals.

cmake_minimum_required(VERSION 3.30)

project(BumpPackageTest LANGUAGES CXX)

find_package(Bump 2 REQUIRED)

add_executable(bump_smoke main.cpp)
target_link_libraries(bump_smoke PRIVATE Bump::bump)

# Windows has no RPATH. A shared Bump installs bump.dll to <prefix>/bin and
# bump.lib to <prefix>/lib, which is the right layout, but an executable only
# finds a DLL in its own directory, the system directories, or PATH -- so linking
# successfully and *running* are two different things there. Without this the
# smoke test built fine against the shared package and then died at startup
# unable to locate bump.dll, which is what a real consumer would hit too.
#
# $<TARGET_RUNTIME_DLLS> resolves through the imported target's
# IMPORTED_LOCATION, so this is also a check that install(TARGETS) recorded the
# DLL's location and not just the import library. The genex is empty on non-DLL
# platforms, so no if(WIN32) guard is needed -- macOS and Linux resolve bump
# through the RPATH the linker already wrote.
add_custom_command(TARGET bump_smoke POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy -t
            "$<TARGET_FILE_DIR:bump_smoke>" "$<TARGET_RUNTIME_DLLS:bump_smoke>"
    COMMAND_EXPAND_LISTS
)

# Reports what the imported target actually carried, so a failure says which
# usage requirement went missing rather than just "it did not link".
#
# IMPORTED_CONFIGURATIONS rather than LOCATION: LOCATION on a multi-config
# imported target reports whichever configuration happens to come first, which
# reads as "linking Debug" even in a Release build. The configuration list is
# both accurate and the more useful fact -- it is the proof that Debug and
# Release accumulated in one prefix instead of clobbering each other.
get_target_property(_bump_type Bump::bump TYPE)
get_target_property(_bump_configs Bump::bump IMPORTED_CONFIGURATIONS)
get_target_property(_bump_includes Bump::bump INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(_bump_defines Bump::bump INTERFACE_COMPILE_DEFINITIONS)
get_target_property(_bump_features Bump::bump INTERFACE_COMPILE_FEATURES)

message(STATUS "")
message(STATUS "Bump package smoke test")
message(STATUS "  Bump_DIR         ${Bump_DIR}")
message(STATUS "  Bump_VERSION     ${Bump_VERSION}")
message(STATUS "  Target type      ${_bump_type}")
message(STATUS "  Configurations   ${_bump_configs}")
message(STATUS "  Includes         ${_bump_includes}")
message(STATUS "  Definitions      ${_bump_defines}")
message(STATUS "  Features         ${_bump_features}")
message(STATUS "  Boost_DIR        ${Boost_DIR}")
message(STATUS "")
