include(GenerateExportHeader)

#==============================================================================
#                          Vendored third-party: smallsha1
#==============================================================================
# Kept as a separate object library so third-party code never inherits bump's
# warning policy and never needs patching. It has a known -Wignored-qualifiers
# that is not ours to fix.

add_library(bump_smallsha1 OBJECT smallsha1/sha1.cpp)

# Both smallsha1/sha1.cpp and bump/CryptographicHash.cpp write
# #include <smallsha1/sha1.h>, so the directory prefix resolves against src/.
target_include_directories(bump_smallsha1 PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_compile_features(bump_smallsha1 PRIVATE cxx_std_20)

set_target_properties(bump_smallsha1 PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    COMPILE_WARNING_AS_ERROR OFF
    FOLDER "bump/third-party"
)

#==============================================================================
#                                   Sources
#==============================================================================

set(BUMP_SOURCES
    bump/AutoTimer.cpp
    bump/CryptographicHash.cpp
    bump/Environment.cpp
    bump/Exception.cpp
    bump/FileInfo.cpp
    bump/FileSystem.cpp
    bump/FileSystemError.cpp
    bump/InvalidArgumentError.cpp
    bump/Log.cpp
    bump/NotImplementedError.cpp
    bump/NotificationCenter.cpp
    bump/NotificationError.cpp
    bump/OutOfRangeError.cpp
    bump/String.cpp
    bump/StringSearchError.cpp
    bump/TextFileReader.cpp
    bump/Timeline.cpp
    bump/Timer.cpp
    bump/TypeCastError.cpp
    bump/Uuid.cpp
    bump/Version.cpp
)

# Environment, FileInfo and FileSystem each have a platform-specific partner.
if(WIN32)
    list(APPEND BUMP_SOURCES
        bump/Environment_win.cpp
        bump/FileInfo_win.cpp
        bump/FileSystem_win.cpp
    )
else()
    list(APPEND BUMP_SOURCES
        bump/Environment_unix.cpp
        bump/FileInfo_unix.cpp
        bump/FileSystem_unix.cpp
    )
endif()

set(BUMP_PUBLIC_HEADERS
    "${PROJECT_SOURCE_DIR}/include/bump/AutoTimer.h"
    "${PROJECT_SOURCE_DIR}/include/bump/CryptographicHash.h"
    "${PROJECT_SOURCE_DIR}/include/bump/Environment.h"
    "${PROJECT_SOURCE_DIR}/include/bump/Exception.h"
    "${PROJECT_SOURCE_DIR}/include/bump/FileInfo.h"
    "${PROJECT_SOURCE_DIR}/include/bump/FileSystem.h"
    "${PROJECT_SOURCE_DIR}/include/bump/FileSystemError.h"
    "${PROJECT_SOURCE_DIR}/include/bump/InvalidArgumentError.h"
    "${PROJECT_SOURCE_DIR}/include/bump/Log.h"
    "${PROJECT_SOURCE_DIR}/include/bump/NotImplementedError.h"
    "${PROJECT_SOURCE_DIR}/include/bump/NotificationCenter.h"
    "${PROJECT_SOURCE_DIR}/include/bump/NotificationCenter_impl.h"
    "${PROJECT_SOURCE_DIR}/include/bump/NotificationError.h"
    "${PROJECT_SOURCE_DIR}/include/bump/OutOfRangeError.h"
    "${PROJECT_SOURCE_DIR}/include/bump/String.h"
    "${PROJECT_SOURCE_DIR}/include/bump/StringSearchError.h"
    "${PROJECT_SOURCE_DIR}/include/bump/TextFileReader.h"
    "${PROJECT_SOURCE_DIR}/include/bump/Timeline.h"
    "${PROJECT_SOURCE_DIR}/include/bump/Timer.h"
    "${PROJECT_SOURCE_DIR}/include/bump/TypeCastError.h"
    "${PROJECT_SOURCE_DIR}/include/bump/Uuid.h"
    "${PROJECT_SOURCE_DIR}/include/bump/bump.h"
)

#==============================================================================
#                                 The bump target
#==============================================================================
# Type comes from BUMP_BUILD_SHARED_LIBS via BUMP_LIBRARY_TYPE. Only one flavour
# is built per configure; each installs into its own prefix.

add_library(bump ${BUMP_LIBRARY_TYPE} ${BUMP_SOURCES} $<TARGET_OBJECTS:bump_smallsha1>)
add_library(Bump::bump ALIAS bump)

# Exported as INTERFACE_COMPILE_FEATURES, so consumers are raised to C++20
# automatically rather than having to set CMAKE_CXX_STANDARD themselves.
target_compile_features(bump PUBLIC cxx_std_20)

#------------------------------------------------------------------------------
# Generated headers
#------------------------------------------------------------------------------

set(BUMP_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include")

configure_file(
    bump/Version.h.in
    "${BUMP_GENERATED_INCLUDE_DIR}/bump/Version.h"
    @ONLY
)

generate_export_header(bump
    BASE_NAME BUMP
    EXPORT_MACRO_NAME BUMP_EXPORT
    NO_EXPORT_MACRO_NAME BUMP_NO_EXPORT
    DEPRECATED_MACRO_NAME BUMP_DEPRECATED
    STATIC_DEFINE BUMP_STATIC_DEFINE
    EXPORT_FILE_NAME "${BUMP_GENERATED_INCLUDE_DIR}/bump/Export.h"
)

list(APPEND BUMP_PUBLIC_HEADERS
    "${BUMP_GENERATED_INCLUDE_DIR}/bump/Export.h"
    "${BUMP_GENERATED_INCLUDE_DIR}/bump/Version.h"
)

#------------------------------------------------------------------------------
# Include directories
#------------------------------------------------------------------------------

target_include_directories(bump
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${BUMP_GENERATED_INCLUDE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
        # For <smallsha1/sha1.h> from CryptographicHash.cpp, which compiles into
        # bump itself rather than into the object library.
        "${PROJECT_SOURCE_DIR}/src"
)

#------------------------------------------------------------------------------
# Public headers
#------------------------------------------------------------------------------
# A framework embeds its headers in the bundle and uses PUBLIC_HEADER;
# everything else uses FILE_SET HEADERS, which additionally enables
# CMAKE_VERIFY_INTERFACE_HEADER_SETS.

if(BUMP_BUILD_FRAMEWORK)
    # PUBLIC_HEADER only nominates which of the target's sources go into the
    # bundle's Headers directory -- the files must be sources too, or nothing is
    # copied and the framework ships with no headers at all.
    target_sources(bump PRIVATE ${BUMP_PUBLIC_HEADERS})
    set_target_properties(bump PROPERTIES PUBLIC_HEADER "${BUMP_PUBLIC_HEADERS}")
else()
    target_sources(bump
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                "${PROJECT_SOURCE_DIR}/include"
                "${BUMP_GENERATED_INCLUDE_DIR}"
            FILES ${BUMP_PUBLIC_HEADERS}
    )
endif()

#------------------------------------------------------------------------------
# Compile definitions
#------------------------------------------------------------------------------

if(NOT BUMP_BUILD_SHARED_LIBS)
    # PUBLIC so consumers inherit it through the exported target.
    target_compile_definitions(bump PUBLIC BUMP_STATIC_DEFINE)
endif()

target_compile_definitions(bump
    PUBLIC
        "$<$<PLATFORM_ID:Windows>:NOMINMAX>"
        "$<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>"
    PRIVATE
        # Boost.Filesystem defaults consumers to v3 while building its own
        # binaries as v4 (config.hpp:26-31). v3 and v4 differ observably:
        # path("/a/b/").filename() is "." under v3 and "" under v4, which reaches
        # FileInfo::filename(), basename() and extension(). Pinning keeps bump's
        # behaviour fixed if a future Boost flips the default, making that a
        # deliberate migration rather than a silent change.
        #
        # PRIVATE, not PUBLIC: path appears in the public headers only as a
        # protected FileInfo member, and every accessor returns bump::String
        # computed inside the library, so no path semantics cross the API. Making
        # it PUBLIC would force consumers' own unrelated filesystem code to v3
        # for no benefit to bump.
        BOOST_FILESYSTEM_VERSION=3
        # Also private: consumers may legitimately use deprecated Boost APIs of
        # their own. On bump it turns the next removal into a compile error when
        # introduced, rather than at the next Boost upgrade.
        BOOST_FILESYSTEM_NO_DEPRECATED
        "$<$<PLATFORM_ID:Windows>:_CRT_SECURE_NO_WARNINGS>"
)

#------------------------------------------------------------------------------
# Dependencies
#------------------------------------------------------------------------------
# PUBLIC where the type leaks into a public header, PRIVATE otherwise:
#   filesystem  FileInfo.h holds a boost::filesystem::path by value
#   thread      Log.h holds boost::mutex; NotificationCenter.h boost::shared_mutex
#   timer       Timer.h holds a boost::timer::cpu_timer by value
#   chrono      transitive of timer, named for clarity
#   headers     Export.h, Uuid.h, NotificationCenter.h include Boost headers
#   regex       String.cpp only
#   date_time   Log.cpp only

target_link_libraries(bump
    PUBLIC
        Boost::headers
        Boost::chrono
        Boost::filesystem
        Boost::thread
        Boost::timer
    PRIVATE
        Boost::date_time
        Boost::regex
)

#------------------------------------------------------------------------------
# Warnings
#------------------------------------------------------------------------------
# Measured clean: this set yields zero warnings across the library on both the
# static and dllexport paths. Warnings-as-errors is left to
# CMAKE_COMPILE_WARNING_AS_ERROR from the presets rather than a custom option.

target_compile_options(bump PRIVATE
    "$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra;-Wpedantic;-Wnon-virtual-dtor;-Woverloaded-virtual;-Wshadow>"
    # /permissive- is implicit under /std:c++20 but stated for clarity.
    # _SCL_SECURE_NO_WARNINGS is deliberately absent: a no-op since VS2015 with
    # zero trigger sites here.
    "$<$<CXX_COMPILER_ID:MSVC>:/W4;/utf-8;/permissive-;/Zc:__cplusplus;/EHsc;/bigobj>"
    "$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<BOOL:${BUMP_WIN32_USE_MP}>>:/MP>"
)

#------------------------------------------------------------------------------
# Target properties
#------------------------------------------------------------------------------

set_target_properties(bump PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${BUMP_SO_VERSION}
    FOLDER "bump/libraries"
)

if(BUMP_HIDE_PRIVATE_SYMBOLS)
    # Makes the 117 BUMP_EXPORT annotations meaningful rather than decorative.
    set_target_properties(bump PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
endif()

if(BUMP_BUILD_FRAMEWORK)
    # CMAKE_DEBUG_POSTFIX does not apply to frameworks; this is the mechanism
    # that lets a Debug and a Release framework coexist in one prefix.
    set_target_properties(bump PROPERTIES
        FRAMEWORK TRUE
        FRAMEWORK_VERSION A
        MACOSX_FRAMEWORK_IDENTIFIER com.bodyviz.bump
        MACOSX_FRAMEWORK_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${PROJECT_VERSION}
        FRAMEWORK_MULTI_CONFIG_POSTFIX_DEBUG "_debug"
    )
endif()
