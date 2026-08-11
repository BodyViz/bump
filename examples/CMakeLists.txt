#==============================================================================
#                              Example applications
#==============================================================================
# Each example is a single translation unit at <name>/<name>.cpp.
#
# Everything an example needs -- include directories, C++20, the export define,
# and Boost -- arrives through Bump::bump's usage requirements.

set(BUMP_EXAMPLES
    bumpAutoTimer
    bumpEnvironment
    bumpExceptions
    bumpFileInfo
    bumpFileSystem
    bumpLog
    bumpNotifications
    bumpStrings
    bumpTimeline
    bumpTimer
    bumpUuids
)

foreach(example IN LISTS BUMP_EXAMPLES)
    add_executable(${example} "${example}/${example}.cpp")
    target_link_libraries(${example} PRIVATE Bump::bump)

    # INSTALL_RPATH so the installed copy can still find a shared bump; see the
    # Installed runtime paths section in the top-level CMakeLists.
    set_target_properties(${example} PROPERTIES
        FOLDER "bump/examples"
        INSTALL_RPATH "${BUMP_RUNTIME_INSTALL_RPATH}"
    )

    target_compile_options(${example} PRIVATE
        "$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra>"
        "$<$<CXX_COMPILER_ID:AppleClang,Clang>:-Wshorten-64-to-32;-Wimplicit-int-conversion>"
        "$<$<CXX_COMPILER_ID:MSVC>:/W4;/utf-8;/permissive-;/EHsc>"
        "$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<BOOL:${BUMP_WIN32_USE_MP}>>:/MP>"
    )

    # bumpFileSystem and bumpFileInfo call asctime/localtime, which MSVC
    # deprecates.
    target_compile_definitions(${example} PRIVATE
        "$<$<PLATFORM_ID:Windows>:_CRT_SECURE_NO_WARNINGS>"
    )

    # Put the DLL next to the executable on Windows so an example can be run
    # straight from the build tree or a debugger. Expands to nothing elsewhere,
    # so this needs no if(WIN32) guard.
    add_custom_command(TARGET ${example} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy -t
                "$<TARGET_FILE_DIR:${example}>" "$<TARGET_RUNTIME_DLLS:${example}>"
        COMMAND_EXPAND_LISTS
    )
endforeach()

install(TARGETS ${BUMP_EXAMPLES}
    RUNTIME DESTINATION "${BUMP_RUNTIME_INSTALL_DIR}/examples"
)
