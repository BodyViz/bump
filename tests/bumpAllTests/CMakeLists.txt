
# Add the source files
SET (TARGET_SRC
	../bumpTest/main.cpp
	../bumpEnvironmentTests/EnvironmentTest.cpp
	../bumpFileSystemTests/FileSystemTest.cpp
	../bumpNotificationTests/NotificationTest.cpp
	../bumpStringTests/StringTest.cpp
	../bumpUuidTests/UuidTest.cpp
)

# Add the header files
SET (TARGET_H
	../bumpTest/BaseTest.h
	../bumpTest/EnvironmentFixture.h
)

SETUP_TEST (bumpAllTests)
