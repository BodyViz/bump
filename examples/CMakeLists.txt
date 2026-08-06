#==============================================================================
#                              Example applications
#==============================================================================
# Each example is a single translation unit at <name>/<name>.cpp, so a plain
# foreach replaces the old SETUP_EXAMPLE macro and the eleven two-line leaf
# CMakeLists files it drove.
#
# Everything an example needs -- include directories, C++20, the export define,
# and Boost -- arrives through Bump::bump's usage requirements. Nothing is
# restated here.

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

    set_target_properties(${example} PROPERTIES FOLDER "bump/examples")

    # The examples are warning-clean, so they inherit
    # CMAKE_COMPILE_WARNING_AS_ERROR along with the library rather than opting
    # out of it.
    target_compile_options(${example} PRIVATE
        "$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra>"
        "$<$<CXX_COMPILER_ID:MSVC>:/W4;/utf-8;/permissive-;/EHsc>"
        "$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<BOOL:${BUMP_WIN32_USE_MP}>>:/MP>"
    )

    # bumpFileSystem and bumpFileInfo call asctime/localtime, which MSVC
    # deprecates. Example code, so silence rather than rewrite.
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
    RUNTIME DESTINATION "${CMAKE_INSTALL_DATADIR}/bump/examples"
)
