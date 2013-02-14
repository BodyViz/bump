
# Only compile if we found Boost
if (Boost_FOUND)

	# Add 3rd party and Boost headers
	SET (smallsha1_INCLUDE_DIR ${Bump_SOURCE_DIR}/include)
	INCLUDE_DIRECTORIES (${smallsha1_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

	# Add the Boost libraries
    SET (TARGET_EXTERNAL_LIBRARIES ${TARGET_EXTERNAL_LIBRARIES} ${Boost_LIBRARIES})

	# Add each of the libraries to the build
	FOREACH (BUMP_LIB bump)

		MESSAGE("Configuring Library: " ${BUMP_LIB})
		ADD_SUBDIRECTORY (${BUMP_LIB})

	ENDFOREACH()

ENDIF ()
