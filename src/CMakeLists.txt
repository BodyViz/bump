
# Only compile if we found Boost
if (Boost_FOUND)

	# Add the Boost headers
	INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIR})

	# Add the Boost regex library
    SET (TARGET_EXTERNAL_LIBRARIES ${TARGET_EXTERNAL_LIBRARIES} ${Boost_LIBRARIES})

	# Add each of the libraries to the build
	FOREACH (BUMP_LIB bump)

		MESSAGE("Configuring Library: " ${BUMP_LIB})
		ADD_SUBDIRECTORY (${BUMP_LIB})

	ENDFOREACH()

ENDIF ()
