
# Add the source files
SET (TARGET_SRC
	../bumpTest/main.cpp
	FileInfoTest.cpp
)

# Add the platform specific source files
IF (WIN32)
	SET (TARGET_SRC ${TARGET_SRC} FileInfoTest_win.cpp)
ELSE (WIN32)
	SET (TARGET_SRC ${TARGET_SRC} FileInfoTest_unix.cpp)
ENDIF (WIN32)

# Add the header files
SET (TARGET_H
	../bumpTest/BaseTest.h
	../bumpTest/EnvironmentFixture.h
	FileInfoTest.h
)

SETUP_TEST (bumpFileInfoTests)
