#==============================================================================
#                          Reference documentation
#==============================================================================
# Reached only when BUMP_BUILD_DOCS is ON and Doxygen was found, so this file
# never has to test for either.
#
# There is no checked-in Doxyfile, deliberately. doxygen_add_docs() runs
# `doxygen -s -g` at configure time and derives its template from whichever
# doxygen is installed, so the file doxygen consumes is always one doxygen
# itself just emitted. Obsolete-tag rot is structurally impossible.
#
# Everything below is a deviation from doxygen's own defaults or from the ones
# doxygen_add_docs() supplies. PROJECT_NAME, PROJECT_NUMBER, PROJECT_BRIEF,
# RECURSIVE, OUTPUT_DIRECTORY, HAVE_DOT and GENERATE_LATEX are all already
# derived from project() or from whether graphviz is installed, so they are
# absent rather than restated.

set(DOXYGEN_HTML_OUTPUT BumpReferenceDocs)
set(DOXYGEN_TAB_SIZE 4)

# Public API only -- but by *excluding* the internals rather than by hiding
# whatever happens to be undocumented, which are not the same thing.
#
# INTERNAL_DOCS=YES then makes \internal a no-op, which it has to be: the
# remaining protected members are documented but marked \internal, and with
# INTERNAL_DOCS=NO doxygen counts a documented-but-internal member as
# undocumented.
set(DOXYGEN_EXTRACT_ALL NO)
set(DOXYGEN_HIDE_UNDOC_MEMBERS NO)
set(DOXYGEN_HIDE_UNDOC_CLASSES NO)
set(DOXYGEN_INTERNAL_DOCS YES)
set(DOXYGEN_EXCLUDE_SYMBOLS "_*")

set(DOXYGEN_SORT_MEMBER_DOCS YES)
set(DOXYGEN_SORT_BRIEF_DOCS YES)
set(DOXYGEN_SORT_GROUP_NAMES YES)
set(DOXYGEN_SORT_BY_SCOPE_NAME YES)
set(DOXYGEN_ALPHABETICAL_INDEX YES)

# Both include roots, so paths render as bump/String.h rather than absolute.
set(DOXYGEN_STRIP_FROM_PATH
    "${PROJECT_SOURCE_DIR}/include"
    "${BUMP_GENERATED_INCLUDE_DIR}"
)

# Without this, BUMP_EXPORT renders literally in every free-function signature.
# The expansion must be *empty*;
set(DOXYGEN_ENABLE_PREPROCESSING YES)
set(DOXYGEN_MACRO_EXPANSION YES)
set(DOXYGEN_EXPAND_ONLY_PREDEF YES)
set(DOXYGEN_PREDEFINED
    "BUMP_EXPORT="
    "BUMP_NO_EXPORT="
    "BUMP_DEPRECATED="
)

#------------------------------------------------------------------------------
# The gate
#------------------------------------------------------------------------------
# A stale @param, a @return on a void, or an undocumented new public method is
# a build failure rather than a quiet degradation of the docs.
#
# FAIL_ON_WARNINGS rather than YES: it processes the whole tree and *then*
# exits non-zero, so one run reports every problem instead of stopping at the
# first.
set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
set(DOXYGEN_WARN_IF_DOC_ERROR YES)
set(DOXYGEN_WARN_NO_PARAMDOC YES)
set(DOXYGEN_WARN_AS_ERROR FAIL_ON_WARNINGS)
set(DOXYGEN_QUIET YES)

#------------------------------------------------------------------------------
# The target
#------------------------------------------------------------------------------
# The binary include directory is named as well as the source one so the
# generated Version.h and Export.h are documented. No add_dependencies() on
# bump is needed: configure_file() and generate_export_header() both write at
# configure time, so a fresh configure followed immediately by --target
# bump_docs succeeds with no compilation at all.
doxygen_add_docs(bump_docs ALL
    "${PROJECT_SOURCE_DIR}/include/bump"
    "${BUMP_GENERATED_INCLUDE_DIR}/bump"
    COMMENT "Generating Bump reference documentation"
)

set_target_properties(bump_docs PROPERTIES FOLDER "bump/docs")

# OPTIONAL because the directory does not exist until bump_docs has run, and
# `cmake --install` does not build first.
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_HTML_OUTPUT}"
    DESTINATION "${CMAKE_INSTALL_DOCDIR}"
    COMPONENT bump-doc
    OPTIONAL
)
