//
//	FileSystemTest.cpp
//	Bump
//
//	Created by Christian Noon on 12/6/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Exception.h>
#include <bump/Filesystem.h>
#include <bump/String.h>

// bumpTest headers
#include "../bumpTest/BaseTest.h"

namespace bumpTest {

/**
 * This is our main file system testing class. The SetUp and TearDown methods are
 * executed before the test runs and after it completes. This is where we can
 * add any custom set up for each test without having to add this to "every"
 * test individually.
 */
class FileSystemTest : public BaseTest
{
protected:

	/** Run immediately before a test starts. Starts the timer. */
	void SetUp()
	{
		// Call the parent setup method
		BaseTest::SetUp();

		// Save the current path so we can always put it back after a test modifies it
		_currentPath = bump::FileSystem::currentPath();

		// Create the following directory structures as relative paths to the executable.
		// This way they aren't hard-coded to any specified computer or file system.
		// - unittest
		//     |- files
		//     |   |- output.txt
		//     |   |- archive.tar.gz
		//     |   |- .hidden_file.txt
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
		_filesDirectory = bump::String("unittest/files");
		_regularDirectory = bump::String("unittest/regular_directory");
		_symlinkDirectory = bump::String("unittest/symlink_directory");
		_symlinkFilesDirectory = bump::String("unittest/symlink_files");

		// unittest
		bump::FileSystem::createDirectory(_unittestDirectory);

		// unittest/files
		bump::FileSystem::createDirectory(_filesDirectory);
		bump::FileSystem::createFile("unittest/files/output.txt");
		bump::FileSystem::createFile("unittest/files/archive.tar.gz");
		bump::FileSystem::createFile("unittest/files/.hidden_file.txt");
		bump::FileSystem::createDirectory(_regularDirectory);
		bump::FileSystem::createFile("unittest/regular_directory/paper.doc");
		bump::FileSystem::createFile("unittest/regular_directory/help.pdf");

		// unittest/symlink_directory
		// NOTE: the source is relative to the destination for directory symlinks
		bump::FileSystem::createSymbolicLink("regular_directory", _symlinkDirectory);

		// unittest/symlink_files
		bump::FileSystem::createDirectory(_symlinkFilesDirectory);
		bump::FileSystem::createSymbolicLink("unittest/files/output.txt", "unittest/symlink_files/output.txt");
		bump::FileSystem::createSymbolicLink("unittest/files/archive.tar.gz", "unittest/symlink_files/archive.tar.gz");
		bump::FileSystem::createSymbolicLink("unittest/files/.hidden_file.txt", "unittest/symlink_files/.hidden_file.txt");
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
	}

	/** Instance member variables. */
	bump::String _unittestDirectory;
	bump::String _filesDirectory;
	bump::String _regularDirectory;
	bump::String _symlinkDirectory;
	bump::String _symlinkFilesDirectory;
	bump::String _currentPath;
};

TEST_F(FileSystemTest, join2)
{
	// Test the default usage
	bump::String joined = bump::FileSystem::join("/home/username", "Desktop");
	EXPECT_STREQ("/home/username/Desktop", joined.c_str());
	joined = bump::FileSystem::join("/", "usr");
	EXPECT_STREQ("/usr", joined.c_str());

	// Test the empty cases
	joined = bump::FileSystem::join("", "usr");
	EXPECT_STREQ("usr", joined.c_str());
	joined = bump::FileSystem::join("/", "");
	EXPECT_STREQ("/", joined.c_str());
	joined = bump::FileSystem::join("", "");
	EXPECT_STREQ("", joined.c_str());

	// Test the cases with extra forward slashes
	joined = bump::FileSystem::join("/home/username/", "Desktop");
	EXPECT_STREQ("/home/username/Desktop", joined.c_str());
	joined = bump::FileSystem::join("/opt/local", "/sbin");
	EXPECT_STREQ("/opt/local/sbin", joined.c_str());

	// Test a case where it can't remove all the slashes
	joined = bump::FileSystem::join("/opt//local/", "/sbin/");
	EXPECT_STREQ("/opt//local//sbin/", joined.c_str());
}

TEST_F(FileSystemTest, join3)
{
	// Test the default usage
	bump::String joined = bump::FileSystem::join("/home", "username", "Desktop");
	EXPECT_STREQ("/home/username/Desktop", joined.c_str());
	joined = bump::FileSystem::join("/", "usr", "/local");
	EXPECT_STREQ("/usr/local", joined.c_str());

	// Test the empty cases
	joined = bump::FileSystem::join("", "usr", "local");
	EXPECT_STREQ("usr/local", joined.c_str());
	joined = bump::FileSystem::join("/", "", "");
	EXPECT_STREQ("/", joined.c_str());
	joined = bump::FileSystem::join("", "", "");
	EXPECT_STREQ("", joined.c_str());

	// Test the cases with extra forward slashes
	joined = bump::FileSystem::join("/home", "/username/", "Desktop");
	EXPECT_STREQ("/home/username/Desktop", joined.c_str());
	joined = bump::FileSystem::join("/opt/", "local", "/sbin");
	EXPECT_STREQ("/opt/local/sbin", joined.c_str());

	// Test a case where it can't remove all the slashes
	joined = bump::FileSystem::join("/opt/", "/local/", "/sbin/");
	EXPECT_STREQ("/opt//local//sbin/", joined.c_str());
}

TEST_F(FileSystemTest, join4)
{
	// Test the default usage
	bump::String joined = bump::FileSystem::join("/", "home", "username", "Desktop");
	EXPECT_STREQ("/home/username/Desktop", joined.c_str());
	joined = bump::FileSystem::join("/", "usr", "/local", "sbin");
	EXPECT_STREQ("/usr/local/sbin", joined.c_str());

	// Test the empty cases
	joined = bump::FileSystem::join("", "usr", "local", "");
	EXPECT_STREQ("usr/local", joined.c_str());
	joined = bump::FileSystem::join("/", "", "", "testing");
	EXPECT_STREQ("/testing", joined.c_str());
	joined = bump::FileSystem::join("", "", "", "");
	EXPECT_STREQ("", joined.c_str());

	// Test the cases with extra forward slashes
	joined = bump::FileSystem::join("/home", "/username/", "Desktop", "/local");
	EXPECT_STREQ("/home/username/Desktop/local", joined.c_str());
	joined = bump::FileSystem::join("/", "opt/", "local", "/sbin");
	EXPECT_STREQ("/opt/local/sbin", joined.c_str());

	// Test a case where it can't remove all the slashes
	joined = bump::FileSystem::join("/", "/opt/", "/local/", "/sbin/");
	EXPECT_STREQ("//opt//local//sbin/", joined.c_str());
}

TEST_F(FileSystemTest, join5)
{
	// Test the default usage
	bump::String joined = bump::FileSystem::join("/", "home", "username", "Desktop", "test");
	EXPECT_STREQ("/home/username/Desktop/test", joined.c_str());
	joined = bump::FileSystem::join("/", "usr", "/local", "sbin", "app");
	EXPECT_STREQ("/usr/local/sbin/app", joined.c_str());

	// Test the empty cases
	joined = bump::FileSystem::join("", "usr", "local", "", "sbin");
	EXPECT_STREQ("usr/local/sbin", joined.c_str());
	joined = bump::FileSystem::join("/", "", "", "testing", "again");
	EXPECT_STREQ("/testing/again", joined.c_str());
	joined = bump::FileSystem::join("", "", "", "", "");
	EXPECT_STREQ("", joined.c_str());

	// Test the cases with extra forward slashes
	joined = bump::FileSystem::join("/home", "/username/", "Desktop", "/local", "app");
	EXPECT_STREQ("/home/username/Desktop/local/app", joined.c_str());
	joined = bump::FileSystem::join("/", "opt/", "local", "/sbin", "app");
	EXPECT_STREQ("/opt/local/sbin/app", joined.c_str());

	// Test a case where it can't remove all the slashes
	joined = bump::FileSystem::join("/", "/opt/", "/local/", "/sbin/", "app/");
	EXPECT_STREQ("//opt//local//sbin/app/", joined.c_str());
}

TEST_F(FileSystemTest, join6)
{
	// Test the default usage
	bump::String joined = bump::FileSystem::join("/", "home", "username", "Desktop", "test", "default");
	EXPECT_STREQ("/home/username/Desktop/test/default", joined.c_str());
	joined = bump::FileSystem::join("/", "usr", "/local", "sbin", "app", "bundle");
	EXPECT_STREQ("/usr/local/sbin/app/bundle", joined.c_str());

	// Test the empty cases
	joined = bump::FileSystem::join("", "usr", "local", "", "sbin", "");
	EXPECT_STREQ("usr/local/sbin", joined.c_str());
	joined = bump::FileSystem::join("/", "", "", "testing", "again", "");
	EXPECT_STREQ("/testing/again", joined.c_str());
	joined = bump::FileSystem::join("", "", "", "", "", "");
	EXPECT_STREQ("", joined.c_str());

	// Test the cases with extra forward slashes
	joined = bump::FileSystem::join("/home", "/username/", "Desktop", "/local", "app", "/bundle");
	EXPECT_STREQ("/home/username/Desktop/local/app/bundle", joined.c_str());
	joined = bump::FileSystem::join("/", "opt/", "local", "/sbin", "app", "/bundle");
	EXPECT_STREQ("/opt/local/sbin/app/bundle", joined.c_str());

	// Test a case where it can't remove all the slashes
	joined = bump::FileSystem::join("/", "/opt/", "/local/", "/sbin/", "app/", "/bundle/");
	EXPECT_STREQ("//opt//local//sbin/app//bundle/", joined.c_str());
}

TEST_F(FileSystemTest, join7)
{
	// Test the default usage
	bump::String joined = bump::FileSystem::join("/", "home", "username", "Desktop", "test", "default", "folder");
	EXPECT_STREQ("/home/username/Desktop/test/default/folder", joined.c_str());
	joined = bump::FileSystem::join("/", "usr", "/local", "sbin", "app", "bundle", "exe");
	EXPECT_STREQ("/usr/local/sbin/app/bundle/exe", joined.c_str());

	// Test the empty cases
	joined = bump::FileSystem::join("", "usr", "local", "", "sbin", "", "/exe");
	EXPECT_STREQ("usr/local/sbin/exe", joined.c_str());
	joined = bump::FileSystem::join("/", "", "", "testing", "again", "", "/exe");
	EXPECT_STREQ("/testing/again/exe", joined.c_str());
	joined = bump::FileSystem::join("", "", "", "", "", "", "");
	EXPECT_STREQ("", joined.c_str());

	// Test the cases with extra forward slashes
	joined = bump::FileSystem::join("/home", "/username/", "Desktop", "/local", "app", "/bundle", "/exe/");
	EXPECT_STREQ("/home/username/Desktop/local/app/bundle/exe/", joined.c_str());
	joined = bump::FileSystem::join("/", "opt/", "local", "/sbin", "app", "/bundle", "exe");
	EXPECT_STREQ("/opt/local/sbin/app/bundle/exe", joined.c_str());

	// Test a case where it can't remove all the slashes
	joined = bump::FileSystem::join("/", "/opt/", "/local/", "/sbin/", "app/", "/bundle/", "/exe/");
	EXPECT_STREQ("//opt//local//sbin/app//bundle//exe/", joined.c_str());
}

TEST_F(FileSystemTest, join8)
{
	// Test the default usage
	bump::String joined = bump::FileSystem::join("/", "home", "username", "Desktop", "test", "default", "folder", "sa");
	EXPECT_STREQ("/home/username/Desktop/test/default/folder/sa", joined.c_str());
	joined = bump::FileSystem::join("/", "usr", "/local", "sbin", "app", "bundle", "exe", "sa");
	EXPECT_STREQ("/usr/local/sbin/app/bundle/exe/sa", joined.c_str());

	// Test the empty cases
	joined = bump::FileSystem::join("", "usr", "local", "", "sbin", "", "/exe", "/so/");
	EXPECT_STREQ("usr/local/sbin/exe/so/", joined.c_str());
	joined = bump::FileSystem::join("/", "", "", "testing", "again", "", "/exe", "");
	EXPECT_STREQ("/testing/again/exe", joined.c_str());
	joined = bump::FileSystem::join("", "", "", "", "", "", "", "");
	EXPECT_STREQ("", joined.c_str());

	// Test the cases with extra forward slashes
	joined = bump::FileSystem::join("/home", "/username/", "Desktop", "/local", "app", "/bundle", "/exe/", "so");
	EXPECT_STREQ("/home/username/Desktop/local/app/bundle/exe/so", joined.c_str());
	joined = bump::FileSystem::join("/", "opt/", "local", "/sbin", "app", "/bundle", "exe", "/so");
	EXPECT_STREQ("/opt/local/sbin/app/bundle/exe/so", joined.c_str());

	// Test a case where it can't remove all the slashes
	joined = bump::FileSystem::join("/", "/opt/", "/local/", "/sbin/", "app/", "/bundle/", "/exe/", "/so");
	EXPECT_STREQ("//opt//local//sbin/app//bundle//exe//so", joined.c_str());
}

TEST_F(FileSystemTest, join9)
{
	// Test the default usage
	bump::String joined = bump::FileSystem::join("/", "home", "username", "Desktop", "test", "default", "folder", "sa", "temp");
	EXPECT_STREQ("/home/username/Desktop/test/default/folder/sa/temp", joined.c_str());
	joined = bump::FileSystem::join("/", "usr", "/local", "sbin", "app", "bundle", "exe", "sa", "temp");
	EXPECT_STREQ("/usr/local/sbin/app/bundle/exe/sa/temp", joined.c_str());

	// Test the empty cases
	joined = bump::FileSystem::join("", "usr", "local", "", "sbin", "", "/exe", "/so/", "temp/");
	EXPECT_STREQ("usr/local/sbin/exe/so/temp/", joined.c_str());
	joined = bump::FileSystem::join("/", "", "", "testing", "again", "", "/exe", "", "/temp");
	EXPECT_STREQ("/testing/again/exe/temp", joined.c_str());
	joined = bump::FileSystem::join("", "", "", "", "", "", "", "", "");
	EXPECT_STREQ("", joined.c_str());

	// Test the cases with extra forward slashes
	joined = bump::FileSystem::join("/home", "/username/", "Desktop", "/local", "app", "/bundle", "/exe/", "so", "/temp/");
	EXPECT_STREQ("/home/username/Desktop/local/app/bundle/exe/so/temp/", joined.c_str());
	joined = bump::FileSystem::join("/", "opt/", "local", "/sbin", "app", "/bundle", "exe", "/so", "/temp");
	EXPECT_STREQ("/opt/local/sbin/app/bundle/exe/so/temp", joined.c_str());

	// Test a case where it can't remove all the slashes
	joined = bump::FileSystem::join("/", "/opt/", "/local/", "/sbin/", "app/", "/bundle/", "/exe/", "/so", "temp/");
	EXPECT_STREQ("//opt//local//sbin/app//bundle//exe//so/temp/", joined.c_str());
}

TEST_F(FileSystemTest, testSetCurrentPath)
{
	// Set the current path to the unittest directory
	bump::String current_path = bump::FileSystem::currentPath();
	bump::String new_current_path = bump::FileSystem::join(current_path, _unittestDirectory);
	bump::FileSystem::setCurrentPath(new_current_path);
	EXPECT_STREQ(new_current_path.c_str(), bump::FileSystem::currentPath().c_str());

	// Try to set the current path to one that isn't valid
	new_current_path = bump::FileSystem::join(current_path, "this_is_not_valid");
	EXPECT_THROW(bump::FileSystem::setCurrentPath(new_current_path), bump::FileSystemError);
}

TEST_F(FileSystemTest, testCurrentPath)
{
	// NOTE: We can't test the actual value here since it will change from computer
	// to computer. Therefore, the tests are more abstract.

	// Test to make sure the current path is not empty
	bump::String current_path = bump::FileSystem::currentPath();
	EXPECT_FALSE(current_path.isEmpty());

	// Test to make sure the current path exists
	EXPECT_TRUE(bump::FileSystem::exists(current_path));

	// Test to make sure the current path is a directory
	EXPECT_TRUE(bump::FileSystem::isDirectory(current_path));
}

TEST_F(FileSystemTest, testTemporaryPath)
{
	// NOTE: We can't test the actual value here since it will change from computer
	// to computer and operating system to operating system. Therefore, the tests
	// are more abstract.

	// Test to make sure the current path is not empty
	bump::String temp_path = bump::FileSystem::temporaryPath();
	EXPECT_FALSE(temp_path.isEmpty());

	// Test to make sure the temp path exists
	EXPECT_TRUE(bump::FileSystem::exists(temp_path));

	// Test to make sure the temp path is a directory
	EXPECT_TRUE(bump::FileSystem::isDirectory(temp_path));
}

TEST_F(FileSystemTest, testExists)
{
	// Test valid directories
	EXPECT_TRUE(bump::FileSystem::exists(_unittestDirectory));
	EXPECT_TRUE(bump::FileSystem::exists(_filesDirectory));
	EXPECT_TRUE(bump::FileSystem::exists(_regularDirectory));
	EXPECT_TRUE(bump::FileSystem::exists(_symlinkFilesDirectory));

	// Test valid directory symlinks
	EXPECT_TRUE(bump::FileSystem::exists(_symlinkDirectory));

	// Test valid files
	EXPECT_TRUE(bump::FileSystem::exists("unittest/files/output.txt"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/files/archive.tar.gz"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/files/.hidden_file.txt"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/regular_directory/paper.doc"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/regular_directory/help.pdf"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/symlink_directory/paper.doc"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/symlink_directory/help.pdf"));

	// Test valid file symlinks
	EXPECT_TRUE(bump::FileSystem::exists("unittest/symlink_files/output.txt"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/symlink_files/archive.tar.gz"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/symlink_files/.hidden_file.txt"));

	// Test invalid directories
	EXPECT_FALSE(bump::FileSystem::exists("unittest_does_not_exist"));
	EXPECT_FALSE(bump::FileSystem::exists("unittest_does_not_exist/files"));
	EXPECT_FALSE(bump::FileSystem::exists("unittest_does_not_exist/regular"));

	// Test invalid directory symlinks
	EXPECT_FALSE(bump::FileSystem::exists("unittest_nope/symlink_directory"));
	EXPECT_FALSE(bump::FileSystem::exists("unittest/nope_symlink_files"));

	// Test invalid files
	EXPECT_FALSE(bump::FileSystem::exists("unittest/files/nope_output.txt"));
	EXPECT_FALSE(bump::FileSystem::exists("unittest/files/.nope_hidden_file.txt"));

	// Test invalid file symlinks
	EXPECT_FALSE(bump::FileSystem::exists("unittest/not_a_directory/paper.doc"));
	EXPECT_FALSE(bump::FileSystem::exists("unittest/not_a_directory/help.pdf"));
	EXPECT_FALSE(bump::FileSystem::exists("unittest/symlink_files/nope_output.txt"));
	EXPECT_FALSE(bump::FileSystem::exists("unittest/symlink_files/nope_archive.tar.gz"));
	EXPECT_FALSE(bump::FileSystem::exists("unittest/symlink_files/.nope_hidden_file.txt"));

	// Test empty use case
	EXPECT_FALSE(bump::FileSystem::exists(""));
}

TEST_F(FileSystemTest, testIsDirectory)
{
	// Test valid directories
	EXPECT_TRUE(bump::FileSystem::isDirectory(_unittestDirectory));
	EXPECT_TRUE(bump::FileSystem::isDirectory(_filesDirectory));
	EXPECT_TRUE(bump::FileSystem::isDirectory(_regularDirectory));
	EXPECT_TRUE(bump::FileSystem::isDirectory(_symlinkFilesDirectory));

	// Test valid directory symlinks
	EXPECT_TRUE(bump::FileSystem::isDirectory(_symlinkDirectory));

	// Test files
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/files/output.txt"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/files/archive.tar.gz"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/files/.hidden_file.txt"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/regular_directory/paper.doc"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/regular_directory/help.pdf"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/symlink_directory/paper.doc"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/symlink_directory/help.pdf"));

	// Test file symlinks
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/symlink_files/output.txt"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/symlink_files/archive.tar.gz"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/symlink_files/.hidden_file.txt"));

	// Test invalid directories
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest_does_not_exist"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest_does_not_exist/files"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest_does_not_exist/regular"));

	// Test invalid directory symlinks
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest_nope/symlink_directory"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/nope_symlink_files"));

	// Test invalid files
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/files/nope_output.txt"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/files/.nope_hidden_file.txt"));

	// Test invalid file symlinks
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/not_a_directory/paper.doc"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/not_a_directory/help.pdf"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/symlink_files/nope_output.txt"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/symlink_files/nope_archive.tar.gz"));
	EXPECT_FALSE(bump::FileSystem::isDirectory("unittest/symlink_files/.nope_hidden_file.txt"));

	// Test empty use case
	EXPECT_FALSE(bump::FileSystem::isDirectory(""));
}

TEST_F(FileSystemTest, testIsFile)
{
	// Test valid directories
	EXPECT_FALSE(bump::FileSystem::isFile(_unittestDirectory));
	EXPECT_FALSE(bump::FileSystem::isFile(_filesDirectory));
	EXPECT_FALSE(bump::FileSystem::isFile(_regularDirectory));
	EXPECT_FALSE(bump::FileSystem::isFile(_symlinkFilesDirectory));

	// Test valid directory symlinks
	EXPECT_FALSE(bump::FileSystem::isFile(_symlinkDirectory));

	// Test files
	EXPECT_TRUE(bump::FileSystem::isFile("unittest/files/output.txt"));
	EXPECT_TRUE(bump::FileSystem::isFile("unittest/files/archive.tar.gz"));
	EXPECT_TRUE(bump::FileSystem::isFile("unittest/files/.hidden_file.txt"));
	EXPECT_TRUE(bump::FileSystem::isFile("unittest/regular_directory/paper.doc"));
	EXPECT_TRUE(bump::FileSystem::isFile("unittest/regular_directory/help.pdf"));
	EXPECT_TRUE(bump::FileSystem::isFile("unittest/symlink_directory/paper.doc"));
	EXPECT_TRUE(bump::FileSystem::isFile("unittest/symlink_directory/help.pdf"));

	// Test file symlinks
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/symlink_files/output.txt"));
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/symlink_files/archive.tar.gz"));
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/symlink_files/.hidden_file.txt"));

	// Test invalid directories
	EXPECT_FALSE(bump::FileSystem::isFile("unittest_does_not_exist"));
	EXPECT_FALSE(bump::FileSystem::isFile("unittest_does_not_exist/files"));
	EXPECT_FALSE(bump::FileSystem::isFile("unittest_does_not_exist/regular"));

	// Test invalid directory symlinks
	EXPECT_FALSE(bump::FileSystem::isFile("unittest_nope/symlink_directory"));
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/nope_symlink_files"));

	// Test invalid files
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/files/nope_output.txt"));
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/files/.nope_hidden_file.txt"));

	// Test invalid file symlinks
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/not_a_directory/paper.doc"));
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/not_a_directory/help.pdf"));
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/symlink_files/nope_output.txt"));
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/symlink_files/nope_archive.tar.gz"));
	EXPECT_FALSE(bump::FileSystem::isFile("unittest/symlink_files/.nope_hidden_file.txt"));

	// Test empty use case
	EXPECT_FALSE(bump::FileSystem::isFile(""));
}

TEST_F(FileSystemTest, testIsSymbolicLink)
{
	// Test valid directories
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(_unittestDirectory));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(_filesDirectory));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(_regularDirectory));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(_symlinkFilesDirectory));

	// Test valid directory symlinks
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(_symlinkDirectory));

	// Test files
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/files/output.txt"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/files/archive.tar.gz"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/files/.hidden_file.txt"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/regular_directory/paper.doc"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/regular_directory/help.pdf"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/symlink_directory/paper.doc"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/symlink_directory/help.pdf"));

	// Test file symlinks
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink("unittest/symlink_files/output.txt"));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink("unittest/symlink_files/archive.tar.gz"));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink("unittest/symlink_files/.hidden_file.txt"));

	// Test invalid directories
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest_does_not_exist"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest_does_not_exist/files"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest_does_not_exist/regular"));

	// Test invalid directory symlinks
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest_nope/symlink_directory"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/nope_symlink_files"));

	// Test invalid files
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/files/nope_output.txt"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/files/.nope_hidden_file.txt"));

	// Test invalid file symlinks
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/not_a_directory/paper.doc"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/not_a_directory/help.pdf"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/symlink_files/nope_output.txt"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/symlink_files/nope_archive.tar.gz"));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink("unittest/symlink_files/.nope_hidden_file.txt"));

	// Test empty use case
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(""));
}

TEST_F(FileSystemTest, testCreateDirectory)
{
	// Create a few directories
	bump::String path = "unittest/Create Directory Test";
	EXPECT_TRUE(bump::FileSystem::createDirectory(path));
	EXPECT_TRUE(bump::FileSystem::exists(path));
	EXPECT_TRUE(bump::FileSystem::isDirectory(path));
	path = "unittest/regular_directory/Another Test";
	EXPECT_TRUE(bump::FileSystem::createDirectory(path));
	EXPECT_TRUE(bump::FileSystem::exists(path));
	EXPECT_TRUE(bump::FileSystem::isDirectory(path));
	path = "unittest/regular_directory/Another Test/Even Here";
	EXPECT_TRUE(bump::FileSystem::createDirectory(path));
	EXPECT_TRUE(bump::FileSystem::exists(path));
	EXPECT_TRUE(bump::FileSystem::isDirectory(path));

	// Create some invalid directories
	path = "unittest/I do not exist/Test";
	EXPECT_FALSE(bump::FileSystem::createDirectory(path));
	EXPECT_FALSE(bump::FileSystem::exists(path));
	EXPECT_FALSE(bump::FileSystem::isDirectory(path));
	path = "unittest/I do not exist/Test/And Again";
	EXPECT_FALSE(bump::FileSystem::createDirectory(path));
	EXPECT_FALSE(bump::FileSystem::exists(path));
	EXPECT_FALSE(bump::FileSystem::isDirectory(path));
}

TEST_F(FileSystemTest, testCreateDirectoryPath)
{
	// Create a directory path
	bump::String path = "unittest/Long/Example/Path";
	EXPECT_TRUE(bump::FileSystem::createFullDirectoryPath(path));
	EXPECT_TRUE(bump::FileSystem::exists("unittest"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/Long"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/Long/Example"));
	EXPECT_TRUE(bump::FileSystem::exists("unittest/Long/Example/Path"));
	EXPECT_TRUE(bump::FileSystem::isDirectory("unittest"));
	EXPECT_TRUE(bump::FileSystem::isDirectory("unittest/Long"));
	EXPECT_TRUE(bump::FileSystem::isDirectory("unittest/Long/Example"));
	EXPECT_TRUE(bump::FileSystem::isDirectory("unittest/Long/Example/Path"));

	// Even wacky paths should work just fine
	path = "unittest/this\t\n\\///is////not/////valid";
	EXPECT_TRUE(bump::FileSystem::createFullDirectoryPath(path));
}

TEST_F(FileSystemTest, testRemoveDirectory)
{
	// Create a couple empty directories
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/empty_dir1"));
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/empty_dir2"));

	// Remove some empty, valid directories
	EXPECT_TRUE(bump::FileSystem::removeDirectory("unittest/empty_dir1"));
	EXPECT_TRUE(bump::FileSystem::removeDirectory("unittest/empty_dir2"));

	// Remove some valid directories and contain files. This should fail b/c
	// the remove directory only succeeds when the directory is empty.
	EXPECT_FALSE(bump::FileSystem::removeDirectory(_symlinkFilesDirectory));
	EXPECT_FALSE(bump::FileSystem::removeDirectory(_regularDirectory));

	// Remove the symlink directory
	EXPECT_TRUE(bump::FileSystem::removeDirectory(_symlinkDirectory));

	// Try to remove some invalid directories
	EXPECT_THROW(bump::FileSystem::removeDirectory("unittest/does not exist"), bump::FileSystemError);
	EXPECT_THROW(bump::FileSystem::removeDirectory("unittest/does not exist/either"), bump::FileSystemError);
	EXPECT_THROW(bump::FileSystem::removeDirectory("unittest/does not exist/either/for good measure"), bump::FileSystemError);

	// Try to remove some files
	EXPECT_THROW(bump::FileSystem::removeDirectory("unittest/files/output.txt"), bump::FileSystemError);
	EXPECT_THROW(bump::FileSystem::removeDirectory("unittest/files/archive.tar.gz"), bump::FileSystemError);
	EXPECT_THROW(bump::FileSystem::removeDirectory("unittest/files/.hidden_file.txt"), bump::FileSystemError);
}

TEST_F(FileSystemTest, testRemoveDirectoryAndContents)
{
	// Create a couple empty directories
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/empty_dir1"));
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/empty_dir2"));

	// Remove some empty, valid directories
	EXPECT_TRUE(bump::FileSystem::removeDirectoryAndContents("unittest/empty_dir1"));
	EXPECT_TRUE(bump::FileSystem::removeDirectoryAndContents("unittest/empty_dir2"));

	// Remove the symlink directory
	EXPECT_TRUE(bump::FileSystem::removeDirectoryAndContents(_symlinkDirectory));

	// Remove some valid directories and contain files
	EXPECT_TRUE(bump::FileSystem::removeDirectoryAndContents(_symlinkFilesDirectory));
	EXPECT_TRUE(bump::FileSystem::removeDirectoryAndContents(_regularDirectory));

	// Try to remove some invalid directories
	EXPECT_THROW(bump::FileSystem::removeDirectoryAndContents("unittest/does not exist"), bump::FileSystemError);
	EXPECT_THROW(bump::FileSystem::removeDirectoryAndContents("unittest/does not exist/either"), bump::FileSystemError);
	EXPECT_THROW(bump::FileSystem::removeDirectoryAndContents("unittest/does not exist/either/for good measure"), bump::FileSystemError);

	// Try to remove some files
	EXPECT_THROW(bump::FileSystem::removeDirectoryAndContents("unittest/files/output.txt"), bump::FileSystemError);
	EXPECT_THROW(bump::FileSystem::removeDirectoryAndContents("unittest/files/archive.tar.gz"), bump::FileSystemError);
	EXPECT_THROW(bump::FileSystem::removeDirectoryAndContents("unittest/files/.hidden_file.txt"), bump::FileSystemError);
}

}	// End of bumpTest namespace
