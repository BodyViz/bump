
# Only compile if we found Boost
IF (Boost_FOUND)

	# Set the default prefix to make it easier to find in our projects
	# NOTE: we remove the empty spaces for the default prefix when
	# using makefiles to make sure the "make clean" works properly.
	IF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
		SET (TARGET_DEFAULT_PREFIX "Example_")
	ELSE (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
		SET (TARGET_DEFAULT_PREFIX "Example_")
	ENDIF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")

	# Set the default label prefix
	SET (TARGET_DEFAULT_LABEL_PREFIX "Examples")

    # Add the Boost headers
    INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIR})

	# Add the Boost libraries
    SET (TARGET_EXTERNAL_LIBRARIES ${TARGET_EXTERNAL_LIBRARIES} ${Boost_LIBRARIES})

	# Add the bump library
	SET (TARGET_COMMON_LIBRARIES bump)

	# Add definitions for shared or static builds
	IF (Bump_DYNAMIC_LINKING)
		ADD_DEFINITIONS(-DBump_LIBRARY)
	ELSE ()
		ADD_DEFINITIONS(-DBump_LIBRARY_STATIC)
	ENDIF ()

	# Add all the examples
	FOREACH (BUMP_EXAMPLE
			bumpAutoTimer
			bumpEnvironment
			bumpExceptions
			bumpFileInfo
			bumpFileSystem
			bumpLog
			bumpNotifications
			bumpStrings
			bumpTimeline
			bumpTimer
			bumpUuids
		)

		MESSAGE ("Configuring Example: " ${BUMP_EXAMPLE})
		ADD_SUBDIRECTORY (${BUMP_EXAMPLE})

	ENDFOREACH ()

ENDIF (Boost_FOUND)
