
# Add the source files
SET (TARGET_SRC
	../bumpTest/main.cpp
	NotificationTest.cpp
)

# Add the header files
SET (TARGET_H
	../bumpTest/BaseTest.h
	../bumpTest/EnvironmentFixture.h
)

SETUP_TEST (bumpNotificationTests)
