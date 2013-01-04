
# Add the source files
SET (TARGET_SRC
	../bumpTest/main.cpp
	../bumpCryptographicHashTests/CryptographicHashTest.cpp
	../bumpEnvironmentTests/EnvironmentTest.cpp
	../bumpFileInfoTests/FileInfoTest.cpp
	../bumpFileSystemTests/FileSystemTest.cpp
	../bumpNotificationTests/NotificationTest.cpp
	../bumpStringTests/StringTest.cpp
	../bumpUuidTests/UuidTest.cpp
)

# Add the platform specific source files
IF (WIN32)
	SET (
		TARGET_SRC
		${TARGET_SRC}
		../bumpFileInfoTests/FileInfoTest_win.cpp
		../bumpFileSystemTests/FileSystemTest_win.cpp
	)
ELSE (WIN32)
	SET (
		TARGET_SRC
		${TARGET_SRC}
		../bumpFileInfoTests/FileInfoTest_unix.cpp
		../bumpFileSystemTests/FileSystemTest_unix.cpp
	)
ENDIF (WIN32)

# Add the header files
SET (TARGET_H
	../bumpTest/BaseTest.h
	../bumpTest/EnvironmentFixture.h
	../bumpFileInfoTests/FileInfoTest.h
	../bumpFileSystemTests/FileSystemTest.h
)

SETUP_TEST (bumpAllTests)
