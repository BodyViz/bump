//
//	FileInfoTest.cpp
//	Bump
//
//	Created by Christian Noon on 12/7/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/foreach.hpp>

// Bump headers
#include <bump/Environment.h>
#include <bump/Exception.h>
#include <bump/FileInfo.h>
#include <bump/FileSystem.h>
#include <bump/String.h>

// bumpTest headers
#include "../bumpTest/BaseTest.h"

// C++ headers
#include <fstream>

namespace bumpTest {

/**
 * This is our main file info testing class. The SetUp and TearDown methods are
 * executed before the test runs and after it completes. This is where we can
 * add any custom set up for each test without having to add this to "every"
 * test individually.
 */
class FileInfoTest : public BaseTest
{
protected:

	/** Run immediately before a test starts. Starts the timer. */
	void SetUp()
	{
		// Call the parent setup method
		BaseTest::SetUp();

		// Create the following directory structures as relative paths to the executable.
		// This way they aren't hard-coded to any specified computer or file system.
		// - unittest
		//     |- empty
		//     |- empty_symlink -> empty
		//     |- files
		//     |   |- info.xml
		//     |   |- output.txt
		//     |   |- archive.tar.gz
		//     |   |- .hidden_file.txt
		//     |- funky.directory
		//     |- funky.directory_symlink
		//     |- .hidden_directory
		//     |- .hidden_directory_symlink
		//     |- .hidden.funky.directory
		//     |- .hidden.funky.directory_symlink
		//     |- regular_directory
		//     |   |- paper.doc
		//     |   |- help.pdf
		//     |- symlink_directory -> regular_directory
		//     |   |- paper.doc
		//     |   |- help.pdf
		//     |- symlink_files
		//     |   |- output.txt -> ../files/output.txt
		//     |   |- archive.tar.gz -> ../files/archive.tar.gz
		//     |   |- .hidden_symlink.txt -> ../files/.hidden_file.txt

		// Set up the class ivars
		_unittestDirectory = bump::String("unittest");
		_emptyDirectory = bump::String("unittest/empty");
		_emptySymlinkDirectory = bump::String("unittest/empty_symlink");
		_filesDirectory = bump::String("unittest/files");
		_regularDirectory = bump::String("unittest/regular_directory");
		_symlinkDirectory = bump::String("unittest/symlink_directory");
		_symlinkFilesDirectory = bump::String("unittest/symlink_files");

		// unittest
		bump::FileSystem::createDirectory(_unittestDirectory);

		// unittest/empty
		bump::FileSystem::createDirectory(_emptyDirectory);

		// unittest/empty_symlink
		// NOTE: the source is relative to the destination directory
		bump::FileSystem::createSymbolicLink("empty", _emptySymlinkDirectory);

		// unittest/files
		bump::FileSystem::createDirectory(_filesDirectory);
		bump::FileSystem::createFile("unittest/files/output.txt");
		bump::FileSystem::createFile("unittest/files/info.xml");
		bump::FileSystem::createFile("unittest/files/archive.tar.gz");
		bump::FileSystem::createFile("unittest/files/.hidden_file.txt");
		bump::FileSystem::createFile("unittest/files/.hidden_archive.tar.gz");
		bump::FileSystem::createDirectory(_regularDirectory);
		bump::FileSystem::createFile("unittest/regular_directory/paper.doc");
		bump::FileSystem::createFile("unittest/regular_directory/help.pdf");

		// unittest/funky.directory
		bump::FileSystem::createDirectory("unittest/funky.directory");
		bump::FileSystem::createSymbolicLink("funky.directory", "unittest/funky.directory_symlink");

		// unittest/.hidden_directory
		bump::FileSystem::createDirectory("unittest/.hidden_directory");
		bump::FileSystem::createSymbolicLink(".hidden_directory", "unittest/.hidden_directory_symlink");

		// unittest/.hidden.funky.directory
		bump::FileSystem::createDirectory("unittest/.hidden.funky.directory");
		bump::FileSystem::createSymbolicLink(".hidden.funky.directory", "unittest/.hidden.funky.directory_symlink");

		// unittest/symlink_directory
		// NOTE: the source is relative to the destination directory
		bump::FileSystem::createSymbolicLink("regular_directory", _symlinkDirectory);

		// unittest/symlink_files
		// NOTE: the source is relative to the destination directory
		bump::FileSystem::createDirectory(_symlinkFilesDirectory);
		bump::FileSystem::createSymbolicLink("../files/info.xml", "unittest/symlink_files/info.xml");
		bump::FileSystem::createSymbolicLink("../files/output.txt", "unittest/symlink_files/output.txt");
		bump::FileSystem::createSymbolicLink("../files/archive.tar.gz", "unittest/symlink_files/archive.tar.gz");
		bump::FileSystem::createSymbolicLink("../files/.hidden_file.txt", "unittest/symlink_files/.hidden_file.txt");
		bump::FileSystem::createSymbolicLink("../files/.hidden_file.txt", "unittest/symlink_files/.hidden_archive.tar.gz");

		// Inject some text into info.xml
		std::ofstream stream("unittest/files/info.xml");
		bump::String xml_text = ("<nodes>"
								 "    <node>"
								 "        <name>Testing</name>"
								 "    </node>"
								 "    <node>"
								 "         <name>Again</name>"
								 "    </node>"
								 "</nodes>");
		stream << xml_text << std::endl;
		stream.close();
	}

	/** Invoked immediately after a test finishes. Stops the timer. */
	void TearDown()
	{
		// Call the parent tear down method
		BaseTest::TearDown();

		// Remove the entire directory structure that was built
		bump::FileSystem::removeDirectoryAndContents("unittest");
	}

	/** Instance member variables. */
	bump::String _unittestDirectory;
	bump::String _emptyDirectory;
	bump::String _emptySymlinkDirectory;
	bump::String _filesDirectory;
	bump::String _regularDirectory;
	bump::String _symlinkDirectory;
	bump::String _symlinkFilesDirectory;
	bump::String _currentPath;
};

TEST_F(FileInfoTest, testExists)
{
	// Test valid directories
	EXPECT_TRUE(bump::FileInfo(_unittestDirectory).exists());
	EXPECT_TRUE(bump::FileInfo(_filesDirectory).exists());
	EXPECT_TRUE(bump::FileInfo(_regularDirectory).exists());
	EXPECT_TRUE(bump::FileInfo(_symlinkFilesDirectory).exists());

	// Test valid directory symlinks
	EXPECT_TRUE(bump::FileInfo(_symlinkDirectory).exists());

	// Test valid files
	EXPECT_TRUE(bump::FileInfo("unittest/files/output.txt").exists());
	EXPECT_TRUE(bump::FileInfo("unittest/files/archive.tar.gz").exists());
	EXPECT_TRUE(bump::FileInfo("unittest/files/.hidden_file.txt").exists());
	EXPECT_TRUE(bump::FileInfo("unittest/regular_directory/paper.doc").exists());
	EXPECT_TRUE(bump::FileInfo("unittest/regular_directory/help.pdf").exists());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_directory/paper.doc").exists());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_directory/help.pdf").exists());

	// Test valid file symlinks
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/output.txt").exists());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/archive.tar.gz").exists());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/.hidden_file.txt").exists());

	// Test invalid directories
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist").exists());
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist/files").exists());
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist/regular").exists());

	// Test invalid directory symlinks
	EXPECT_FALSE(bump::FileInfo("unittest_nope/symlink_directory").exists());
	EXPECT_FALSE(bump::FileInfo("unittest/nope_symlink_files").exists());

	// Test invalid files
	EXPECT_FALSE(bump::FileInfo("unittest/files/nope_output.txt").exists());
	EXPECT_FALSE(bump::FileInfo("unittest/files/.nope_hidden_file.txt").exists());

	// Test invalid file symlinks
	EXPECT_FALSE(bump::FileInfo("unittest/not_a_directory/paper.doc").exists());
	EXPECT_FALSE(bump::FileInfo("unittest/not_a_directory/help.pdf").exists());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/nope_output.txt").exists());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/nope_archive.tar.gz").exists());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/.nope_hidden_file.txt").exists());

	// Test empty use case
	EXPECT_FALSE(bump::FileInfo("").exists());
}

TEST_F(FileInfoTest, testFileSize)
{
	// Test valid files
	EXPECT_EQ(0, bump::FileInfo("unittest/files/output.txt").fileSize());
	EXPECT_EQ(113, bump::FileInfo("unittest/files/info.xml").fileSize());

	// Test valid file symlinks
	EXPECT_EQ(0, bump::FileInfo("unittest/symlink_files/output.txt").fileSize());
	EXPECT_EQ(113, bump::FileInfo("unittest/symlink_files/info.xml").fileSize());

	// Test valid directories
	EXPECT_THROW(bump::FileInfo("unittest/files").fileSize(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/symlink_files").fileSize(), bump::FileSystemError);

	// Test valid directory symlink
	EXPECT_THROW(bump::FileInfo("unittest/symlink_directory").fileSize(), bump::FileSystemError);

	// Test invalid paths
	EXPECT_THROW(bump::FileInfo("unittest/does/not/exist/output.txt").fileSize(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/try/again").fileSize(), bump::FileSystemError);
}

TEST_F(FileInfoTest, testIsAbsolute)
{
	// Test some relative files
	EXPECT_FALSE(bump::FileInfo("unittest/files/output.txt").isAbsolute());
	EXPECT_FALSE(bump::FileInfo("unittest/files/archive.tar.gz").isAbsolute());

	// Test some relative directories
	EXPECT_FALSE(bump::FileInfo("unittest/files").isAbsolute());
	EXPECT_FALSE(bump::FileInfo("unittest/regular_directory").isAbsolute());

	// Test some relative symlinks
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/output.txt").isAbsolute());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/output.txt").isAbsolute());

	// Test some absolute files
	bump::FileInfo info(bump::FileInfo("unittest/files/output.txt").absolutePath());
	EXPECT_TRUE(info.isAbsolute());
	info = bump::FileInfo(bump::FileInfo("unittest/files/output.txt").absolutePath());
	EXPECT_TRUE(info.isAbsolute());

	// Test some absolute directories
	info = bump::FileInfo(bump::FileInfo("unittest/files").absolutePath());
	EXPECT_TRUE(info.isAbsolute());
	info = bump::FileInfo(bump::FileInfo("unittest/regular_directory").absolutePath());
	EXPECT_TRUE(info.isAbsolute());

	// Test some absolute symlinks
	info = bump::FileInfo(bump::FileInfo("unittest/symlink_files/output.txt").absolutePath());
	EXPECT_TRUE(info.isAbsolute());
	info = bump::FileInfo(bump::FileInfo("unittest/symlink_files/output.txt").absolutePath());
	EXPECT_TRUE(info.isAbsolute());

	// Test some invalid relative paths
	EXPECT_FALSE(bump::FileInfo("unittest/does/not/exist/output.txt").isAbsolute());
	EXPECT_FALSE(bump::FileInfo("unittest/try/again").isAbsolute());
}

TEST_F(FileInfoTest, testIsRelative)
{
	// Test some relative files
	EXPECT_TRUE(bump::FileInfo("unittest/files/output.txt").isRelative());
	EXPECT_TRUE(bump::FileInfo("unittest/files/archive.tar.gz").isRelative());

	// Test some relative directories
	EXPECT_TRUE(bump::FileInfo("unittest/files").isRelative());
	EXPECT_TRUE(bump::FileInfo("unittest/regular_directory").isRelative());

	// Test some relative symlinks
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/output.txt").isRelative());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/output.txt").isRelative());

	// Test some absolute files
	bump::FileInfo info(bump::FileInfo("unittest/files/output.txt").isRelative());
	EXPECT_FALSE(info.isAbsolute());
	info = bump::FileInfo(bump::FileInfo("unittest/files/output.txt").isRelative());
	EXPECT_FALSE(info.isAbsolute());

	// Test some absolute directories
	info = bump::FileInfo(bump::FileInfo("unittest/files").isRelative());
	EXPECT_FALSE(info.isAbsolute());
	info = bump::FileInfo(bump::FileInfo("unittest/regular_directory").isRelative());
	EXPECT_FALSE(info.isAbsolute());

	// Test some absolute symlinks
	info = bump::FileInfo(bump::FileInfo("unittest/symlink_files/output.txt").isRelative());
	EXPECT_FALSE(info.isAbsolute());
	info = bump::FileInfo(bump::FileInfo("unittest/symlink_files/output.txt").isRelative());
	EXPECT_FALSE(info.isAbsolute());

	// Test some invalid relative paths
	EXPECT_TRUE(bump::FileInfo("unittest/does/not/exist/output.txt").isRelative());
	EXPECT_TRUE(bump::FileInfo("unittest/try/again").isRelative());
}

TEST_F(FileInfoTest, testIsDirectory)
{
	// Test valid directories
	EXPECT_TRUE(bump::FileInfo(_unittestDirectory).isDirectory());
	EXPECT_TRUE(bump::FileInfo(_filesDirectory).isDirectory());
	EXPECT_TRUE(bump::FileInfo(_regularDirectory).isDirectory());
	EXPECT_TRUE(bump::FileInfo(_symlinkFilesDirectory).isDirectory());

	// Test valid directory symlinks
	EXPECT_TRUE(bump::FileInfo(_symlinkDirectory).isDirectory());

	// Test files
	EXPECT_FALSE(bump::FileInfo("unittest/files/output.txt").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/files/archive.tar.gz").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/files/.hidden_file.txt").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/regular_directory/paper.doc").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/regular_directory/help.pdf").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_directory/paper.doc").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_directory/help.pdf").isDirectory());

	// Test file symlinks
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/output.txt").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/archive.tar.gz").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/.hidden_file.txt").isDirectory());

	// Test invalid directories
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist/files").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist/regular").isDirectory());

	// Test invalid directory symlinks
	EXPECT_FALSE(bump::FileInfo("unittest_nope/symlink_directory").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/nope_symlink_files").isDirectory());

	// Test invalid files
	EXPECT_FALSE(bump::FileInfo("unittest/files/nope_output.txt").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/files/.nope_hidden_file.txt").isDirectory());

	// Test invalid file symlinks
	EXPECT_FALSE(bump::FileInfo("unittest/not_a_directory/paper.doc").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/not_a_directory/help.pdf").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/nope_output.txt").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/nope_archive.tar.gz").isDirectory());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/.nope_hidden_file.txt").isDirectory());

	// Test empty use case
	EXPECT_FALSE(bump::FileInfo("").isDirectory());
}

TEST_F(FileInfoTest, testIsFile)
{
	// Test valid directories
	EXPECT_FALSE(bump::FileInfo(_unittestDirectory).isFile());
	EXPECT_FALSE(bump::FileInfo(_filesDirectory).isFile());
	EXPECT_FALSE(bump::FileInfo(_regularDirectory).isFile());
	EXPECT_FALSE(bump::FileInfo(_symlinkFilesDirectory).isFile());

	// Test valid directory symlinks
	EXPECT_FALSE(bump::FileInfo(_symlinkDirectory).isFile());

	// Test files
	EXPECT_TRUE(bump::FileInfo("unittest/files/output.txt").isFile());
	EXPECT_TRUE(bump::FileInfo("unittest/files/archive.tar.gz").isFile());
	EXPECT_TRUE(bump::FileInfo("unittest/files/.hidden_file.txt").isFile());
	EXPECT_TRUE(bump::FileInfo("unittest/regular_directory/paper.doc").isFile());
	EXPECT_TRUE(bump::FileInfo("unittest/regular_directory/help.pdf").isFile());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_directory/paper.doc").isFile());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_directory/help.pdf").isFile());

	// Test file symlinks
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/output.txt").isFile());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/archive.tar.gz").isFile());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/.hidden_file.txt").isFile());

	// Test invalid directories
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist").isFile());
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist/files").isFile());
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist/regular").isFile());

	// Test invalid directory symlinks
	EXPECT_FALSE(bump::FileInfo("unittest_nope/symlink_directory").isFile());
	EXPECT_FALSE(bump::FileInfo("unittest/nope_symlink_files").isFile());

	// Test invalid files
	EXPECT_FALSE(bump::FileInfo("unittest/files/nope_output.txt").isFile());
	EXPECT_FALSE(bump::FileInfo("unittest/files/.nope_hidden_file.txt").isFile());

	// Test invalid file symlinks
	EXPECT_FALSE(bump::FileInfo("unittest/not_a_directory/paper.doc").isFile());
	EXPECT_FALSE(bump::FileInfo("unittest/not_a_directory/help.pdf").isFile());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/nope_output.txt").isFile());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/nope_archive.tar.gz").isFile());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/.nope_hidden_file.txt").isFile());

	// Test empty use case
	EXPECT_FALSE(bump::FileInfo("").isFile());
}

TEST_F(FileInfoTest, testIsSymbolicLink)
{
	// Test valid directories
	EXPECT_FALSE(bump::FileInfo(_unittestDirectory).isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo(_filesDirectory).isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo(_regularDirectory).isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo(_symlinkFilesDirectory).isSymbolicLink());

	// Test valid directory symlinks
	EXPECT_TRUE(bump::FileInfo(_symlinkDirectory).isSymbolicLink());

	// Test files
	EXPECT_FALSE(bump::FileInfo("unittest/files/output.txt").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/files/archive.tar.gz").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/files/.hidden_file.txt").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/regular_directory/paper.doc").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/regular_directory/help.pdf").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_directory/paper.doc").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_directory/help.pdf").isSymbolicLink());

	// Test file symlinks
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/output.txt").isSymbolicLink());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/archive.tar.gz").isSymbolicLink());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/.hidden_file.txt").isSymbolicLink());

	// Test invalid directories
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist/files").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest_does_not_exist/regular").isSymbolicLink());

	// Test invalid directory symlinks
	EXPECT_FALSE(bump::FileInfo("unittest_nope/symlink_directory").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/nope_symlink_files").isSymbolicLink());

	// Test invalid files
	EXPECT_FALSE(bump::FileInfo("unittest/files/nope_output.txt").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/files/.nope_hidden_file.txt").isSymbolicLink());

	// Test invalid file symlinks
	EXPECT_FALSE(bump::FileInfo("unittest/not_a_directory/paper.doc").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/not_a_directory/help.pdf").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/nope_output.txt").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/nope_archive.tar.gz").isSymbolicLink());
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/.nope_hidden_file.txt").isSymbolicLink());

	// Test empty use case
	EXPECT_FALSE(bump::FileInfo("").isSymbolicLink());
}

TEST_F(FileInfoTest, testIsEmpty)
{
	// Test non-empty file
	EXPECT_FALSE(bump::FileInfo("unittest/files/info.xml").isEmpty());

	// Test empty file
	EXPECT_TRUE(bump::FileInfo("unittest/files/output.txt").isEmpty());

	// Test non-empty directory
	EXPECT_FALSE(bump::FileInfo("unittest/files").isEmpty());

	// Test empty directory
	EXPECT_TRUE(bump::FileInfo(_emptyDirectory).isEmpty());

	// Test non-empty file symlink
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/info.xml").isEmpty());

	// Test empty file symlink
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/output.txt").isEmpty());

	// Test non-empty directory symlink
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_directory").isEmpty());

	// Test empty directory symlink
	EXPECT_TRUE(bump::FileInfo("unittest/empty_symlink").isEmpty());

	// Test invalid path
	EXPECT_THROW(bump::FileInfo("unittest/not/valid").isEmpty(), bump::FileSystemError);

	// Test unreadable permissions non-empty file (still works properly on files)
	EXPECT_TRUE(bump::FileSystem::setPermissions("unittest/files/info.xml", 0));
	EXPECT_FALSE(bump::FileInfo("unittest/files/info.xml").isEmpty());
	EXPECT_TRUE(bump::FileSystem::setPermissions("unittest/files/info.xml", bump::FileSystem::ALL_ALL));

	// Test unreadable permissions empty file (still works properly on files)
	EXPECT_TRUE(bump::FileSystem::setPermissions("unittest/files/output.txt", 0));
	EXPECT_TRUE(bump::FileInfo("unittest/files/output.txt").isEmpty());
	EXPECT_TRUE(bump::FileSystem::setPermissions("unittest/files/output.txt", bump::FileSystem::ALL_ALL));

	// Test unreadable permissions directory
	EXPECT_TRUE(bump::FileSystem::setPermissions("unittest/files", 0));
	EXPECT_THROW(bump::FileInfo("unittest/files").isEmpty(), bump::FileSystemError);
	EXPECT_TRUE(bump::FileSystem::setPermissions("unittest/files", bump::FileSystem::ALL_ALL));

	// Test invalid paths
	EXPECT_THROW(bump::FileInfo("unittest/not/valid/output.txt").isEmpty(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/not/valid").isEmpty(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("").isEmpty(), bump::FileSystemError);
}

TEST_F(FileInfoTest, testIsHidden)
{
	// Test file
	EXPECT_FALSE(bump::FileInfo("unittest/files/output.txt").isHidden());

	// Test hidden file
	EXPECT_TRUE(bump::FileInfo("unittest/files/.hidden_file.txt").isHidden());

	// Test file symlink
	EXPECT_FALSE(bump::FileInfo("unittest/symlink_files/output.txt").isHidden());

	// Test hidden file symlink
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/.hidden_file.txt").isHidden());

	// Test directory
	EXPECT_FALSE(bump::FileInfo("unittest/files").isHidden());

	// Test hidden directory
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/.hidden_files"));
	EXPECT_TRUE(bump::FileInfo("unittest/.hidden_files").isHidden());

	// Test directory symlink
	EXPECT_FALSE(bump::FileInfo("unittest/empty_symlink").isHidden());

	// Test hidden directory symlink
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(".hidden_files", "unittest/.hidden_files_symlink"));
	EXPECT_TRUE(bump::FileInfo("unittest/.hidden_files_symlink").isHidden());

	// Test invalid paths
	EXPECT_FALSE(bump::FileInfo("unittest/not/valid/output.txt").isHidden());
	EXPECT_FALSE(bump::FileInfo("unittest/not/valid").isHidden());
	EXPECT_FALSE(bump::FileInfo("").isHidden());
}

TEST_F(FileInfoTest, testAbsolutePath)
{
	// Test file
	bump::String abs_path = bump::FileInfo("unittest/files/output.txt").absolutePath();
	EXPECT_FALSE(abs_path.isEmpty());
	bump::String expected_abs_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "unittest/files/output.txt");
	EXPECT_STREQ(expected_abs_path.c_str(), abs_path.c_str());

	// Test file symlink
	abs_path = bump::FileInfo("unittest/symlink_files/output.txt").absolutePath();
	EXPECT_FALSE(abs_path.isEmpty());
	expected_abs_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "unittest/symlink_files/output.txt");
	EXPECT_STREQ(expected_abs_path.c_str(), abs_path.c_str());

	// Test directory
	abs_path = bump::FileInfo("unittest/files").absolutePath();
	EXPECT_FALSE(abs_path.isEmpty());
	expected_abs_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "unittest/files");
	EXPECT_STREQ(expected_abs_path.c_str(), abs_path.c_str());

	// Test directory symlink
	abs_path = bump::FileInfo("unittest/symlink_directory").absolutePath();
	EXPECT_FALSE(abs_path.isEmpty());
	expected_abs_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "unittest/symlink_directory");
	EXPECT_STREQ(expected_abs_path.c_str(), abs_path.c_str());

	// Test invalid paths (passes since the path is never resolved)
	abs_path = bump::FileInfo("unittest/not/valid/output.txt").absolutePath();
	EXPECT_FALSE(abs_path.isEmpty());
	expected_abs_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "unittest/not/valid/output.txt");
	EXPECT_STREQ(expected_abs_path.c_str(), abs_path.c_str());

	abs_path = bump::FileInfo("unittest/not/valid").absolutePath();
	EXPECT_FALSE(abs_path.isEmpty());
	expected_abs_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "unittest/not/valid");
	EXPECT_STREQ(expected_abs_path.c_str(), abs_path.c_str());

	abs_path = bump::FileInfo("").absolutePath();
	EXPECT_FALSE(abs_path.isEmpty());
	expected_abs_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "");
	EXPECT_STREQ(expected_abs_path.c_str(), abs_path.c_str());
}

TEST_F(FileInfoTest, testCanonicalPath)
{
	// Test file
	bump::String canonical_path = bump::FileInfo("unittest/files/output.txt").canonicalPath();
	EXPECT_FALSE(canonical_path.isEmpty());
	bump::String expected_canonical_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "unittest/files/output.txt");
	EXPECT_STREQ(expected_canonical_path.c_str(), canonical_path.c_str());

	// Test file symlink
	canonical_path = bump::FileInfo("unittest/symlink_files/output.txt").canonicalPath();
	EXPECT_FALSE(canonical_path.isEmpty());
	expected_canonical_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "unittest/files/output.txt");
	EXPECT_STREQ(expected_canonical_path.c_str(), canonical_path.c_str());

	// Test directory
	canonical_path = bump::FileInfo("unittest/files").canonicalPath();
	EXPECT_FALSE(canonical_path.isEmpty());
	expected_canonical_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "unittest/files");
	EXPECT_STREQ(expected_canonical_path.c_str(), canonical_path.c_str());

	// Test directory symlink
	canonical_path = bump::FileInfo("unittest/symlink_directory").canonicalPath();
	EXPECT_FALSE(canonical_path.isEmpty());
	expected_canonical_path = bump::FileSystem::join(bump::FileSystem::currentPath(), "unittest/regular_directory");
	EXPECT_STREQ(expected_canonical_path.c_str(), canonical_path.c_str());

	// Test invalid paths (passes since the path is never resolved)
	EXPECT_THROW(bump::FileInfo("unittest/not/valid/output.txt").canonicalPath(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/not/valid").canonicalPath(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("").canonicalPath(), bump::FileSystemError);
}

TEST_F(FileInfoTest, testParentPath)
{
	// Test file
	bump::String parent_path = bump::FileInfo("unittest/files/output.txt").parentPath();
	EXPECT_FALSE(parent_path.isEmpty());
	EXPECT_STREQ("unittest/files", parent_path.c_str());

	// Test file symlink
	parent_path = bump::FileInfo("unittest/symlink_files/output.txt").parentPath();
	EXPECT_FALSE(parent_path.isEmpty());
	EXPECT_STREQ("unittest/symlink_files", parent_path.c_str());

	// Test directory
	parent_path = bump::FileInfo("unittest/files").parentPath();
	EXPECT_FALSE(parent_path.isEmpty());
	EXPECT_STREQ("unittest", parent_path.c_str());

	// Test directory symlink
	parent_path = bump::FileInfo("unittest/symlink_directory").parentPath();
	EXPECT_FALSE(parent_path.isEmpty());
	EXPECT_STREQ("unittest", parent_path.c_str());

	// Test invalid paths (passes since the path is never resolved)
	parent_path = bump::FileInfo("unittest/not/valid/output.txt").parentPath();
	EXPECT_FALSE(parent_path.isEmpty());
	EXPECT_STREQ("unittest/not/valid", parent_path.c_str());

	parent_path = bump::FileInfo("unittest/not/valid").parentPath();
	EXPECT_FALSE(parent_path.isEmpty());
	EXPECT_STREQ("unittest/not", parent_path.c_str());

	parent_path = bump::FileInfo("").parentPath();
	EXPECT_TRUE(parent_path.isEmpty());
	EXPECT_STREQ("", parent_path.c_str());
}

TEST_F(FileInfoTest, testBasename)
{
	// Test regular filename file
	bump::String basename = bump::FileInfo("unittest/files/output.txt").basename();
	EXPECT_STREQ("output", basename.c_str());

	// Test compound filename file
	basename = bump::FileInfo("unittest/files/archive.tar.gz").basename();
	EXPECT_STREQ("archive", basename.c_str());

	// Test hidden filename file
	basename = bump::FileInfo("unittest/files/.hidden_file.txt").basename();
	EXPECT_STREQ(".hidden_file", basename.c_str());

	// Test compound hidden filename file
	basename = bump::FileInfo("unittest/files/.archive.tar.gz").basename();
	EXPECT_STREQ(".archive", basename.c_str());

	// Test regular filename directory
	basename = bump::FileInfo("unittest/files").basename();
	EXPECT_STREQ("files", basename.c_str());

	// Test compound filename directory
	basename = bump::FileInfo("unittest/funky.directory").basename();
	EXPECT_STREQ("funky.directory", basename.c_str());

	// Test hidden filename directory
	basename = bump::FileInfo("unittest/.hidden_directory").basename();
	EXPECT_STREQ(".hidden_directory", basename.c_str());

	// Test compound hidden filename directory
	basename = bump::FileInfo("unittest/.hidden.funky.directory").basename();
	EXPECT_STREQ(".hidden.funky.directory", basename.c_str());

	// Test regular filename file symlink
	basename = bump::FileInfo("unittest/symlink_files/output.txt").basename();
	EXPECT_STREQ("output", basename.c_str());

	// Test compound filename file symlink
	basename = bump::FileInfo("unittest/symlink_files/archive.tar.gz").basename();
	EXPECT_STREQ("archive", basename.c_str());

	// Test hidden filename file symlink
	basename = bump::FileInfo("unittest/symlink_files/.hidden_file.txt").basename();
	EXPECT_STREQ(".hidden_file", basename.c_str());

	// Test compound hidden filename file symlink
	basename = bump::FileInfo("unittest/symlink_files/.archive.tar.gz").basename();
	EXPECT_STREQ(".archive", basename.c_str());

	// Test regular filename directory symlink
	basename = bump::FileInfo("unittest/empty_symlink").basename();
	EXPECT_STREQ("empty_symlink", basename.c_str());

	// Test compound filename directory symlink
	basename = bump::FileInfo("unittest/funky.directory_symlink").basename();
	EXPECT_STREQ("funky.directory_symlink", basename.c_str());

	// Test hidden filename directory symlink
	basename = bump::FileInfo("unittest/.hidden_directory_symlink").basename();
	EXPECT_STREQ(".hidden_directory_symlink", basename.c_str());

	// Test compound hidden filename directory symlink
	basename = bump::FileInfo("unittest/.hidden.funky.directory_symlink").basename();
	EXPECT_STREQ(".hidden.funky.directory_symlink", basename.c_str());

	// Test an invalid file with an extension
	basename = bump::FileInfo("unittest/files/invalid.doc").basename();
	EXPECT_STREQ("invalid", basename.c_str());

	// Test an invalid file without an extension
	basename = bump::FileInfo("unittest/files/invalid").basename();
	EXPECT_STREQ("invalid", basename.c_str());

	// Test empty path
	basename = bump::FileInfo("").basename();
	EXPECT_STREQ("", basename.c_str());
}

TEST_F(FileInfoTest, testCompleteBasename)
{
	// Test regular filename file
	bump::String complete_basename = bump::FileInfo("unittest/files/output.txt").completeBasename();
	EXPECT_STREQ("output", complete_basename.c_str());

	// Test compound filename file
	complete_basename = bump::FileInfo("unittest/files/archive.tar.gz").completeBasename();
	EXPECT_STREQ("archive.tar", complete_basename.c_str());

	// Test hidden filename file
	complete_basename = bump::FileInfo("unittest/files/.hidden_file.txt").completeBasename();
	EXPECT_STREQ(".hidden_file", complete_basename.c_str());

	// Test compound hidden filename file
	complete_basename = bump::FileInfo("unittest/files/.archive.tar.gz").completeBasename();
	EXPECT_STREQ(".archive.tar", complete_basename.c_str());

	// Test regular filename directory
	complete_basename = bump::FileInfo("unittest/files").completeBasename();
	EXPECT_STREQ("files", complete_basename.c_str());

	// Test compound filename directory
	complete_basename = bump::FileInfo("unittest/funky.directory").completeBasename();
	EXPECT_STREQ("funky.directory", complete_basename.c_str());

	// Test hidden filename directory
	complete_basename = bump::FileInfo("unittest/.hidden_directory").completeBasename();
	EXPECT_STREQ(".hidden_directory", complete_basename.c_str());

	// Test compound hidden filename directory
	complete_basename = bump::FileInfo("unittest/.hidden.funky.directory").completeBasename();
	EXPECT_STREQ(".hidden.funky.directory", complete_basename.c_str());

	// Test regular filename file symlink
	complete_basename = bump::FileInfo("unittest/symlink_files/output.txt").completeBasename();
	EXPECT_STREQ("output", complete_basename.c_str());

	// Test compound filename file symlink
	complete_basename = bump::FileInfo("unittest/symlink_files/archive.tar.gz").completeBasename();
	EXPECT_STREQ("archive.tar", complete_basename.c_str());

	// Test hidden filename file symlink
	complete_basename = bump::FileInfo("unittest/symlink_files/.hidden_file.txt").completeBasename();
	EXPECT_STREQ(".hidden_file", complete_basename.c_str());

	// Test compound hidden filename file symlink
	complete_basename = bump::FileInfo("unittest/symlink_files/.archive.tar.gz").completeBasename();
	EXPECT_STREQ(".archive.tar", complete_basename.c_str());

	// Test regular filename directory symlink
	complete_basename = bump::FileInfo("unittest/empty_symlink").completeBasename();
	EXPECT_STREQ("empty_symlink", complete_basename.c_str());

	// Test compound filename directory symlink
	complete_basename = bump::FileInfo("unittest/funky.directory_symlink").completeBasename();
	EXPECT_STREQ("funky.directory_symlink", complete_basename.c_str());

	// Test hidden filename directory symlink
	complete_basename = bump::FileInfo("unittest/.hidden_directory_symlink").completeBasename();
	EXPECT_STREQ(".hidden_directory_symlink", complete_basename.c_str());

	// Test compound hidden filename directory symlink
	complete_basename = bump::FileInfo("unittest/.hidden.funky.directory_symlink").completeBasename();
	EXPECT_STREQ(".hidden.funky.directory_symlink", complete_basename.c_str());

	// Test an invalid file with an extension
	complete_basename = bump::FileInfo("unittest/files/invalid.doc").completeBasename();
	EXPECT_STREQ("invalid", complete_basename.c_str());

	// Test an invalid file without an extension
	complete_basename = bump::FileInfo("unittest/files/invalid").completeBasename();
	EXPECT_STREQ("invalid", complete_basename.c_str());

	// Test empty path
	complete_basename = bump::FileInfo("").completeBasename();
	EXPECT_STREQ("", complete_basename.c_str());
}

TEST_F(FileInfoTest, testExtension)
{
	// Test regular filename file
	bump::String extension = bump::FileInfo("unittest/files/output.txt").extension();
	EXPECT_STREQ("txt", extension.c_str());

	// Test compound filename file
	extension = bump::FileInfo("unittest/files/archive.tar.gz").extension();
	EXPECT_STREQ("gz", extension.c_str());

	// Test hidden filename file
	extension = bump::FileInfo("unittest/files/.hidden_file.txt").extension();
	EXPECT_STREQ("txt", extension.c_str());

	// Test compound hidden filename file
	extension = bump::FileInfo("unittest/files/.archive.tar.gz").extension();
	EXPECT_STREQ("gz", extension.c_str());

	// Test regular filename directory
	extension = bump::FileInfo("unittest/files").extension();
	EXPECT_STREQ("", extension.c_str());

	// Test compound filename directory
	extension = bump::FileInfo("unittest/funky.directory").extension();
	EXPECT_STREQ("", extension.c_str());

	// Test hidden filename directory
	extension = bump::FileInfo("unittest/.hidden_directory").extension();
	EXPECT_STREQ("", extension.c_str());

	// Test compound hidden filename directory
	extension = bump::FileInfo("unittest/.hidden.funky.directory").extension();
	EXPECT_STREQ("", extension.c_str());

	// Test regular filename file symlink
	extension = bump::FileInfo("unittest/symlink_files/output.txt").extension();
	EXPECT_STREQ("txt", extension.c_str());

	// Test compound filename file symlink
	extension = bump::FileInfo("unittest/symlink_files/archive.tar.gz").extension();
	EXPECT_STREQ("gz", extension.c_str());

	// Test hidden filename file symlink
	extension = bump::FileInfo("unittest/symlink_files/.hidden_file.txt").extension();
	EXPECT_STREQ("txt", extension.c_str());

	// Test compound hidden filename file symlink
	extension = bump::FileInfo("unittest/symlink_files/.archive.tar.gz").extension();
	EXPECT_STREQ("gz", extension.c_str());

	// Test regular filename directory symlink
	extension = bump::FileInfo("unittest/empty_symlink").extension();
	EXPECT_STREQ("", extension.c_str());

	// Test compound filename directory symlink
	extension = bump::FileInfo("unittest/funky.directory_symlink").extension();
	EXPECT_STREQ("", extension.c_str());

	// Test hidden filename directory symlink
	extension = bump::FileInfo("unittest/.hidden_directory_symlink").extension();
	EXPECT_STREQ("", extension.c_str());

	// Test compound hidden filename directory symlink
	extension = bump::FileInfo("unittest/.hidden.funky.directory_symlink").extension();
	EXPECT_STREQ("", extension.c_str());

	// Test an invalid file with an extension
	extension = bump::FileInfo("unittest/files/invalid.doc").extension();
	EXPECT_STREQ("doc", extension.c_str());

	// Test an invalid file without an extension
	extension = bump::FileInfo("unittest/files/invalid").extension();
	EXPECT_STREQ("", extension.c_str());

	// Test empty path
	extension = bump::FileInfo("").extension();
	EXPECT_STREQ("", extension.c_str());
}

TEST_F(FileInfoTest, testCompleteExtension)
{
	// Test regular filename file
	bump::String complete_extension = bump::FileInfo("unittest/files/output.txt").completeExtension();
	EXPECT_STREQ("txt", complete_extension.c_str());

	// Test compound filename file
	complete_extension = bump::FileInfo("unittest/files/archive.tar.gz").completeExtension();
	EXPECT_STREQ("tar.gz", complete_extension.c_str());

	// Test hidden filename file
	complete_extension = bump::FileInfo("unittest/files/.hidden_file.txt").completeExtension();
	EXPECT_STREQ("txt", complete_extension.c_str());

	// Test compound hidden filename file
	complete_extension = bump::FileInfo("unittest/files/.archive.tar.gz").completeExtension();
	EXPECT_STREQ("tar.gz", complete_extension.c_str());

	// Test regular filename directory
	complete_extension = bump::FileInfo("unittest/files").completeExtension();
	EXPECT_STREQ("", complete_extension.c_str());

	// Test compound filename directory
	complete_extension = bump::FileInfo("unittest/funky.directory").completeExtension();
	EXPECT_STREQ("", complete_extension.c_str());

	// Test hidden filename directory
	complete_extension = bump::FileInfo("unittest/.hidden_directory").completeExtension();
	EXPECT_STREQ("", complete_extension.c_str());

	// Test compound hidden filename directory
	complete_extension = bump::FileInfo("unittest/.hidden.funky.directory").completeExtension();
	EXPECT_STREQ("", complete_extension.c_str());

	// Test regular filename file symlink
	complete_extension = bump::FileInfo("unittest/symlink_files/output.txt").completeExtension();
	EXPECT_STREQ("txt", complete_extension.c_str());

	// Test compound filename file symlink
	complete_extension = bump::FileInfo("unittest/symlink_files/archive.tar.gz").completeExtension();
	EXPECT_STREQ("tar.gz", complete_extension.c_str());

	// Test hidden filename file symlink
	complete_extension = bump::FileInfo("unittest/symlink_files/.hidden_file.txt").completeExtension();
	EXPECT_STREQ("txt", complete_extension.c_str());

	// Test compound hidden filename file symlink
	complete_extension = bump::FileInfo("unittest/symlink_files/.archive.tar.gz").completeExtension();
	EXPECT_STREQ("tar.gz", complete_extension.c_str());

	// Test regular filename directory symlink
	complete_extension = bump::FileInfo("unittest/empty_symlink").completeExtension();
	EXPECT_STREQ("", complete_extension.c_str());

	// Test compound filename directory symlink
	complete_extension = bump::FileInfo("unittest/funky.directory_symlink").completeExtension();
	EXPECT_STREQ("", complete_extension.c_str());

	// Test hidden filename directory symlink
	complete_extension = bump::FileInfo("unittest/.hidden_directory_symlink").completeExtension();
	EXPECT_STREQ("", complete_extension.c_str());

	// Test compound hidden filename directory symlink
	complete_extension = bump::FileInfo("unittest/.hidden.funky.directory_symlink").completeExtension();
	EXPECT_STREQ("", complete_extension.c_str());

	// Test an invalid file with an extension
	complete_extension = bump::FileInfo("unittest/files/invalid.doc").completeExtension();
	EXPECT_STREQ("doc", complete_extension.c_str());

	// Test an invalid file without an extension
	complete_extension = bump::FileInfo("unittest/files/invalid").completeExtension();
	EXPECT_STREQ("", complete_extension.c_str());

	// Test empty path
	complete_extension = bump::FileInfo("").completeExtension();
	EXPECT_STREQ("", complete_extension.c_str());
}

TEST_F(FileInfoTest, testFilename)
{
	// Test regular filename file
	bump::String filename = bump::FileInfo("unittest/files/output.txt").filename();
	EXPECT_STREQ("output.txt", filename.c_str());

	// Test compound filename file
	filename = bump::FileInfo("unittest/files/archive.tar.gz").filename();
	EXPECT_STREQ("archive.tar.gz", filename.c_str());

	// Test hidden filename file
	filename = bump::FileInfo("unittest/files/.hidden_file.txt").filename();
	EXPECT_STREQ(".hidden_file.txt", filename.c_str());

	// Test compound hidden filename file
	filename = bump::FileInfo("unittest/files/.archive.tar.gz").filename();
	EXPECT_STREQ(".archive.tar.gz", filename.c_str());

	// Test regular filename directory
	filename = bump::FileInfo("unittest/files").filename();
	EXPECT_STREQ("files", filename.c_str());

	// Test compound filename directory
	filename = bump::FileInfo("unittest/funky.directory").filename();
	EXPECT_STREQ("funky.directory", filename.c_str());

	// Test hidden filename directory
	filename = bump::FileInfo("unittest/.hidden_directory").filename();
	EXPECT_STREQ(".hidden_directory", filename.c_str());

	// Test compound hidden filename directory
	filename = bump::FileInfo("unittest/.hidden.funky.directory").filename();
	EXPECT_STREQ(".hidden.funky.directory", filename.c_str());

	// Test regular filename file symlink
	filename = bump::FileInfo("unittest/symlink_files/output.txt").filename();
	EXPECT_STREQ("output.txt", filename.c_str());

	// Test compound filename file symlink
	filename = bump::FileInfo("unittest/symlink_files/archive.tar.gz").filename();
	EXPECT_STREQ("archive.tar.gz", filename.c_str());

	// Test hidden filename file symlink
	filename = bump::FileInfo("unittest/symlink_files/.hidden_file.txt").filename();
	EXPECT_STREQ(".hidden_file.txt", filename.c_str());

	// Test compound hidden filename file symlink
	filename = bump::FileInfo("unittest/symlink_files/.archive.tar.gz").filename();
	EXPECT_STREQ(".archive.tar.gz", filename.c_str());

	// Test regular filename directory symlink
	filename = bump::FileInfo("unittest/empty_symlink").filename();
	EXPECT_STREQ("empty_symlink", filename.c_str());

	// Test compound filename directory symlink
	filename = bump::FileInfo("unittest/funky.directory_symlink").filename();
	EXPECT_STREQ("funky.directory_symlink", filename.c_str());

	// Test hidden filename directory symlink
	filename = bump::FileInfo("unittest/.hidden_directory_symlink").filename();
	EXPECT_STREQ(".hidden_directory_symlink", filename.c_str());

	// Test compound hidden filename directory symlink
	filename = bump::FileInfo("unittest/.hidden.funky.directory_symlink").filename();
	EXPECT_STREQ(".hidden.funky.directory_symlink", filename.c_str());

	// Test an invalid file with an extension
	filename = bump::FileInfo("unittest/files/invalid.doc").filename();
	EXPECT_STREQ("invalid.doc", filename.c_str());

	// Test an invalid file without an extension
	filename = bump::FileInfo("unittest/files/invalid").filename();
	EXPECT_STREQ("invalid", filename.c_str());

	// Test empty path
	filename = bump::FileInfo("").filename();
	EXPECT_STREQ("", filename.c_str());
}

TEST_F(FileInfoTest, testIsReadableByUser)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByUser());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByUser());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByUser());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByUser());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByUser());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByUser());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByUser());
}

TEST_F(FileInfoTest, testIsWritableByUser)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByUser());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByUser());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByUser());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByUser());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByUser());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByUser());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByUser());
}

TEST_F(FileInfoTest, testIsExecutableByUser)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByUser());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByUser());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByUser());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByUser());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByUser());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByUser());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByUser());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByUser());
}

TEST_F(FileInfoTest, testIsReadableByOwner)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByOwner());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByOwner());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByOwner());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByOwner());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOwner());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOwner());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOwner());
}

TEST_F(FileInfoTest, testIsWritableByOwner)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByOwner());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByOwner());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByOwner());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByOwner());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOwner());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOwner());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOwner());
}

TEST_F(FileInfoTest, testIsExecutableByOwner)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByOwner());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByOwner());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByOwner());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOwner());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByOwner());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOwner());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOwner());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOwner());
}

TEST_F(FileInfoTest, testIsReadableByGroup)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByGroup());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByGroup());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByGroup());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByGroup());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByGroup());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByGroup());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByGroup());
}

TEST_F(FileInfoTest, testIsWritableByGroup)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByGroup());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByGroup());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByGroup());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByGroup());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByGroup());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByGroup());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByGroup());
}

TEST_F(FileInfoTest, testIsExecutableByGroup)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByGroup());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByGroup());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByGroup());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByGroup());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByGroup());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByGroup());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByGroup());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByGroup());
}

TEST_F(FileInfoTest, testIsReadableByOthers)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByOthers());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByOthers());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByOthers());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isReadableByOthers());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOthers());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOthers());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isReadableByOthers());
}

TEST_F(FileInfoTest, testIsWritableByOthers)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByOthers());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByOthers());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByOthers());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isWritableByOthers());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOthers());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOthers());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isWritableByOthers());
}

TEST_F(FileInfoTest, testIsExecutableByOthers)
{
	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByOthers());

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByOthers());

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByOthers());

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, false));
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOthers());
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, true));
	EXPECT_TRUE(bump::FileInfo(path).isExecutableByOthers());

	// Test invalid paths
	path = "unittest/not/valid/output.txt";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOthers());
	path = "unittest/not/valid";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOthers());
	path = "";
	EXPECT_FALSE(bump::FileInfo(path).isExecutableByOthers());
}

TEST_F(FileInfoTest, testOwner)
{
#ifdef _WIN32

	// On Windows, the owner should always come back empty since this is not implemented yet
	EXPECT_TRUE(bump::FileInfo("unittest/files/output.txt").owner().isEmpty());
	EXPECT_TRUE(bump::FileInfo("unittest/files").owner().isEmpty());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/output.txt").owner().isEmpty());
	EXPECT_TRUE(bump::FileInfo("unittest/empty_symlink").owner().isEmpty());
	EXPECT_TRUE(bump::FileInfo("unittest/not/valid/output.txt").owner().isEmpty());
	EXPECT_TRUE(bump::FileInfo("unittest/not/valid").owner().isEmpty());
	EXPECT_TRUE(bump::FileInfo("").owner().isEmpty());

#else

	// On Unix, compare the owner against the current username

	// Test a file
	bump::String username = bump::Environment::currentUsername();
	bump::String owner = bump::FileInfo("unittest/files/output.txt").owner();
	EXPECT_FALSE(owner.isEmpty());
	EXPECT_STREQ(owner.c_str(), username.c_str());

	// Test a directory
	owner = bump::FileInfo("unittest/files").owner();
	EXPECT_FALSE(owner.isEmpty());
	EXPECT_STREQ(owner.c_str(), username.c_str());

	// Test a file symlink
	owner = bump::FileInfo("unittest/symlink_files/output.txt").owner();
	EXPECT_FALSE(owner.isEmpty());
	EXPECT_STREQ(owner.c_str(), username.c_str());

	// Test a directory symlink
	owner = bump::FileInfo("unittest/empty_symlink").owner();
	EXPECT_FALSE(owner.isEmpty());
	EXPECT_STREQ(owner.c_str(), username.c_str());

	// Test some invalid paths
	EXPECT_THROW(bump::FileInfo("unittest/not/valid/output.txt").owner(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/not/valid").owner(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("").owner(), bump::FileSystemError);

#endif
}

TEST_F(FileInfoTest, testOwnerId)
{
#ifdef _WIN32

	// On Windows, the owner id should always come back as -1 since it's not implemented yet
	EXPECT_EQ(-1, bump::FileInfo("unittest/files/output.txt").ownerId());
	EXPECT_EQ(-1, bump::FileInfo("unittest/files").ownerId());
	EXPECT_EQ(-1, bump::FileInfo("unittest/symlink_files/output.txt").ownerId());
	EXPECT_EQ(-1, bump::FileInfo("unittest/empty_symlink").ownerId());
	EXPECT_EQ(-1, bump::FileInfo("unittest/not/valid/output.txt").ownerId());
	EXPECT_EQ(-1, bump::FileInfo("unittest/not/valid").ownerId());
	EXPECT_EQ(-1, bump::FileInfo("").ownerId());

#else

	// On Unix, the only thing we can do for an owner id is make sure it's greater than or equal to 0

	// Test a file
	unsigned int owner_id = bump::FileInfo("unittest/files/output.txt").ownerId();
	EXPECT_LT(0, owner_id);

	// Test a directory
	owner_id = bump::FileInfo("unittest/files").ownerId();
	EXPECT_LT(0, owner_id);

	// Test a file symlink
	owner_id = bump::FileInfo("unittest/symlink_files/output.txt").ownerId();
	EXPECT_LT(0, owner_id);

	// Test a directory symlink
	owner_id = bump::FileInfo("unittest/empty_symlink").ownerId();
	EXPECT_LT(0, owner_id);

	// Test some invalid paths
	EXPECT_THROW(bump::FileInfo("unittest/not/valid/output.txt").ownerId(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/not/valid").ownerId(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("").ownerId(), bump::FileSystemError);

#endif
}

TEST_F(FileInfoTest, testGroup)
{
#ifdef _WIN32

	// On Windows, the group should always come back empty since this is not implemented yet
	EXPECT_TRUE(bump::FileInfo("unittest/files/output.txt").group().isEmpty());
	EXPECT_TRUE(bump::FileInfo("unittest/files").group().isEmpty());
	EXPECT_TRUE(bump::FileInfo("unittest/symlink_files/output.txt").group().isEmpty());
	EXPECT_TRUE(bump::FileInfo("unittest/empty_symlink").group().isEmpty());
	EXPECT_TRUE(bump::FileInfo("unittest/not/valid/output.txt").group().isEmpty());
	EXPECT_TRUE(bump::FileInfo("unittest/not/valid").group().isEmpty());
	EXPECT_TRUE(bump::FileInfo("").group().isEmpty());

#else

	// On Unix, make sure the group is not empty (all we can do since we can't predict what the group will be)

	// Test a file
	bump::String group = bump::FileInfo("unittest/files/output.txt").group();
	EXPECT_FALSE(group.isEmpty());

	// Test a directory
	group = bump::FileInfo("unittest/files").group();
	EXPECT_FALSE(group.isEmpty());

	// Test a file symlink
	group = bump::FileInfo("unittest/symlink_files/output.txt").group();
	EXPECT_FALSE(group.isEmpty());

	// Test a directory symlink
	group = bump::FileInfo("unittest/empty_symlink").group();
	EXPECT_FALSE(group.isEmpty());

	// Test some invalid paths
	EXPECT_THROW(bump::FileInfo("unittest/not/valid/output.txt").group(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/not/valid").group(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("").group(), bump::FileSystemError);

#endif
}

TEST_F(FileInfoTest, testGroupId)
{
#ifdef _WIN32

	// On Windows, the group id should always come back as -1 since it's not implemented yet
	EXPECT_EQ(-1, bump::FileInfo("unittest/files/output.txt").groupId());
	EXPECT_EQ(-1, bump::FileInfo("unittest/files").groupId());
	EXPECT_EQ(-1, bump::FileInfo("unittest/symlink_files/output.txt").groupId());
	EXPECT_EQ(-1, bump::FileInfo("unittest/empty_symlink").groupId());
	EXPECT_EQ(-1, bump::FileInfo("unittest/not/valid/output.txt").groupId());
	EXPECT_EQ(-1, bump::FileInfo("unittest/not/valid").groupId());
	EXPECT_EQ(-1, bump::FileInfo("").groupId());

#else

	// On Unix, the only thing we can do for a group id is make sure it's greater than or equal to 0

	// Test a file
	unsigned int group_id = bump::FileInfo("unittest/files/output.txt").groupId();
	EXPECT_LT(0, group_id);

	// Test a directory
	group_id = bump::FileInfo("unittest/files").groupId();
	EXPECT_LT(0, group_id);

	// Test a file symlink
	group_id = bump::FileInfo("unittest/symlink_files/output.txt").groupId();
	EXPECT_LT(0, group_id);

	// Test a directory symlink
	group_id = bump::FileInfo("unittest/empty_symlink").groupId();
	EXPECT_LT(0, group_id);

	// Test some invalid paths
	EXPECT_THROW(bump::FileInfo("unittest/not/valid/output.txt").groupId(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/not/valid").groupId(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("").groupId(), bump::FileSystemError);

#endif
}

TEST_F(FileInfoTest, testModifiedDate)
{
	// Create a time object
	std::tm time_obj;
	time_obj.tm_sec = 42;
	time_obj.tm_min = 11;
	time_obj.tm_hour = 21;
	time_obj.tm_mday = 19;
	time_obj.tm_mon = 10;
	time_obj.tm_year = 89;
	time_obj.tm_wday = 3;
	std::time_t time = std::mktime(&time_obj);

	// Test a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setModifiedDate(path, time));
	std::time_t modified_date = bump::FileInfo(path).modifiedDate();
	EXPECT_EQ(time, modified_date);

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setModifiedDate(path, time));
	modified_date = bump::FileInfo(path).modifiedDate();
	EXPECT_EQ(time, modified_date);

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setModifiedDate(path, time));
	modified_date = bump::FileInfo(path).modifiedDate();
	EXPECT_EQ(time, modified_date);

	// Test a directory symlink
	path = "unittest/empty_symlink";
	EXPECT_TRUE(bump::FileSystem::setModifiedDate(path, time));
	modified_date = bump::FileInfo(path).modifiedDate();
	EXPECT_EQ(time, modified_date);
}

}	// End of bumpTest namespace
