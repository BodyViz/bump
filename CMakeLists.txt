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

# Linkage is a BUMP_* option so it groups with the rest in a cache editor, and so
# it always exists as a typed BOOL rather than only when someone passes -D for it.
# Past that point BUMP_BUILD_SHARED_LIBS is authoritative, and the
# resulting type is handed to add_library() explicitly rather than left implicit.
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
# Guarded so that add_subdirectory()/FetchContent consumers keep control of
# their own build configuration.

if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # Boost's imported targets provide no Debug mapping for MinSizeRel or
    # RelWithDebInfo and fall back to the release archives. Harmless on macOS,
    # potentially heap-corrupting under MSVC, so restrict the set.
    if(CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_CONFIGURATION_TYPES Debug Release)
        # Ninja Multi-Config only; Xcode and Visual Studio reject this variable.
        if(CMAKE_GENERATOR STREQUAL "Ninja Multi-Config")
            set(CMAKE_DEFAULT_BUILD_TYPE Debug)
        endif()
    elseif(NOT CMAKE_BUILD_TYPE)
        # Single-config generators default to an unoptimized no-config build,
        # which the old `configure` script papered over with -DCMAKE_BUILD_TYPE.
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

find_package(Boost 1.91 REQUIRED CONFIG COMPONENTS
    chrono
    date_time
    filesystem
    regex
    thread
    timer
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
#                                  Subdirectories
#==============================================================================

add_subdirectory(src)

if(BUMP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# TODO(phase 6): if(BUMP_BUILD_TESTS) add_subdirectory(tests) endif()
# TODO(phase 10): if(BUMP_BUILD_DOCS) add_subdirectory(doc) endif()

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
    message(STATUS "  Install prefix     ${CMAKE_INSTALL_PREFIX}")
    message(STATUS "")
endif()
