
# Only compile if we found GTest and Boost
IF (GTEST_FOUND AND Boost_FOUND)

	# Set the default prefix to make it easier to find in our projects
	# NOTE: we remove the empty spaces for the default prefix when
	# using makefiles to make sure the "make clean" works properly.
	IF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
		SET (TARGET_DEFAULT_PREFIX "Test_")
	ELSE (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
		SET (TARGET_DEFAULT_PREFIX "Test - ")
	ENDIF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")

	# Set the default label prefix
	SET (TARGET_DEFAULT_LABEL_PREFIX "Tests")

	# Add the GTest and Boost headers
	INCLUDE_DIRECTORIES (${GTEST_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

	# Add the Boost libraries
	SET (TARGET_EXTERNAL_LIBRARIES ${TARGET_EXTERNAL_LIBRARIES} ${Boost_LIBRARIES})

	# Add the GTest libraries
	SET (TARGET_EXTERNAL_LIBRARIES ${TARGET_EXTERNAL_LIBRARIES} ${GTEST_LIBRARIES})

	# Add the bump library
	SET (TARGET_COMMON_LIBRARIES bump)

	# Add definitions for shared or static builds
	IF (Bump_DYNAMIC_LINKING)
		ADD_DEFINITIONS(-DBump_LIBRARY)
	ELSE ()
		ADD_DEFINITIONS(-DBump_LIBRARY_STATIC)
	ENDIF ()
	
	# Add each set of tests
	FOREACH (BUMP_TEST
			bumpAllTests
			bumpEnvironmentTests
			bumpFileInfoTests
			bumpFileSystemTests
			bumpNotificationTests
			bumpStringTests
			bumpUuidTests
		)

		MESSAGE ("Configuring Test: " ${BUMP_TEST})
		ADD_SUBDIRECTORY (${BUMP_TEST})

	ENDFOREACH ()

ENDIF (GTEST_FOUND AND Boost_FOUND)
