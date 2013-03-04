
# Add the source files
SET (TARGET_SRC
	../bumpTest/main.cpp
	TextFileReaderTest.cpp
)

# Add the header files
SET (TARGET_H
	../bumpTest/BaseTest.h
	../bumpTest/EnvironmentFixture.h
)

SETUP_TEST (bumpTextFileReaderTests)
