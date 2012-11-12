
# Only compile if we found GTest and Boost
IF (GTEST_FOUND AND Boost_FOUND)

    # Add the GTest and Boost headers
    INCLUDE_DIRECTORIES (${GTEST_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

	# Add the GTest libraries
	SET (TARGET_EXTERNAL_LIBRARIES ${TARGET_EXTERNAL_LIBRARIES} ${GTEST_LIBRARIES})

	# Add the bump library
	SET (TARGET_COMMON_LIBRARIES bump)

	# Add each set of tests
	FOREACH (BUMP_TEST
			bumpStringTests
		)

	    MESSAGE ("Configuring Test: " ${BUMP_TEST})
	    ADD_SUBDIRECTORY (${BUMP_TEST})

	ENDFOREACH ()

ENDIF (GTEST_FOUND AND Boost_FOUND)
