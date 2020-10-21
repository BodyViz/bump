//
//	TextFileReaderTest.cpp
//	Bump
//
//  Created by Joseph Holub on 2/1/13.
//  Copyright (c) 2012 Joseph Holub. All rights reserved.
//

// C++ Headers
#include <fstream>

// Bump headers
#include <bump/FileSystem.h>
#include <bump/Log.h>
#include <bump/String.h>
#include <bump/TextFileReader.h>

// bumpTest headers
#include "../bumpTest/BaseTest.h"

namespace bumpTest {

/**
 * This is our main TextFileReader testing class. The SetUp and TearDown methods are
 * executed before the test runs and after it completes. This is where we can
 * add any custom set up for each test without having to add this to "every"
 * test individually.
 */
class TextFileReaderTest : public BaseTest
{
protected:

	/** Run immediately before a test starts. Starts the timer. */
	void SetUp()
	{
		// Call the parent setup method
		BaseTest::SetUp();

		// Set the Log level so no unneccessary information is provided
		bump::Log::instance()->setIsLogEnabled(true);
		_previousLogLevel = bump::Log::instance()->logLevel();
		bump::Log::instance()->setLogLevel(bump::Log::ALWAYS_LVL);

		// Save the current path so we can always put it back after a test modifies it
		_currentPath = bump::FileSystem::currentPath();

		// Create a unitTest Directory for saving files
		_unittestDirectory = bump::String("unittest");
		bump::FileSystem::createDirectory(_unittestDirectory);

		// Create a test txt file to use
		bump::FileSystem::createFile("unittest/unit_test.txt");

		// Set some file names to use throughout this test
		_validFileName = bump::String("unittest/unit_test.txt");
		_invalidFileName = bump::String("unit_test.txt");
		_nonsensicalFileName = bump::String("dsfkh3#$sfd");

		// Add content to the file to be read in.
		std::ofstream unit_file;
		unit_file.open("unittest/unit_test.txt");
		if (unit_file.is_open())
		{
			unit_file << "1: This is the first line\n";
			unit_file << "2: This is the second line\n";
			unit_file << "3: This is the third line\n";
			unit_file << "4: This is the fourth line\n";
			unit_file << "5: This is the fifth line\n";
			unit_file << "6: This is the sixth line\n";
			unit_file << "7: This is the seventh line\n";
			unit_file << "8: This is the eighth line\n";
			unit_file << "9: This is the ninth line\n";
			unit_file << "10: This is the tenth line";
		}
		unit_file.close();
	}

	/** Invoked immediately after a test finishes. Stops the timer. */
	void TearDown()
	{
		// Call the parent tear down method
		BaseTest::TearDown();

		// Put the current path back to what it was originally
		bump::FileSystem::setCurrentPath(_currentPath);

		// Remove the entire directory structure that was built
		bump::FileSystem::removeDirectoryAndContents("unittest");

		// Reset the Log level to what it was before
		bump::Log::instance()->setLogLevel(_previousLogLevel);
	}

	bump::String _currentPath;
	bump::String _unittestDirectory;
	bump::String _validFileName;
	bump::String _invalidFileName;
	bump::String _nonsensicalFileName;
	bump::Log::LogLevel _previousLogLevel;
};

TEST_F(TextFileReaderTest, testValidityOfFile)
{
	// Check if the correct path is passed if we get back a full StringList
	bump::StringList entire_file = bump::TextFileReader::fileContents(_validFileName);
	EXPECT_FALSE(entire_file.empty());
	entire_file = bump::TextFileReader::fileContents(_validFileName, 1, 1);
	EXPECT_FALSE(entire_file.empty());
	entire_file = bump::TextFileReader::fileContents(_validFileName, 1);
	EXPECT_FALSE(entire_file.empty());
	bump::String line = bump::TextFileReader::firstLine(_validFileName);
	EXPECT_STREQ("1: This is the first line", line.toStdString().c_str());
	entire_file = bump::TextFileReader::header (_validFileName, 1);
	EXPECT_FALSE(entire_file.empty());
	entire_file = bump::TextFileReader::footer(_validFileName, 1);
	EXPECT_FALSE(entire_file.empty());
	int numLines = bump::TextFileReader::numberOfLines(_validFileName);
	EXPECT_EQ(10, numLines);

	// Check for the full path being passed in
	bump::String file_path = _currentPath + bump::String("/") + _validFileName;
	entire_file = bump::TextFileReader::fileContents(file_path);
	EXPECT_FALSE(entire_file.empty());
	entire_file = bump::TextFileReader::fileContents(file_path, 1, 1);
	EXPECT_FALSE(entire_file.empty());
	entire_file = bump::TextFileReader::fileContents(file_path, 1);
	EXPECT_FALSE(entire_file.empty());
	line = bump::TextFileReader::firstLine(file_path);
	EXPECT_STREQ("1: This is the first line", line.toStdString().c_str());
	entire_file = bump::TextFileReader::header (file_path, 1);
	EXPECT_FALSE(entire_file.empty());
	entire_file = bump::TextFileReader::footer(file_path, 1);
	EXPECT_FALSE(entire_file.empty());
	numLines = bump::TextFileReader::numberOfLines(file_path);
	EXPECT_EQ(10, numLines);

	// Check if the correct path is not passed and return an empty string
	entire_file = bump::TextFileReader::fileContents(_invalidFileName);
	EXPECT_TRUE(entire_file.empty());
	entire_file = bump::TextFileReader::fileContents(_invalidFileName, 1, 1);
	EXPECT_TRUE(entire_file.empty());
	entire_file = bump::TextFileReader::fileContents(_invalidFileName, 1);
	EXPECT_TRUE(entire_file.empty());
	line = bump::TextFileReader::firstLine(_invalidFileName);
	EXPECT_STREQ("", line.toStdString().c_str());
	entire_file = bump::TextFileReader::header (_invalidFileName, 1);
	EXPECT_TRUE(entire_file.empty());
	entire_file = bump::TextFileReader::footer(_invalidFileName, 1);
	EXPECT_TRUE(entire_file.empty());
	numLines = bump::TextFileReader::numberOfLines(_invalidFileName);
	EXPECT_EQ(-1, numLines);

	// Check if a non-sensical filename is passed in
	entire_file = bump::TextFileReader::fileContents(_nonsensicalFileName);
	EXPECT_TRUE(entire_file.empty());
	entire_file = bump::TextFileReader::fileContents(_nonsensicalFileName, 1, 1);
	EXPECT_TRUE(entire_file.empty());
	entire_file = bump::TextFileReader::fileContents(_nonsensicalFileName, 1);
	EXPECT_TRUE(entire_file.empty());
	line = bump::TextFileReader::firstLine(_nonsensicalFileName);
	EXPECT_STREQ("", line.toStdString().c_str());
	entire_file = bump::TextFileReader::header (_nonsensicalFileName, 1);
	EXPECT_TRUE(entire_file.empty());
	entire_file = bump::TextFileReader::footer(_nonsensicalFileName, 1);
	EXPECT_TRUE(entire_file.empty());
	numLines = bump::TextFileReader::numberOfLines(_nonsensicalFileName);
	EXPECT_EQ(-1, numLines);
}

TEST_F(TextFileReaderTest, testReadEntireFile)
{
	// Test reading the entire file when given an appropriate file path
	bump::StringList entire_file = bump::TextFileReader::fileContents(_validFileName);
	EXPECT_STREQ("1: This is the first line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("2: This is the second line", entire_file.at(1).toStdString().c_str());
	EXPECT_STREQ("3: This is the third line", entire_file.at(2).toStdString().c_str());
	EXPECT_STREQ("4: This is the fourth line", entire_file.at(3).toStdString().c_str());
	EXPECT_STREQ("5: This is the fifth line", entire_file.at(4).toStdString().c_str());
	EXPECT_STREQ("6: This is the sixth line", entire_file.at(5).toStdString().c_str());
	EXPECT_STREQ("7: This is the seventh line", entire_file.at(6).toStdString().c_str());
	EXPECT_STREQ("8: This is the eighth line", entire_file.at(7).toStdString().c_str());
	EXPECT_STREQ("9: This is the ninth line", entire_file.at(8).toStdString().c_str());
	EXPECT_STREQ("10: This is the tenth line", entire_file.at(9).toStdString().c_str());
}

TEST_F(TextFileReaderTest, testReadSubsetOfFile)
{
	// Grab the 2 lines of the file starting at the second line
	bump::StringList entire_file = bump::TextFileReader::fileContents(_validFileName, 2, 2);
	EXPECT_STREQ("2: This is the second line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("3: This is the third line", entire_file.at(1).toStdString().c_str());

	// Entering a negative number in for the beginningLine
	entire_file = bump::TextFileReader::fileContents(_validFileName, -2, 2);
	EXPECT_TRUE(entire_file.empty());

	// Entering a float number in for the beginningLine
	entire_file = bump::TextFileReader::fileContents(_validFileName, 2.999, 2);
	EXPECT_STREQ("2: This is the second line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("3: This is the third line", entire_file.at(1).toStdString().c_str());

	// Entering a float number in for the numLines
	entire_file = bump::TextFileReader::fileContents(_validFileName, 2, 2.999);
	EXPECT_STREQ("2: This is the second line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("3: This is the third line", entire_file.at(1).toStdString().c_str());

	// Request more lines than are left in the file
	entire_file = bump::TextFileReader::fileContents(_validFileName, 5, 6);
	EXPECT_STREQ("5: This is the fifth line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("6: This is the sixth line", entire_file.at(1).toStdString().c_str());
	EXPECT_STREQ("7: This is the seventh line", entire_file.at(2).toStdString().c_str());
	EXPECT_STREQ("8: This is the eighth line", entire_file.at(3).toStdString().c_str());
	EXPECT_STREQ("9: This is the ninth line", entire_file.at(4).toStdString().c_str());
	EXPECT_STREQ("10: This is the tenth line", entire_file.at(5).toStdString().c_str());

	// Request a line that is beyond the limit of the file
	entire_file = bump::TextFileReader::fileContents(_validFileName, 11, 6);
	EXPECT_TRUE(entire_file.empty());
}

TEST_F(TextFileReaderTest, testReadFromLineToEnd)
{
	// Grab the 2 lines of the file starting at the second line
	bump::StringList entire_file = bump::TextFileReader::fileContents(_validFileName, 2);
	EXPECT_STREQ("2: This is the second line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("3: This is the third line", entire_file.at(1).toStdString().c_str());
	EXPECT_STREQ("4: This is the fourth line", entire_file.at(2).toStdString().c_str());
	EXPECT_STREQ("5: This is the fifth line", entire_file.at(3).toStdString().c_str());
	EXPECT_STREQ("6: This is the sixth line", entire_file.at(4).toStdString().c_str());
	EXPECT_STREQ("7: This is the seventh line", entire_file.at(5).toStdString().c_str());
	EXPECT_STREQ("8: This is the eighth line", entire_file.at(6).toStdString().c_str());
	EXPECT_STREQ("9: This is the ninth line", entire_file.at(7).toStdString().c_str());
	EXPECT_STREQ("10: This is the tenth line", entire_file.at(8).toStdString().c_str());

	// Entering a negative number in for the beginningLine
	entire_file = bump::TextFileReader::fileContents(_validFileName, -2);
	EXPECT_TRUE(entire_file.empty());

	// Entering a float number in for the beginningLine
	entire_file = bump::TextFileReader::fileContents(_validFileName, 2.999);
	EXPECT_STREQ("2: This is the second line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("3: This is the third line", entire_file.at(1).toStdString().c_str());
	EXPECT_STREQ("4: This is the fourth line", entire_file.at(2).toStdString().c_str());
	EXPECT_STREQ("5: This is the fifth line", entire_file.at(3).toStdString().c_str());
	EXPECT_STREQ("6: This is the sixth line", entire_file.at(4).toStdString().c_str());
	EXPECT_STREQ("7: This is the seventh line", entire_file.at(5).toStdString().c_str());
	EXPECT_STREQ("8: This is the eighth line", entire_file.at(6).toStdString().c_str());
	EXPECT_STREQ("9: This is the ninth line", entire_file.at(7).toStdString().c_str());
	EXPECT_STREQ("10: This is the tenth line", entire_file.at(8).toStdString().c_str());

	// Request a line that is beyond the limit of the file
	entire_file = bump::TextFileReader::fileContents(_validFileName, 11, 6);
	EXPECT_TRUE(entire_file.empty());
}

TEST_F(TextFileReaderTest, testReadFirstLine)
{
	// With a valid file path, invalids are taken care of in testValidityOfFile()
	bump::String line = bump::TextFileReader::firstLine(_validFileName);
	EXPECT_STREQ("1: This is the first line", line.toStdString().c_str());
}

TEST_F(TextFileReaderTest, testHeader)
{
	// Grab the header of two lines
	bump::StringList entire_file = bump::TextFileReader::header(_validFileName, 2);
	EXPECT_STREQ("1: This is the first line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("2: This is the second line", entire_file.at(1).toStdString().c_str());

	// Entering a negative number in for the numLines
	entire_file = bump::TextFileReader::header(_validFileName, -2);
	EXPECT_TRUE(entire_file.empty());

	// Entering a float number in for the numLines
	entire_file = bump::TextFileReader::header(_validFileName, 2.999);
	EXPECT_STREQ("1: This is the first line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("2: This is the second line", entire_file.at(1).toStdString().c_str());

	// Request a header size larger than the entire file
	entire_file = bump::TextFileReader::header(_validFileName, 11);
	EXPECT_STREQ("1: This is the first line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("2: This is the second line", entire_file.at(1).toStdString().c_str());
	EXPECT_STREQ("3: This is the third line", entire_file.at(2).toStdString().c_str());
	EXPECT_STREQ("4: This is the fourth line", entire_file.at(3).toStdString().c_str());
	EXPECT_STREQ("5: This is the fifth line", entire_file.at(4).toStdString().c_str());
	EXPECT_STREQ("6: This is the sixth line", entire_file.at(5).toStdString().c_str());
	EXPECT_STREQ("7: This is the seventh line", entire_file.at(6).toStdString().c_str());
	EXPECT_STREQ("8: This is the eighth line", entire_file.at(7).toStdString().c_str());
	EXPECT_STREQ("9: This is the ninth line", entire_file.at(8).toStdString().c_str());
	EXPECT_STREQ("10: This is the tenth line", entire_file.at(9).toStdString().c_str());
}

TEST_F(TextFileReaderTest, testFooter)
{
	// Grab the footer of two lines
	bump::StringList entire_file = bump::TextFileReader::footer(_validFileName, 2);
	EXPECT_STREQ("9: This is the ninth line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("10: This is the tenth line", entire_file.at(1).toStdString().c_str());

	// Entering a negative number in for the numLines
	entire_file = bump::TextFileReader::footer(_validFileName, -2);
	EXPECT_TRUE(entire_file.empty());

	// Entering a float number in for the numLines
	entire_file = bump::TextFileReader::footer(_validFileName, 2.999);
	EXPECT_STREQ("9: This is the ninth line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("10: This is the tenth line", entire_file.at(1).toStdString().c_str());

	// Request a header size larger than the entire file
	entire_file = bump::TextFileReader::footer(_validFileName, 11);
	EXPECT_STREQ("1: This is the first line", entire_file.at(0).toStdString().c_str());
	EXPECT_STREQ("2: This is the second line", entire_file.at(1).toStdString().c_str());
	EXPECT_STREQ("3: This is the third line", entire_file.at(2).toStdString().c_str());
	EXPECT_STREQ("4: This is the fourth line", entire_file.at(3).toStdString().c_str());
	EXPECT_STREQ("5: This is the fifth line", entire_file.at(4).toStdString().c_str());
	EXPECT_STREQ("6: This is the sixth line", entire_file.at(5).toStdString().c_str());
	EXPECT_STREQ("7: This is the seventh line", entire_file.at(6).toStdString().c_str());
	EXPECT_STREQ("8: This is the eighth line", entire_file.at(7).toStdString().c_str());
	EXPECT_STREQ("9: This is the ninth line", entire_file.at(8).toStdString().c_str());
	EXPECT_STREQ("10: This is the tenth line", entire_file.at(9).toStdString().c_str());
}

TEST_F(TextFileReaderTest, testNumberOfLines)
{
	// With a valid file path, invalids are taken care of in testValidityOfFile()
	int numLines = bump::TextFileReader::numberOfLines(_validFileName);
	EXPECT_EQ(10, numLines);
}

}	// End of bumpTest namespace
