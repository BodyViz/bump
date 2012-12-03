
# Only compile if we found GTest and Boost
IF (GTEST_FOUND AND Boost_FOUND)

	# Set the prefixes to make it easier to find in our projects
	SET (TARGET_DEFAULT_PREFIX "Test - ")
	SET (TARGET_DEFAULT_LABEL_PREFIX "Tests")

	# Add the GTest and Boost headers
	INCLUDE_DIRECTORIES (${GTEST_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

	# Add the GTest libraries
	SET (TARGET_EXTERNAL_LIBRARIES ${TARGET_EXTERNAL_LIBRARIES} ${GTEST_LIBRARIES})

	# Add the bump library
	SET (TARGET_COMMON_LIBRARIES bump)

	# Add each set of tests
	FOREACH (BUMP_TEST
			bumpAllTests
			bumpEnvironmentTests
			bumpStringTests
			bumpUuidTests
		)

		MESSAGE ("Configuring Test: " ${BUMP_TEST})
		ADD_SUBDIRECTORY (${BUMP_TEST})

	ENDFOREACH ()

ENDIF (GTEST_FOUND AND Boost_FOUND)
