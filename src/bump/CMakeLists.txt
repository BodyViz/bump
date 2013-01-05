
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
	${HEADER_PATH}/CryptographicHash.h
	${HEADER_PATH}/Environment.h
	${HEADER_PATH}/Exception.h
	${HEADER_PATH}/Export.h
	${HEADER_PATH}/FileInfo.h
	${HEADER_PATH}/FileSystem.h
	${HEADER_PATH}/FileSystemError.h
	${HEADER_PATH}/InvalidArgumentError.h
	${HEADER_PATH}/Log.h
	${HEADER_PATH}/Log_impl.h
	${HEADER_PATH}/NotificationCenter.h
	${HEADER_PATH}/NotificationCenter_impl.h
	${HEADER_PATH}/NotificationError.h
	${HEADER_PATH}/NotImplementedError.h
	${HEADER_PATH}/OutOfRangeError.h
	${HEADER_PATH}/Singleton.h
	${HEADER_PATH}/SingletonError.h
	${HEADER_PATH}/String.h
	${HEADER_PATH}/StringSearchError.h
	${HEADER_PATH}/Timeline.h
	${HEADER_PATH}/Timer.h
	${HEADER_PATH}/TypeCastError.h
	${HEADER_PATH}/Uuid.h
	${HEADER_PATH}/Version.h
	${HEADER_PATH}/bump.h
)

# Add some of the source files
SET (TARGET_SRC
	AutoTimer.cpp
	CryptographicHash.cpp
	Exception.cpp
)

# Add Environment files
IF (WIN32)
	SET (TARGET_SRC ${TARGET_SRC} Environment.cpp Environment_win.cpp)
ELSE (WIN32)
	SET (TARGET_SRC ${TARGET_SRC} Environment.cpp Environment_unix.cpp)
ENDIF (WIN32)

# Add FileInfo files
IF (WIN32)
	SET (TARGET_SRC ${TARGET_SRC} FileInfo.cpp FileInfo_win.cpp)
ELSE (WIN32)
	SET (TARGET_SRC ${TARGET_SRC} FileInfo.cpp FileInfo_unix.cpp)
ENDIF (WIN32)

# Add FileSystem files
IF (WIN32)
	SET (TARGET_SRC ${TARGET_SRC} FileSystem.cpp FileSystem_win.cpp)
ELSE (WIN32)
	SET (TARGET_SRC ${TARGET_SRC} FileSystem.cpp FileSystem_unix.cpp)
ENDIF (WIN32)

# Add the rest of the source files
SET (TARGET_SRC
	${TARGET_SRC}
	FileSystemError.cpp
	InvalidArgumentError.cpp
	Log.cpp
	NotificationCenter.cpp
	NotificationError.cpp
	NotImplementedError.cpp
	OutOfRangeError.cpp
	SingletonError.cpp
	String.cpp
	StringSearchError.cpp
	Timeline.cpp
	Timer.cpp
	TypeCastError.cpp
	Uuid.cpp
	Version.cpp
)

# Add smallsha1 as a target 3rd party dependency
SET (TARGET_3RD_PARTY_LIBRARIES smallsha1)

# Finish setting up the library
SETUP_LIBRARY (${LIB_NAME})
