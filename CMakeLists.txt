cmake_minimum_required(VERSION 3.30)

project(Bump
    VERSION 2.0.0
    DESCRIPTION "C++ wrapper library for modern Boost functionality"
    HOMEPAGE_URL "https://github.com/BodyViz/bump"
    LANGUAGES CXX
)
set(BUMP_SO_VERSION ${PROJECT_VERSION_MAJOR})

include(CMakeDependentOption)
include(GNUInstallDirs)

#==============================================================================
#                                   Guardrails
#==============================================================================

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
set(CMAKE_LINK_LIBRARIES_ONLY_TARGETS ON)

#==============================================================================
#                                    Options
#==============================================================================

if(DEFINED BUILD_SHARED_LIBS)
    set(_bump_shared_default ${BUILD_SHARED_LIBS})
else()
    set(_bump_shared_default OFF)
endif()
option(BUMP_BUILD_SHARED_LIBS
    "Build Bump as a shared library instead of static" ${_bump_shared_default})
unset(_bump_shared_default)

if(BUMP_BUILD_SHARED_LIBS)
    set(BUMP_LIBRARY_TYPE SHARED)
else()
    set(BUMP_LIBRARY_TYPE STATIC)
endif()

option(BUMP_BUILD_EXAMPLES "Build the Bump example applications" ON)
option(BUMP_BUILD_TESTS "Build the Bump unit tests" OFF)
option(BUMP_BUILD_DOCS "Build the Bump reference documentation with Doxygen" OFF)
option(BUMP_HIDE_PRIVATE_SYMBOLS
    "Export only BUMP_EXPORT-annotated symbols from the shared library" ON)

# Platform-conditional options. cmake_dependent_option keeps them out of the
# cache entirely off-platform rather than wrapping them in if().
cmake_dependent_option(BUMP_BUILD_FRAMEWORK
    "Build Bump as a macOS framework instead of a plain library" OFF "APPLE" OFF)
cmake_dependent_option(BUMP_WIN32_USE_MP
    "Compile with /MP for parallel builds" ON "MSVC" OFF)

# A framework is a shared bundle.
if(BUMP_BUILD_FRAMEWORK AND NOT BUMP_BUILD_SHARED_LIBS)
    message(FATAL_ERROR
        "BUMP_BUILD_FRAMEWORK requires a shared build. Enable "
        "BUMP_BUILD_SHARED_LIBS as well, or turn BUMP_BUILD_FRAMEWORK off.")
endif()

#==============================================================================
#                            Standalone-only settings
#==============================================================================

if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # Boost's imported targets provide no Debug mapping for MinSizeRel or
    # RelWithDebInfo and fall back to the release archives. Harmless on macOS,
    # potentially heap-corrupting under MSVC, so restrict the set.
    if(CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_CONFIGURATION_TYPES Debug Release)
        if(CMAKE_GENERATOR STREQUAL "Ninja Multi-Config")
            set(CMAKE_DEFAULT_BUILD_TYPE Debug)
        endif()
    elseif(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release)
    endif()

    # Distinguishes Debug from Release artifacts so both can be installed into a
    # single prefix. Frameworks ignore these and use
    # FRAMEWORK_MULTI_CONFIG_POSTFIX_<CONFIG> instead.
    set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Debug library name postfix")
    set(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "RelWithDebInfo postfix")
    set(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "MinSizeRel postfix")

    # Per-config subdirectories are left at CMake's defaults.
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
endif()

#==============================================================================
#                                  Dependencies
#==============================================================================

# Stated once and reused by cmake/BumpConfig.cmake.in, so the package's
# find_dependency() call cannot drift from what bump was actually built against.
set(BUMP_BOOST_VERSION 1.91)
set(BUMP_BOOST_COMPONENTS chrono date_time filesystem regex thread timer)

find_package(Boost ${BUMP_BOOST_VERSION} REQUIRED CONFIG
    COMPONENTS ${BUMP_BOOST_COMPONENTS}
)

if(BUMP_BUILD_TESTS)
    find_package(GTest REQUIRED CONFIG)
endif()

if(BUMP_BUILD_DOCS)
    find_package(Doxygen)
    if(NOT Doxygen_FOUND)
        message(WARNING "BUMP_BUILD_DOCS is ON but Doxygen was not found; "
                        "documentation will not be built.")
    endif()
endif()

#==============================================================================
#                            Installed runtime paths
#==============================================================================
# The examples and the test binaries install to share/bump/<group> while the
# library lands in lib/ -- or Frameworks/ for a framework build -- so once
# installed they can only find a shared bump through a relative RPATH. Without
# one, an installed example aborts at startup with "no LC_RPATH's found", which
# the build tree never reveals because CMake gives it an absolute RPATH there
# and strips it on install.
#
# Both groups sit exactly one level below share/bump, so a single value serves
# both. Derived with file(RELATIVE_PATH) from the real destinations rather than
# spelled out as ../../.., so it stays correct when CMAKE_INSTALL_LIBDIR is
# lib64 or the framework flavour redirects the library elsewhere.

set(BUMP_RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/bump")

if(BUMP_BUILD_FRAMEWORK)
    set(_bump_library_dir "Frameworks")
else()
    set(_bump_library_dir "${CMAKE_INSTALL_LIBDIR}")
endif()

# "group" stands in for examples or tests; only the depth matters here.
file(RELATIVE_PATH _bump_rpath
    "${CMAKE_INSTALL_PREFIX}/${BUMP_RUNTIME_INSTALL_DIR}/group"
    "${CMAKE_INSTALL_PREFIX}/${_bump_library_dir}"
)

# @loader_path on Apple platforms, $ORIGIN for ELF. Windows resolves DLLs by
# directory and ignores RPATH entirely, so this is simply unused there.
if(APPLE)
    set(BUMP_RUNTIME_INSTALL_RPATH "@loader_path/${_bump_rpath}")
else()
    set(BUMP_RUNTIME_INSTALL_RPATH "$ORIGIN/${_bump_rpath}")
endif()

unset(_bump_library_dir)
unset(_bump_rpath)

#==============================================================================
#                                  Subdirectories
#==============================================================================

# Where src/ writes the two generated public headers, Version.h and Export.h.
# Stated here rather than in src/ because doc/ documents them too, and a
# directory-scoped set() in one subdirectory is not visible in a sibling.
set(BUMP_GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include")

add_subdirectory(src)

if(BUMP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUMP_BUILD_TESTS)
    # Makes `cmake --build . --target test` useful without remembering the flag.
    set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUMP_BUILD_DOCS AND Doxygen_FOUND)
    add_subdirectory(doc)
endif()

#==============================================================================
#                              Install and export
#==============================================================================
# Produces the BumpConfig package.
#
# The install(TARGETS ... EXPORT BumpTargets) that feeds this lives in
# src/CMakeLists.txt, next to the target it describes.

include(CMakePackageConfigHelpers)

set(BUMP_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/Bump")

#------------------------------------------------------------------------------
# Windows counterpart to BUMP_RUNTIME_INSTALL_RPATH
#------------------------------------------------------------------------------
# Windows has no RPATH: an executable finds a DLL in its own directory, the
# system directories or PATH, and nowhere else. This installs DLLs next to the
# examples and tests so they don't fail at runtime.
#
# install(FILES $<TARGET_FILE:bump>) rather than install(TARGETS bump RUNTIME):
# the latter would also install the unmentioned artifact kinds to their default
# destinations, re-installing the import library. $<TARGET_FILE> on a Windows
# shared library is the DLL; the import library is $<TARGET_LINKER_FILE>.
if(WIN32 AND BUMP_BUILD_SHARED_LIBS)
    if(BUMP_BUILD_EXAMPLES)
        install(FILES "$<TARGET_FILE:bump>"
            DESTINATION "${BUMP_RUNTIME_INSTALL_DIR}/examples")
    endif()
    if(BUMP_BUILD_TESTS)
        install(FILES "$<TARGET_FILE:bump>"
            DESTINATION "${BUMP_RUNTIME_INSTALL_DIR}/tests")
    endif()
endif()

# BumpTargets.cmake globs for its per-configuration BumpTargets-<config>.cmake
# siblings, so installing Debug and then Release into one prefix accumulates
# rather than clobbers. That is what makes both libbump.a and libbumpd.a usable
# from a single find_package().
install(EXPORT BumpTargets
    FILE BumpTargets.cmake
    NAMESPACE Bump::
    DESTINATION "${BUMP_INSTALL_CMAKEDIR}"
)

# Normalised to a literal ON/OFF so the generated config can never contain a
# bare `set(Boost_USE_STATIC_LIBS )`, which would read as defined-but-false and
# quietly flip a consumer to shared Boost.
set(BUMP_BOOST_USE_STATIC_LIBS OFF)
if(Boost_USE_STATIC_LIBS)
    set(BUMP_BOOST_USE_STATIC_LIBS ON)
endif()
list(JOIN BUMP_BOOST_COMPONENTS " " BUMP_BOOST_COMPONENTS_SPACED)

configure_package_config_file(cmake/BumpConfig.cmake.in
    "${PROJECT_BINARY_DIR}/BumpConfig.cmake"
    INSTALL_DESTINATION "${BUMP_INSTALL_CMAKEDIR}"
)

# SameMajorVersion: find_package(Bump 2) keeps working across future 2.x
# releases.
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/BumpConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${PROJECT_BINARY_DIR}/BumpConfig.cmake"
    "${PROJECT_BINARY_DIR}/BumpConfigVersion.cmake"
    DESTINATION "${BUMP_INSTALL_CMAKEDIR}"
)

#==============================================================================
#                              Configuration summary
#==============================================================================

if(PROJECT_IS_TOP_LEVEL)
    message(STATUS "")
    message(STATUS "Bump ${PROJECT_VERSION} (SO version ${BUMP_SO_VERSION})")
    message(STATUS "  Boost              ${Boost_VERSION} -> ${Boost_DIR}")
    message(STATUS "  Boost static libs  ${Boost_USE_STATIC_LIBS}")
    if(CMAKE_CONFIGURATION_TYPES)
        message(STATUS "  Configurations     ${CMAKE_CONFIGURATION_TYPES}")
    else()
        message(STATUS "  Build type         ${CMAKE_BUILD_TYPE}")
    endif()
    message(STATUS "  Library type       ${BUMP_LIBRARY_TYPE}")
    if(APPLE)
        message(STATUS "  Framework          ${BUMP_BUILD_FRAMEWORK}")
        message(STATUS "  Architectures      ${CMAKE_OSX_ARCHITECTURES}")
        message(STATUS "  Deployment target  ${CMAKE_OSX_DEPLOYMENT_TARGET}")
    endif()
    message(STATUS "  Hide private syms  ${BUMP_HIDE_PRIVATE_SYMBOLS}")
    message(STATUS "  Examples / tests   ${BUMP_BUILD_EXAMPLES} / ${BUMP_BUILD_TESTS}")
    if(BUMP_BUILD_DOCS AND Doxygen_FOUND)
        message(STATUS "  Documentation      Doxygen ${DOXYGEN_VERSION}")
    else()
        message(STATUS "  Documentation      ${BUMP_BUILD_DOCS}")
    endif()
    message(STATUS "  Install prefix     ${CMAKE_INSTALL_PREFIX}")
    message(STATUS "")
endif()
