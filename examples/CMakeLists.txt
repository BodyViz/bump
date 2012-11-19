
# Only compile if we found Boost
IF (Boost_FOUND)

    # Add the Boost headers
    INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIR})

	# Add the Boost libraries
    SET (TARGET_EXTERNAL_LIBRARIES ${TARGET_EXTERNAL_LIBRARIES} ${Boost_LIBRARIES})

	# Add the bump library
	SET (TARGET_COMMON_LIBRARIES bump)

	# Add all the examples
	FOREACH (BUMP_EXAMPLE
			bumpExceptions
			bumpStrings
			bumpUuids
		)

		MESSAGE ("Configuring Example: " ${BUMP_EXAMPLE})
		ADD_SUBDIRECTORY (${BUMP_EXAMPLE})

	ENDFOREACH ()

ENDIF (Boost_FOUND)
