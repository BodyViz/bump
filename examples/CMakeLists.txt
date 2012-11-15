
# Only compile if we found Boost
IF (Boost_FOUND)

    # Add the Boost headers
    INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIR})

	# Add the bump library
	SET (TARGET_COMMON_LIBRARIES bump)

	# Add all the examples
	FOREACH (BUMP_EXAMPLE
			bumpExceptions
		)

		MESSAGE ("Configuring Example: " ${BUMP_EXAMPLE})
		ADD_SUBDIRECTORY (${BUMP_EXAMPLE})

	ENDFOREACH ()

ENDIF (Boost_FOUND)
