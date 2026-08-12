#==============================================================================
#                         BumpConfig content assertions
#==============================================================================
# Run by the package-config-boost-linkage test. Asserts that the generated
# BumpConfig records Boost's linkage preference exactly as the build expressed
# it, where "expressed nothing" must stay nothing: a defined-but-false
# Boost_USE_STATIC_LIBS is an active demand for shared Boost, so recording OFF
# for a build that never asked forbids a static-only Boost in the consumer.
#
#   CONFIG_FILE  the generated BumpConfig.cmake
#   EXPECTED     the build's own Boost_USE_STATIC_LIBS, or empty if undefined

if(NOT EXISTS "${CONFIG_FILE}")
    message(FATAL_ERROR "BumpConfig.cmake not found at ${CONFIG_FILE}")
endif()

file(READ "${CONFIG_FILE}" _contents)

# Either a literal forced into the consumer, or the recorded value the config
# applies conditionally. Anything else records no preference.
if(_contents MATCHES "set\\(Boost_USE_STATIC_LIBS[ \t]+([A-Za-z0-9]+)\\)")
    set(_recorded "${CMAKE_MATCH_1}")
elseif(_contents MATCHES "set\\(_bump_boost_static_libs[ \t]+\"([^\"]*)\"\\)")
    set(_recorded "${CMAKE_MATCH_1}")
else()
    set(_recorded "")
endif()

if(NOT _recorded STREQUAL "${EXPECTED}")
    if("${EXPECTED}" STREQUAL "")
        message(FATAL_ERROR
            "BumpConfig records Boost_USE_STATIC_LIBS as '${_recorded}' but this "
            "build expressed no preference. Record nothing instead: a consumer "
            "with a static-only Boost cannot satisfy a package that demands "
            "shared.")
    else()
        message(FATAL_ERROR
            "BumpConfig records Boost_USE_STATIC_LIBS as '${_recorded}'; this "
            "build was configured with '${EXPECTED}'.")
    endif()
endif()
