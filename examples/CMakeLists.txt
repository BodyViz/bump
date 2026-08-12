#==============================================================================
#                              Example applications
#==============================================================================
# Each example is a single translation unit at <name>/<name>.cpp.
#
# Everything an example needs -- include directories, C++20, the export define,
# and Boost -- arrives through Bump::bump's usage requirements.

set(CMAKE_INSTALL_RPATH "${BUMP_RUNTIME_INSTALL_RPATH}")
set(CMAKE_FOLDER "bump/examples")

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

endforeach()

install(TARGETS ${BUMP_EXAMPLES}
    RUNTIME DESTINATION "${BUMP_RUNTIME_INSTALL_DIR}/examples"
)

# Windows has no RPATH, so the DLLs have to sit beside the executables. The union
# over the whole group, not one representative: an example that grows a
# dependency the others lack is then still covered.
if(WIN32 AND BUILD_SHARED_LIBS)
    set(_bump_example_dlls "")
    foreach(example IN LISTS BUMP_EXAMPLES)
        list(APPEND _bump_example_dlls "$<TARGET_RUNTIME_DLLS:${example}>")
    endforeach()

    install(FILES "$<REMOVE_DUPLICATES:${_bump_example_dlls}>"
        DESTINATION "${BUMP_RUNTIME_INSTALL_DIR}/examples")
endif()
