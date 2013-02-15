
# Set the minimum required version of CMake
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

# Enable folders inside Visual Studio and Xcode
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

# Project settings
PROJECT (Bump)
SET (BUMP_MAJOR_VERSION 1)
SET (BUMP_MINOR_VERSION 1)
SET (BUMP_PATCH_VERSION 5)
SET (BUMP_SO_VERSION 17)
SET (BUMP_VERSION ${BUMP_MAJOR_VERSION}.${BUMP_MINOR_VERSION}.${BUMP_PATCH_VERSION})

# Include all the header directories
INCLUDE_DIRECTORIES (
	${Bump_SOURCE_DIR}/include
)

# Make the headers visible to everything
IF (NOT ${PROJECT_BINARY_DIR} EQUAL ${PROJECT_SOURCE_DIR})
   INCLUDE_DIRECTORIES (${PROJECT_BINARY_DIR}/include)
ENDIF()

# Set up the Bump Version file
SET (BUMP_VERSION_HEADER "${PROJECT_SOURCE_DIR}/include/bump/Version.h")
CONFIGURE_FILE ("${PROJECT_SOURCE_DIR}/src/bump/Version.in" ${BUMP_VERSION_HEADER})

# Add the custom macro utilities
SET (CMAKE_MODULE_PATH "${Bump_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
INCLUDE (BumpMacroUtils)

# If on an apple device, set whether to compile frameworks
IF (APPLE)
	OPTION (Bump_COMPILE_FRAMEWORKS "Compile frameworks instead of dylibs" ON)
	SET (Bump_INSTALL_NAME_DIR "@executable_path/../Frameworks"
		CACHE STRING "install name dir for compiled frameworks"
	)
ENDIF ()

# Set whether to use dynamic or static linking
OPTION (Bump_DYNAMIC_LINKING "Set to ON to build BUMP with dynamic linking (shared libraries). Use OFF for static." ON)
IF (Bump_DYNAMIC_LINKING OR Bump_COMPILE_FRAMEWORKS)
	SET (Bump_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
ELSE ()
	SET (Bump_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
ENDIF()

# If compiling with Visual Studio, set up some specific flags
IF (WIN32 AND MSVC)

	# This option is to enable the /MP switch for Visual Studio 2005 and above compilers
	OPTION (Bump_WIN32_USE_MP "Set to ON to build BUMP with the /MP option (Visual Studio 2005 and above)." ON)
	MARK_AS_ADVANCED (Bump_WIN32_USE_MP)
	IF (Bump_WIN32_USE_MP)
		SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	ENDIF ()

	# Some specific compiler flags to disable some warnings
	ADD_DEFINITIONS (-D_SCL_SECURE_NO_WARNINGS)
	ADD_DEFINITIONS (-D_CRT_SECURE_NO_DEPRECATE)

ENDIF ()

# Postfixes for all build types
SET (CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Add a postfix, usually 'd' on most operating systems")
SET (CMAKE_RELEASE_POSTFIX "" CACHE STRING "Add a postfix, usually empty on most operating systems")
SET (CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "Add a postfix, usually 'rd' on most operating systems")
SET (CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "Add a postfix, usually 's' on most operating systems")
IF (CMAKE_BUILD_TYPE MATCHES "Release")
	SET (CMAKE_BUILD_POSTFIX "${CMAKE_RELEASE_POSTFIX}")
ELSEIF (CMAKE_BUILD_TYPE MATCHES "MinSizeRel")
	SET (CMAKE_BUILD_POSTFIX "${CMAKE_MINSIZEREL_POSTFIX}")
ELSEIF (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
	SET (CMAKE_BUILD_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}")
ELSEIF (CMAKE_BUILD_TYPE MATCHES "Debug")
	SET (CMAKE_BUILD_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
ELSE ()
	SET (CMAKE_BUILD_POSTFIX "")
ENDIF ()

# Create the bin and lib directories
SET (OUTPUT_BINDIR ${PROJECT_BINARY_DIR}/bin)
MAKE_DIRECTORY (${OUTPUT_BINDIR})
SET (OUTPUT_LIBDIR ${PROJECT_BINARY_DIR}/lib)
MAKE_DIRECTORY (${OUTPUT_LIBDIR})

# Set up CMake to properly use the bin and lib directories when compiling
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIBDIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})
IF (WIN32)
	SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})
ELSE (WIN32)
	SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIBDIR})
ENDIF (WIN32)

# For each configuration (Debug, Release, MinSizeRel... and/or anything else)
FOREACH (CONF ${CMAKE_CONFIGURATION_TYPES})
	STRING (TOUPPER "${CONF}" CONF)			 # Go uppercase (DEBUG, RELEASE...)
	SET ("CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_LIBDIR}")
	SET ("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_BINDIR}")
	IF (WIN32)
		SET ("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_BINDIR}")
	ELSE ()
		SET ("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_LIBDIR}")
	ENDIF ()
ENDFOREACH ()

# Find Boost...using static, multithreaded libs with a shared runtime on Windows
IF (WIN32 AND MSVC)
	SET (Boost_USE_STATIC_LIBS    ON)
ENDIF (WIN32 AND MSVC)
SET (Boost_USE_MULTITHREAD    ON)
SET (Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE (Boost 1.52.0 COMPONENTS chrono date_time filesystem regex system thread timer REQUIRED)

# Find GTest
FIND_PACKAGE (GTest)

# Add the src subdirectory
ADD_SUBDIRECTORY (src)

# Set up everything for Doxygen
OPTION (Bump_BUILD_DOCUMENTATION "Build Bump reference documentation using Doxygen" OFF)
MARK_AS_ADVANCED (CLEAR Bump_BUILD_DOCUMENTATION)
IF (Bump_BUILD_DOCUMENTATION)

	# Find all the packages
	FIND_PACKAGE (UnixCommands)
	FIND_PACKAGE (Doxygen)
	FIND_PACKAGE (Gnuplot)
	FIND_PACKAGE (HTMLHelp)
	FIND_PACKAGE (Perl)
	FIND_PACKAGE (Wget)

	# Additional options
	OPTION (DOCUMENTATION_HTML_HELP "Build the HTML Help file (CHM)." OFF)
	OPTION (DOCUMENTATION_HTML_TARZ "Build a compressed tar archive of the HTML doc." OFF)

	# Advanced options
	MARK_AS_ADVANCED (DOCUMENTATION_HTML_HELP DOCUMENTATION_HTML_TARZ)

	# This processes our doxyfile.cmake and substitutes paths to generate a final Doxyfile
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/doc/doxyfile.cmake ${PROJECT_BINARY_DIR}/doc/bump.doxyfile)
	INSTALL (DIRECTORY ${PROJECT_BINARY_DIR}/doc/BumpReferenceDocs DESTINATION doc COMPONENT bump-doc)

	# Now we are going to create the new target to build the documentation. We need
	# to do this a bit differently when using makefiles so we remove the target
	# name spaces. How this works is that ${DOXYGEN} is run against the bump.doxyfile
	# and the docs are generated.
	IF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
		ADD_CUSTOM_TARGET ("Documentation_bump" ${DOXYGEN} ${PROJECT_BINARY_DIR}/doc/bump.doxyfile)
	    SET_TARGET_PROPERTIES ("Documentation_bump" PROPERTIES FOLDER "Documentation")
	ELSE (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
		ADD_CUSTOM_TARGET ("Documentation - bump" ${DOXYGEN} ${PROJECT_BINARY_DIR}/doc/bump.doxyfile)
	    SET_TARGET_PROPERTIES ("Documentation - bump" PROPERTIES FOLDER "Documentation")
	ENDIF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")

	# Need to create the BumpReferenceDocs directory in our build/doc directory
	FILE (MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/doc/BumpReferenceDocs)

ENDIF (Bump_BUILD_DOCUMENTATION)

# Set whether to build the examples
OPTION (Bump_BUILD_EXAMPLES "Enable to build Bump Examples" ON)
IF (Bump_BUILD_EXAMPLES)
	 ADD_SUBDIRECTORY (examples)
ENDIF ()

# Set whether to build the tests
OPTION (Bump_BUILD_TESTS "Enable to build Bump Tests" OFF)
IF (Bump_BUILD_TESTS)
   ADD_SUBDIRECTORY (tests)
ENDIF ()
