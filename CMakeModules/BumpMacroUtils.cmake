
#######################################################################################################
#
#  Macro for common setup of libraries.
#
#  NOTE: it expects some variables to be set either within local CMakeLists or higher in the hierarchy.
#
#  LIB_NAME						- name of the target library
#  TARGET_SRC					- source files of the target
#  TARGET_H						- eventual headers of the target
#  TARGET_H_NO_MODULE_INSTALL	- target headers that won't get installed by the ModuleInstall script
#  TARGET_LIBRARIES				- libraries to link to that are internal to the project (have d suffix)
#  TARGET_EXTERNAL_LIBRARIES	- external libraries and are not differentiated with d suffix
#  TARGET_LABEL					- label IDE should show up for targets
#
##########################################################################################################

MACRO (SETUP_LIBRARY LIB_NAME)

	SET (TARGET_NAME ${LIB_NAME})
	SET (TARGET_TARGETNAME ${LIB_NAME})
	ADD_LIBRARY (
		${LIB_NAME}
		${Bump_USER_DEFINED_DYNAMIC_OR_STATIC}
		${TARGET_SRC}
		${TARGET_H}
	)

	SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES FOLDER "Libraries")
	IF (TARGET_LABEL)
		SET_TARGET_PROPERTIES (
			${TARGET_TARGETNAME}
			PROPERTIES
			PROJECT_LABEL
			"${TARGET_LABEL}"
		)
	ENDIF (TARGET_LABEL)

	# Add linking to other libraries here
	IF (TARGET_LIBRARIES)
		LINK_INTERNAL (${LIB_NAME} ${TARGET_LIBRARIES})
	ENDIF()
	IF (TARGET_EXTERNAL_LIBRARIES)
		LINK_EXTERNAL (${LIB_NAME} ${TARGET_EXTERNAL_LIBRARIES})
	ENDIF()
	IF (TARGET_LIBRARIES_VARS)
		LINK_WITH_VARIABLES (${LIB_NAME} ${TARGET_LIBRARIES_VARS})
	ENDIF(TARGET_LIBRARIES_VARS)

	# Install the libraries
	SET (INSTALL_INCDIR include)
	SET (INSTALL_BINDIR bin)
	SET (INSTALL_LIBDIR lib)
	SET (INSTALL_ARCHIVEDIR lib)

	INSTALL(
		TARGETS ${LIB_NAME}
		RUNTIME DESTINATION ${INSTALL_BINDIR}
		LIBRARY DESTINATION ${INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${INSTALL_ARCHIVEDIR}
	)

	IF (NOT Bump_COMPILE_FRAMEWORKS)
		INSTALL (
			FILES ${TARGET_H}
			DESTINATION ${INSTALL_INCDIR}/${LIB_NAME}
		)

		# Still need to install the RPATH even if it is not a framework for deployment
		IF (APPLE)
			SET (CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
			SET (CMAKE_INSTALL_RPATH "${BUMP_INSTALL_NAME_DIR}")

			SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES
				 FRAMEWORK FALSE
				 FRAMEWORK_VERSION ${BUMP_SO_VERSION}
				 PUBLIC_HEADER "${TARGET_H}"
				 INSTALL_NAME_DIR "${BUMP_INSTALL_NAME_DIR}"
			)
		ENDIF()

	ELSE ()
		SET (CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
		SET (CMAKE_INSTALL_RPATH "${BUMP_INSTALL_NAME_DIR}")

		SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES
			 FRAMEWORK TRUE
			 FRAMEWORK_VERSION ${BUMP_SO_VERSION}
			 PUBLIC_HEADER "${TARGET_H}"
			 INSTALL_NAME_DIR "${BUMP_INSTALL_NAME_DIR}"
		)
	ENDIF ()

	# Set the version of the library
	SET_TARGET_PROPERTIES (${LIB_NAME} PROPERTIES VERSION ${BUMP_VERSION} SOVERSION ${BUMP_SO_VERSION})

ENDMACRO (SETUP_LIBRARY LIB_NAME)


#######################################################################################################
#
#  Macros for linking with internal and external libraries. All the libraries to link come
#  in as a list.
#
#  NOTE: it expects some variables to be set either within local CMakeLists or higher in the hierarchy.
#
#  LIB_NAME						- name of the target library
#
##########################################################################################################

MACRO (LINK_EXTERNAL TRGTNAME)
	TARGET_LINK_LIBRARIES (${TRGTNAME} ${ARGN})
ENDMACRO()

MACRO (LINK_INTERNAL TRGTNAME)
	IF (MSVC OR APPLE AND NOT Bump_COMPILE_FRAMEWORKS)
		FOREACH (LINKLIB ${ARGN})
			IF (MSVC)
				TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${OUTPUT_LIBDIR}/${LINKLIB}${CMAKE_RELEASE_POSTFIX}.lib" debug "${OUTPUT_LIBDIR}/${LINKLIB}${CMAKE_DEBUG_POSTFIX}.lib")
				ADD_DEPENDENCIES(${TRGTNAME} ${LINKLIB})
			ELSEIF (APPLE AND Bump_DYNAMIC_LINKING)
				TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${OUTPUT_LIBDIR}/lib${LINKLIB}${CMAKE_RELEASE_POSTFIX}.dylib" debug "${OUTPUT_LIBDIR}/lib${LINKLIB}${CMAKE_DEBUG_POSTFIX}.dylib")
				ADD_DEPENDENCIES(${TRGTNAME} ${LINKLIB})
			ELSE ()
				TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${OUTPUT_LIBDIR}/lib${LINKLIB}${CMAKE_RELEASE_POSTFIX}.a" debug "${OUTPUT_LIBDIR}/lib${LINKLIB}${CMAKE_DEBUG_POSTFIX}.a")
				ADD_DEPENDENCIES(${TRGTNAME} ${LINKLIB})
			ENDIF ()
		ENDFOREACH ()
	ELSE (MSVC OR APPLE AND NOT Bump_COMPILE_FRAMEWORKS)
		TARGET_LINK_LIBRARIES (${TRGTNAME} ${ARGN})
	ENDIF (MSVC OR APPLE AND NOT Bump_COMPILE_FRAMEWORKS)

	# This is what it used to be, may need to be modified with postfix addition
	#TARGET_LINK_LIBRARIES (${TRGTNAME} ${ARGN})
ENDMACRO ()

MACRO (LINK_WITH_VARIABLES TRGTNAME)
	FOREACH (varname ${ARGN})
		IF (${varname}_DEBUG)
			TARGET_LINK_LIBRARIES (${TRGTNAME} optimized "${${varname}}" debug "${${varname}_DEBUG}")
		ELSE ()
			TARGET_LINK_LIBRARIES (${TRGTNAME} "${${varname}}")
		ENDIF ()
	ENDFOREACH ()
ENDMACRO ()


#######################################################################################################
#
#  Macro for linking a target against all necessary libraries.
#
#  NOTE: it expects some variables to be set either within local CMakeLists or higher in the hierarchy.
#
#  TARGET_COMMON_LIBRARIES		- common internal libraries to link against
#  TARGET_TARGETNAME			- name of the target
#
##########################################################################################################

MACRO (SETUP_LINK_LIBRARIES)

	# First eliminate any duplicate common libraries
	SET (TARGET_LIBRARIES ${TARGET_COMMON_LIBRARIES})
	FOREACH (LINKLIB ${TARGET_ADDED_LIBRARIES})
		SET (TO_INSERT TRUE)
		FOREACH (value ${TARGET_COMMON_LIBRARIES})
			IF (${value} STREQUAL ${LINKLIB})
				SET (TO_INSERT FALSE)
			ENDIF ()
		ENDFOREACH ()
		IF (TO_INSERT)
			LIST (APPEND TARGET_LIBRARIES ${LINKLIB})
		ENDIF ()
	ENDFOREACH ()

	# Link the target to all the libraries built by this cmake project
	LINK_INTERNAL (${TARGET_TARGETNAME} ${TARGET_LIBRARIES})

	# Add linking to other libraries built externally
	IF (TARGET_EXTERNAL_LIBRARIES)
		TARGET_LINK_LIBRARIES (${TARGET_TARGETNAME} ${TARGET_EXTERNAL_LIBRARIES})
	ENDIF ()
	IF (TARGET_LIBRARIES_VARS)
		LINK_WITH_VARIABLES (${TARGET_TARGETNAME} ${TARGET_LIBRARIES_VARS})
	ENDIF ()

ENDMACRO (SETUP_LINK_LIBRARIES)


#######################################################################################################
#
#  Macro for setting up examples and applications.
#
#  NOTE: it expects some variables to be set either within local CMakeLists or higher in the hierarchy.
#
#  TARGET_COMMON_LIBRARIES		- common internal libraries to link against
#  TARGET_H						- eventual headers of the target
#  TARGET_SRC					- source files of the target
#
##########################################################################################################

MACRO (SETUP_EXE IS_COMMANDLINE_APP)

	IF (NOT TARGET_TARGETNAME)
		SET (TARGET_TARGETNAME "${TARGET_DEFAULT_PREFIX}${TARGET_NAME}")
	ENDIF()

	IF (NOT TARGET_LABEL)
		SET (TARGET_LABEL "${TARGET_DEFAULT_LABEL_PREFIX} ${TARGET_NAME}")
	ENDIF()

	IF (${IS_COMMANDLINE_APP})
		ADD_EXECUTABLE (${TARGET_TARGETNAME} ${TARGET_SRC} ${TARGET_H})
	ELSE (${IS_COMMANDLINE_APP})
		IF (WIN32)
			IF (REQUIRE_WINMAIN_FLAG)
				SET (PLATFORM_SPECIFIC_CONTROL WIN32)
			ENDIF ()
		ENDIF ()
		ADD_EXECUTABLE(${TARGET_TARGETNAME} ${PLATFORM_SPECIFIC_CONTROL} ${TARGET_SRC} ${TARGET_H})
	ENDIF ()

	SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES PROJECT_LABEL "${TARGET_LABEL}")
	SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES OUTPUT_NAME ${TARGET_NAME})
	SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES DEBUG_OUTPUT_NAME "${TARGET_NAME}${CMAKE_DEBUG_POSTFIX}")
	SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES RELEASE_OUTPUT_NAME "${TARGET_NAME}${CMAKE_RELEASE_POSTFIX}")
	SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES RELWITHDEBINFO_OUTPUT_NAME "${TARGET_NAME}${CMAKE_RELWITHDEBINFO_POSTFIX}")
	SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES MINSIZEREL_OUTPUT_NAME "${TARGET_NAME}${CMAKE_MINSIZEREL_POSTFIX}")

	SETUP_LINK_LIBRARIES()

ENDMACRO (SETUP_EXE)


#######################################################################################################
#
#  Macro for setting up an example.
#
#  NOTE: it expects some variables to be set either within local CMakeLists or higher in the hierarchy.
#
#  TARGET_COMMON_LIBRARIES		- common internal libraries to link against
#  TARGET_SRC					- source files of the target
#
##########################################################################################################

MACRO (SETUP_EXAMPLE EXAMPLE_NAME)

	SET (TARGET_NAME ${EXAMPLE_NAME})

	# Specify whether it is a command line app
	IF (${ARGC} GREATER 1)
		SET (IS_COMMANDLINE_APP ${ARGV1})
	ELSE ()
		SET (IS_COMMANDLINE_APP 0)
	ENDIF ()

	# Setup the executable
	SETUP_EXE (${IS_COMMANDLINE_APP})

	# Put the generated project into an Examples folder
	SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES FOLDER "Examples")

	# Install the example
	INSTALL (
		TARGETS ${TARGET_TARGETNAME}
		RUNTIME DESTINATION share/examples/bin
	)

ENDMACRO (SETUP_EXAMPLE)

#######################################################################################################
#
#  Macro for setting up a test.
#
#  NOTE: it expects some variables to be set either within local CMakeLists or higher in the hierarchy.
#
#  TARGET_COMMON_LIBRARIES		- common internal libraries to link against
#  TARGET_SRC					- source files of the target
#
##########################################################################################################

MACRO (SETUP_TEST TEST_NAME)

	SET (TARGET_NAME ${TEST_NAME})

	# Specify whether it is a command line app
	IF (${ARGC} GREATER 1)
		SET (IS_COMMANDLINE_APP ${ARGV1})
	ELSE ()
		SET (IS_COMMANDLINE_APP 0)
	ENDIF ()

	# Setup the executable
	SETUP_EXE (${IS_COMMANDLINE_APP})

	# Put the generated project into an Tests folder
	SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES FOLDER "Tests")

	# Install the example
	INSTALL (
		TARGETS ${TARGET_TARGETNAME}
		RUNTIME DESTINATION share/tests/bin
	)

ENDMACRO (SETUP_TEST)
