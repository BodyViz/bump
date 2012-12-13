###########################################################################################
#
# FindBump.cmake
# Bump
#
# Created by Christian Noon 12/12/12.
# Copyright (c) 2012 Christian Noon. All rights reserved.
#
#
# This module defines:
#
# - BUMP_DIR (where the Bump installation was installed)
# - BUMP_LIBRARIES (where to find the libraries)
# - BUMP_FOUND (whether the headers and library were found)
# - BUMP_INCLUDE_DIR (where to find the headers)
#
###########################################################################################

FIND_PATH (BUMP_INCLUDE_DIR bump/bump.h
    ${BUMP_DIR}/include
    NO_DEFAULT_PATH
)

MACRO (FIND_BUMP_LIBRARY MYLIBRARY MYLIBRARYNAME)

    FIND_LIBRARY ("${MYLIBRARY}_DEBUG"
        NAMES "${MYLIBRARYNAME}d"
        PATHS
        ${BUMP_DIR}/lib/Debug
        ${BUMP_DIR}/lib64/Debug
        ${BUMP_DIR}/lib
        ${BUMP_DIR}/lib64
        NO_DEFAULT_PATH
    )

    FIND_LIBRARY ("${MYLIBRARY}_DEBUG"
        NAMES "${MYLIBRARYNAME}d"
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
        /usr/local/lib64
        /usr/lib
        /usr/lib64
        /opt/local/lib
        /opt/lib
    )

    FIND_LIBRARY (${MYLIBRARY}
        NAMES "${MYLIBRARYNAME}"
        PATHS
        ${BUMP_DIR}/lib/Release
        ${BUMP_DIR}/lib64/Release
        ${BUMP_DIR}/lib
        ${BUMP_DIR}/lib64
        NO_DEFAULT_PATH
    )

    FIND_LIBRARY (${MYLIBRARY}
        NAMES "${MYLIBRARYNAME}"
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
        /usr/local/lib64
        /usr/lib
        /usr/lib64
        /opt/local/lib
        /opt/lib
    )

	# Set the debug version to the release if the debug couldn't be found
    IF (NOT ${MYLIBRARY}_DEBUG)
        IF (${MYLIBRARY})
            SET (${MYLIBRARY}_DEBUG ${${MYLIBRARY}})
        ENDIF ()
    ENDIF ()

	# Bake both debug and release into the same variable
    SET (${MYLIBRARY} optimized ${${MYLIBRARY}} debug ${${MYLIBRARY}_DEBUG})

ENDMACRO (FIND_BUMP_LIBRARY LIBRARY LIBRARYNAME)

# Go fetch all the bump library
FIND_BUMP_LIBRARY (BUMP_bump_LIBRARY bump)

# Build the BUMP_LIBRARY variable
SET (BUMP_FOUND "NO")
IF (BUMP_bump_LIBRARY)
    SET (BUMP_FOUND "YES")
    SET (BUMP_LIBRARIES ${BUMP_bump_LIBRARY})
ENDIF ()

# Add the ability to just set the BUMP_DIR and let CMake figure the rest out
IF (NOT BUMP_FOUND)
	SET (BUMP_DIR "" CACHE PATH "Root of Bump installation tree (optional).")
ENDIF ()
