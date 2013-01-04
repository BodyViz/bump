
# Add each 3rd party library
FOREACH (BUMP_3RD_PARTY_LIB smallsha1)

	MESSAGE("Configuring 3rd Party Library: " ${BUMP_3RD_PARTY_LIB})
	ADD_SUBDIRECTORY (${BUMP_3RD_PARTY_LIB})

ENDFOREACH()
