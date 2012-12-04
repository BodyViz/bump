
# Only compile if we found Boost
IF (Boost_FOUND)

	# Set the prefixes to make it easier to find in our projects
	SET (TARGET_DEFAULT_PREFIX "Example - ")
	SET (TARGET_DEFAULT_LABEL_PREFIX "Examples")

    # Add the Boost headers
    INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIR})

	# Add the Boost libraries
    SET (TARGET_EXTERNAL_LIBRARIES ${TARGET_EXTERNAL_LIBRARIES} ${Boost_LIBRARIES})

	# Add the bump library
	SET (TARGET_COMMON_LIBRARIES bump)

	# Add all the examples
	FOREACH (BUMP_EXAMPLE
			bumpEnvironment
			bumpExceptions
			bumpLog
			bumpNotifications
			bumpStrings
			bumpUuids
		)

		MESSAGE ("Configuring Example: " ${BUMP_EXAMPLE})
		ADD_SUBDIRECTORY (${BUMP_EXAMPLE})

	ENDFOREACH ()

ENDIF (Boost_FOUND)
