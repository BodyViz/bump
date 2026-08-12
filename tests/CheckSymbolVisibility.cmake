#==============================================================================
#                          Exported symbol policy
#==============================================================================
# Run by the symbol-visibility test. BUMP_HIDE_PRIVATE_SYMBOLS promises to
# "export only BUMP_EXPORT-annotated symbols from the shared library" -- note
# the shared library. The two flavours fail that promise in opposite directions:
#
#   shared  the vendored smallsha1 is compiled as a separate object library and
#           never inherits the visibility properties, so its symbols escape.
#   static  BUMP_EXPORT expands to nothing under BUMP_STATIC_DEFINE, so hidden
#           visibility hides every symbol in the archive and a shared library
#           that links it re-exports none of them.
#
#   LIBRARY  the built libbump artifact
#   TYPE     STATIC_LIBRARY or SHARED_LIBRARY

find_program(NM_EXECUTABLE nm REQUIRED)

# Matched on the mangled names: 4bump and 4sha1 are the namespace components.
set(_bump_visible 0)
set(_sha1_visible 0)

if(TYPE STREQUAL "SHARED_LIBRARY")
    # -g -U is already exactly "global, defined", so every line counts.
    execute_process(COMMAND "${NM_EXECUTABLE}" -gU "${LIBRARY}"
        OUTPUT_VARIABLE _symbols COMMAND_ERROR_IS_FATAL ANY)
    string(REPLACE "\n" ";" _lines "${_symbols}")
    foreach(line IN LISTS _lines)
        if(line MATCHES "4bump")
            math(EXPR _bump_visible "${_bump_visible}+1")
        elseif(line MATCHES "4sha1")
            math(EXPR _sha1_visible "${_sha1_visible}+1")
        endif()
    endforeach()
else()
    # -m names the symbol class, of which only a bare "external" is reachable
    # from outside: "private external" is the hidden-visibility form, and
    # "non-external" is a file-local static. An undefined symbol is reported as
    # plain external whatever its definition looks like elsewhere, so references
    # have to be dropped or every archive reads as fully visible.
    execute_process(COMMAND "${NM_EXECUTABLE}" -m "${LIBRARY}"
        OUTPUT_VARIABLE _symbols COMMAND_ERROR_IS_FATAL ANY)
    string(REPLACE "\n" ";" _lines "${_symbols}")
    foreach(line IN LISTS _lines)
        if(line MATCHES "\\(undefined\\)" OR NOT line MATCHES "\\) external ")
            continue()
        endif()
        if(line MATCHES "4bump")
            math(EXPR _bump_visible "${_bump_visible}+1")
        elseif(line MATCHES "4sha1")
            math(EXPR _sha1_visible "${_sha1_visible}+1")
        endif()
    endforeach()
endif()

if(TYPE STREQUAL "SHARED_LIBRARY")
    if(_sha1_visible GREATER 0)
        message(FATAL_ERROR
            "${LIBRARY} exports ${_sha1_visible} vendored smallsha1 symbol(s). "
            "An application linking bump alongside any other library carrying "
            "its own copy gets whichever the loader binds first.")
    endif()
    if(_bump_visible EQUAL 0)
        message(FATAL_ERROR
            "${LIBRARY} exports no bump symbols at all; consumers cannot link.")
    endif()
else()
    if(_bump_visible EQUAL 0)
        message(FATAL_ERROR
            "Every bump symbol in ${LIBRARY} is private external. A shared "
            "library linking this archive re-exports none of them, so anything "
            "linking only that shared library fails with undefined references.")
    endif()
endif()
