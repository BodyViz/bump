#==============================================================================
#                     Imported configuration selection
#==============================================================================
# Run by the imported-config test against the report file-generated next to the
# smoke binary.
#
# A package normally ships Debug and Release only, so a consumer building
# RelWithDebInfo or MinSizeRel has no exact match. Without MAP_IMPORTED_CONFIG_*
# CMake then falls back to the first entry of IMPORTED_CONFIGURATIONS, which
# glob order makes Debug -- on MSVC that links a /MDd bump into a /MD consumer,
# with two CRT heaps and a different std:: container layout across the boundary.

file(STRINGS "${REPORT}" _lines)
foreach(line IN LISTS _lines)
    if(line MATCHES "^([a-z_]+)=(.*)$")
        set(_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}")
    endif()
endforeach()

string(REPLACE "," ";" _configurations "${_configurations}")

foreach(config RELWITHDEBINFO MINSIZEREL)
    string(TOLOWER "${config}" _key)
    if(_map_${_key} STREQUAL "")
        message(FATAL_ERROR
            "Bump::bump carries no MAP_IMPORTED_CONFIG_${config}. A consumer "
            "building ${config} against a package holding "
            "'${_configurations}' resolves through CMake's last resort, the "
            "first of those, rather than through a release-CRT artifact.")
    endif()

    # Independent of what this particular package happens to contain: Debug may
    # be in the list as a last resort, but never ahead of a release-CRT
    # configuration, or MSVC links /MDd into a /MD consumer.
    list(FIND _map_${_key} Debug _debug_at)
    list(FIND _map_${_key} Release _release_at)
    if(_debug_at GREATER_EQUAL 0 AND _release_at GREATER_EQUAL 0
            AND _debug_at LESS _release_at)
        message(FATAL_ERROR
            "MAP_IMPORTED_CONFIG_${config} is '${_map_${_key}}', which prefers "
            "Debug over Release.")
    endif()
endforeach()

# BUMP_STATIC_DEFINE is what makes Export.h take its static branch. It is PUBLIC,
# so it reaches every consumer through the exported target, and it has to agree
# with what was actually built: a static package without it leaves BUMP_EXPORT as
# __declspec(dllimport) under MSVC, and the consumer fails to link with
# unresolved __imp_ externals against an archive.
if(_type STREQUAL "STATIC_LIBRARY" AND NOT _static_define STREQUAL "1")
    message(FATAL_ERROR
        "Bump::bump is a STATIC_LIBRARY but the package does not define "
        "BUMP_STATIC_DEFINE.")
elseif(_type STREQUAL "SHARED_LIBRARY" AND _static_define STREQUAL "1")
    message(FATAL_ERROR
        "Bump::bump is a SHARED_LIBRARY but the package defines "
        "BUMP_STATIC_DEFINE, which suppresses the import attributes consumers "
        "need.")
endif()

# Only meaningful where the consumer's configuration is one the package does not
# ship; an exact match needs no mapping and is always right.
string(TOUPPER "${_config}" _config_upper)
if(NOT _config_upper IN_LIST _configurations AND NOT _release STREQUAL "")
    if(NOT _selected STREQUAL "${_release}")
        message(FATAL_ERROR
            "A ${_config} consumer of a '${_configurations}' package resolved "
            "Bump::bump to\n  ${_selected}\nrather than the release artifact\n  "
            "${_release}")
    endif()
endif()
