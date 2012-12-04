
# Add definitions for shared or static builds
IF (Bump_DYNAMIC_LINKING)
	ADD_DEFINITIONS(-DBump_LIBRARY)
ELSE ()
	ADD_DEFINITIONS(-DBump_LIBRARY_STATIC)
ENDIF ()

# Set up the lib name and header path
SET (LIB_NAME bump)
SET (HEADER_PATH ${Bump_SOURCE_DIR}/include/${LIB_NAME})

# Add all the headers
SET (
	TARGET_H
	${HEADER_PATH}/AutoTimer.h
	${HEADER_PATH}/Environment.h
	${HEADER_PATH}/Exception.h
	${HEADER_PATH}/Export.h
	${HEADER_PATH}/Log.h
	${HEADER_PATH}/NotificationCenter.h
	${HEADER_PATH}/String.h
	${HEADER_PATH}/Timeline.h
	${HEADER_PATH}/Timer.h
	${HEADER_PATH}/Uuid.h
	${HEADER_PATH}/Version.h
	${HEADER_PATH}/bump.h
)

# Add all the source files
SET (
	TARGET_SRC
	AutoTimer.cpp
	Environment.cpp
	Log.cpp
	NotificationCenter.cpp
	String.cpp
	Timeline.cpp
	Timer.cpp
	Uuid.cpp
	Version.cpp
)

# Finish setting up the library
SETUP_LIBRARY (${LIB_NAME})
