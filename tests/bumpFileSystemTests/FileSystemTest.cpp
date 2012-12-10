//
//	FileSystemTest.cpp
//	Bump
//
//	Created by Christian Noon on 12/6/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/foreach.hpp>

// Bump headers
#include <bump/Exception.h>
#include <bump/FileSystem.h>
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
		// NOTE: the source is relative to the destination directory
		bump::FileSystem::createSymbolicLink("regular_directory", _symlinkDirectory);

		// unittest/symlink_files
		// NOTE: the source is relative to the destination directory
		bump::FileSystem::createDirectory(_symlinkFilesDirectory);
		bump::FileSystem::createSymbolicLink("../files/output.txt", "unittest/symlink_files/output.txt");
		bump::FileSystem::createSymbolicLink("../files/archive.tar.gz", "unittest/symlink_files/archive.tar.gz");
		bump::FileSystem::createSymbolicLink("../files/.hidden_file.txt", "unittest/symlink_files/.hidden_file.txt");
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
	EXPECT_FALSE(bump::FileSystem::setCurrentPath(new_current_path));
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
	EXPECT_TRUE(bump::FileSystem::isFile("unittest/symlink_files/output.txt"));
	EXPECT_TRUE(bump::FileSystem::isFile("unittest/symlink_files/archive.tar.gz"));
	EXPECT_TRUE(bump::FileSystem::isFile("unittest/symlink_files/.hidden_file.txt"));

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
	EXPECT_FALSE(bump::FileSystem::removeDirectory("unittest/does not exist"));
	EXPECT_FALSE(bump::FileSystem::removeDirectory("unittest/does not exist/either"));
	EXPECT_FALSE(bump::FileSystem::removeDirectory("unittest/does not exist/either/for good measure"));

	// Try to remove some files
	EXPECT_FALSE(bump::FileSystem::removeDirectory("unittest/files/output.txt"));
	EXPECT_FALSE(bump::FileSystem::removeDirectory("unittest/files/archive.tar.gz"));
	EXPECT_FALSE(bump::FileSystem::removeDirectory("unittest/files/.hidden_file.txt"));
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
	EXPECT_FALSE(bump::FileSystem::removeDirectoryAndContents("unittest/does not exist"));
	EXPECT_FALSE(bump::FileSystem::removeDirectoryAndContents("unittest/does not exist/either"));
	EXPECT_FALSE(bump::FileSystem::removeDirectoryAndContents("unittest/does not exist/either/for good measure"));

	// Try to remove some files
	EXPECT_FALSE(bump::FileSystem::removeDirectoryAndContents("unittest/files/output.txt"));
	EXPECT_FALSE(bump::FileSystem::removeDirectoryAndContents("unittest/files/archive.tar.gz"));
	EXPECT_FALSE(bump::FileSystem::removeDirectoryAndContents("unittest/files/.hidden_file.txt"));
}

TEST_F(FileSystemTest, testRenameDirectory)
{
	// Create a couple empty directories
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/empty_dir1"));
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/empty_dir2"));

	// Rename both of the directories
	EXPECT_TRUE(bump::FileSystem::renameDirectory("unittest/empty_dir1", "unittest/renamed_dir1"));
	EXPECT_TRUE(bump::FileSystem::renameDirectory("unittest/empty_dir2", "unittest/renamed_dir2"));

	// Try to rename a source directory that doesn't exist
	EXPECT_FALSE(bump::FileSystem::renameDirectory("unittest/not actual directory", "unittest/worth a try"));
	EXPECT_FALSE(bump::FileSystem::renameDirectory("unittest/invalid/dir", "unittest/nope"));

	// Try to rename a valid source directory to a destination who's parent directory doesn't exist
	EXPECT_FALSE(bump::FileSystem::renameDirectory("unittest/renamed_dir1", "unittest/long/path/renamed_dir1"));
	EXPECT_FALSE(bump::FileSystem::renameDirectory("unittest/renamed_dir2", "unittest/this/is/not/valid/renamed_dir2"));
}

TEST_F(FileSystemTest, testDirectoryList)
{
	// Create a couple empty directories
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/empty_dir1"));
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/empty_dir2"));

	// Get the directory list (should be completely empty)
	bump::StringList empty_dir_list1 = bump::FileSystem::directoryList("unittest/empty_dir1");
	EXPECT_TRUE(empty_dir_list1.empty());
	bump::StringList empty_dir_list2 = bump::FileSystem::directoryList("unittest/empty_dir2");
	EXPECT_TRUE(empty_dir_list2.empty());

	// Get the directory list of unittest
	bump::StringList unittest_list = bump::FileSystem::directoryList("unittest");
	EXPECT_EQ(6, unittest_list.size());
	EXPECT_STREQ("unittest/empty_dir1", unittest_list.at(0).c_str());
	EXPECT_STREQ("unittest/empty_dir2", unittest_list.at(1).c_str());
	EXPECT_STREQ("unittest/files", unittest_list.at(2).c_str());
	EXPECT_STREQ("unittest/regular_directory", unittest_list.at(3).c_str());
	EXPECT_STREQ("unittest/symlink_directory", unittest_list.at(4).c_str());
	EXPECT_STREQ("unittest/symlink_files", unittest_list.at(5).c_str());

	// Get the directory list of the unittest/files directory
	bump::StringList files_list = bump::FileSystem::directoryList("unittest/files");
	EXPECT_EQ(3, files_list.size());
	EXPECT_STREQ("unittest/files/.hidden_file.txt", files_list.at(0).c_str());
	EXPECT_STREQ("unittest/files/archive.tar.gz", files_list.at(1).c_str());
	EXPECT_STREQ("unittest/files/output.txt", files_list.at(2).c_str());

	// Get the directory list of the unittest/symlink_directory
	bump::StringList symlink_dir_list = bump::FileSystem::directoryList("unittest/symlink_directory");
	EXPECT_EQ(2, symlink_dir_list.size());
	EXPECT_STREQ("unittest/symlink_directory/help.pdf", symlink_dir_list.at(0).c_str());
	EXPECT_STREQ("unittest/symlink_directory/paper.doc", symlink_dir_list.at(1).c_str());
}

TEST_F(FileSystemTest, testDirectoryInfoList)
{
	// Create a couple empty directories
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/empty_dir1"));
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/empty_dir2"));

	// Get the directory list (should be completely empty)
	bump::FileInfoList empty_dir_list1 = bump::FileSystem::directoryInfoList("unittest/empty_dir1");
	EXPECT_TRUE(empty_dir_list1.empty());
	bump::FileInfoList empty_dir_list2 = bump::FileSystem::directoryInfoList("unittest/empty_dir2");
	EXPECT_TRUE(empty_dir_list2.empty());

	// Get the directory list of unittest
	bump::FileInfoList unittest_list = bump::FileSystem::directoryInfoList("unittest");
	EXPECT_EQ(6, unittest_list.size());
	EXPECT_STREQ("unittest/empty_dir1", unittest_list.at(0).path().c_str());
	EXPECT_STREQ("unittest/empty_dir2", unittest_list.at(1).path().c_str());
	EXPECT_STREQ("unittest/files", unittest_list.at(2).path().c_str());
	EXPECT_STREQ("unittest/regular_directory", unittest_list.at(3).path().c_str());
	EXPECT_STREQ("unittest/symlink_directory", unittest_list.at(4).path().c_str());
	EXPECT_STREQ("unittest/symlink_files", unittest_list.at(5).path().c_str());

	// Get the directory list of the unittest/files directory
	bump::FileInfoList files_list = bump::FileSystem::directoryInfoList("unittest/files");
	EXPECT_EQ(3, files_list.size());
	EXPECT_STREQ("unittest/files/.hidden_file.txt", files_list.at(0).path().c_str());
	EXPECT_STREQ("unittest/files/archive.tar.gz", files_list.at(1).path().c_str());
	EXPECT_STREQ("unittest/files/output.txt", files_list.at(2).path().c_str());

	// Get the directory list of the unittest/symlink_directory
	bump::FileInfoList symlink_dir_list = bump::FileSystem::directoryInfoList("unittest/symlink_directory");
	EXPECT_EQ(2, symlink_dir_list.size());
	EXPECT_STREQ("unittest/symlink_directory/help.pdf", symlink_dir_list.at(0).path().c_str());
	EXPECT_STREQ("unittest/symlink_directory/paper.doc", symlink_dir_list.at(1).path().c_str());
}

TEST_F(FileSystemTest, testCreateFile)
{
	// Create a few files
	bump::String path = "unittest/file1.txt";
	EXPECT_TRUE(bump::FileSystem::createFile(path));
	EXPECT_TRUE(bump::FileSystem::exists(path));
	EXPECT_TRUE(bump::FileSystem::isFile(path));
	path = "unittest/regular_directory/file2.doc";
	EXPECT_TRUE(bump::FileSystem::createFile(path));
	EXPECT_TRUE(bump::FileSystem::exists(path));
	EXPECT_TRUE(bump::FileSystem::isFile(path));
	path = "unittest/regular_directory/file3.pdf";
	EXPECT_TRUE(bump::FileSystem::createFile(path));
	EXPECT_TRUE(bump::FileSystem::exists(path));
	EXPECT_TRUE(bump::FileSystem::isFile(path));

	// Create some invalid files
	path = "unittest/I do not exist/file4.txt";
	EXPECT_FALSE(bump::FileSystem::createFile(path));
	EXPECT_FALSE(bump::FileSystem::exists(path));
	EXPECT_FALSE(bump::FileSystem::isFile(path));
	path = "unittest/I do not exist/Test/file5.txt";
	EXPECT_FALSE(bump::FileSystem::createFile(path));
	EXPECT_FALSE(bump::FileSystem::exists(path));
	EXPECT_FALSE(bump::FileSystem::isFile(path));
}

TEST_F(FileSystemTest, testRemoveFile)
{
	// Create a few files and remove them
	bump::String path = "unittest/file1.txt";
	EXPECT_TRUE(bump::FileSystem::createFile(path));
	EXPECT_TRUE(bump::FileSystem::exists(path));
	EXPECT_TRUE(bump::FileSystem::isFile(path));
	EXPECT_TRUE(bump::FileSystem::removeFile(path));
	EXPECT_FALSE(bump::FileSystem::exists(path));
	EXPECT_FALSE(bump::FileSystem::isFile(path));
	path = "unittest/regular_directory/file2.doc";
	EXPECT_TRUE(bump::FileSystem::createFile(path));
	EXPECT_TRUE(bump::FileSystem::exists(path));
	EXPECT_TRUE(bump::FileSystem::isFile(path));
	EXPECT_TRUE(bump::FileSystem::removeFile(path));
	EXPECT_FALSE(bump::FileSystem::exists(path));
	EXPECT_FALSE(bump::FileSystem::isFile(path));
	path = "unittest/regular_directory/file3.pdf";
	EXPECT_TRUE(bump::FileSystem::createFile(path));
	EXPECT_TRUE(bump::FileSystem::exists(path));
	EXPECT_TRUE(bump::FileSystem::isFile(path));
	EXPECT_TRUE(bump::FileSystem::removeFile(path));
	EXPECT_FALSE(bump::FileSystem::exists(path));
	EXPECT_FALSE(bump::FileSystem::isFile(path));

	// Try to remove some invalid files
	path = "unittest/I do not exist/file4.txt";
	EXPECT_FALSE(bump::FileSystem::removeFile(path));
	path = "unittest/I do not exist/Test/file5.txt";
	EXPECT_FALSE(bump::FileSystem::removeFile(path));

	// Try to remove some directories, fails since path isn't a file
	path = "unittest/files";
	EXPECT_FALSE(bump::FileSystem::removeFile(path));
	path = "unittest/regular_directory";
	EXPECT_FALSE(bump::FileSystem::removeFile(path));

	// Try to remove some files with a parent path symlink
	path = "unittest/symlink_directory/paper.doc";
	EXPECT_TRUE(bump::FileSystem::removeFile(path));
	path = "unittest/symlink_directory/help.pdf";
	EXPECT_TRUE(bump::FileSystem::removeFile(path));

	// Remove some valid file symlinks
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::removeFile(path));
	path = "unittest/symlink_files/archive.tar.gz";
	EXPECT_TRUE(bump::FileSystem::removeFile(path));
}

TEST_F(FileSystemTest, testCopyFile)
{
	// Copy some files
	bump::String source = "unittest/files/output.txt";
	bump::String destination = "unittest/files/output_copy.txt";
	EXPECT_TRUE(bump::FileSystem::copyFile(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isFile(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isFile(source));
	source = "unittest/files/.hidden_file.txt";
	destination = "unittest/files/.hidden_file_copy.txt";
	EXPECT_TRUE(bump::FileSystem::copyFile(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isFile(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isFile(source));

	// Try to copy some invalid files
	source = "unittest/I do not exist/file4.txt";
	destination = "unittest/files/file4.txt";
	EXPECT_FALSE(bump::FileSystem::copyFile(source, destination));
	source = "unittest/I do not exist/Test/file5.txt";
	destination = "unittest/files/file5.txt";
	EXPECT_FALSE(bump::FileSystem::copyFile(source, destination));

	// Try to copy some directories, fails since source isn't a file
	source = "unittest/files";
	destination = "unittest/files/bad_file.txt";
	EXPECT_FALSE(bump::FileSystem::copyFile(source, destination));
	source = "unittest/regular_directory";
	destination = "unittest/files/bad_file.txt";
	EXPECT_FALSE(bump::FileSystem::copyFile(source, destination));

	// Try to copy some files with a parent path symlink
	source = "unittest/symlink_directory/paper.doc";
	destination = "unittest/files/paper_copy.doc";
	EXPECT_TRUE(bump::FileSystem::copyFile(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isFile(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isFile(source));
	source = "unittest/symlink_directory/help.pdf";
	destination = "unittest/help_copy.pdf";
	EXPECT_TRUE(bump::FileSystem::copyFile(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isFile(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isFile(source));

	// Copy some valid file symlinks
	source = "unittest/symlink_files/output.txt";
	destination = "unittest/symlink_files/output_copy.txt";
	EXPECT_TRUE(bump::FileSystem::copyFile(source, destination));
	source = "unittest/symlink_files/archive.tar.gz";
	destination = "unittest/symlink_files/archive_copy.tar.gz";
	EXPECT_TRUE(bump::FileSystem::copyFile(source, destination));
}

TEST_F(FileSystemTest, testRenameFile)
{
	// Rename some files
	bump::String source = "unittest/files/output.txt";
	bump::String destination = "unittest/files/output_copy.txt";
	EXPECT_TRUE(bump::FileSystem::renameFile(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isFile(destination));
	EXPECT_FALSE(bump::FileSystem::exists(source));
	EXPECT_FALSE(bump::FileSystem::isFile(source));
	source = "unittest/files/.hidden_file.txt";
	destination = "unittest/files/.hidden_file_copy.txt";
	EXPECT_TRUE(bump::FileSystem::renameFile(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isFile(destination));
	EXPECT_FALSE(bump::FileSystem::exists(source));
	EXPECT_FALSE(bump::FileSystem::isFile(source));

	// Try to rename some invalid files
	source = "unittest/I do not exist/file4.txt";
	destination = "unittest/files/file4.txt";
	EXPECT_FALSE(bump::FileSystem::renameFile(source, destination));
	source = "unittest/I do not exist/Test/file5.txt";
	destination = "unittest/files/file5.txt";
	EXPECT_FALSE(bump::FileSystem::renameFile(source, destination));

	// Try to rename some directories, fails since source isn't a file
	source = "unittest/files";
	destination = "unittest/files/bad_file.txt";
	EXPECT_FALSE(bump::FileSystem::renameFile(source, destination));
	source = "unittest/regular_directory";
	destination = "unittest/files/bad_file.txt";
	EXPECT_FALSE(bump::FileSystem::renameFile(source, destination));

	// Try to rename some files with a parent path symlink
	source = "unittest/symlink_directory/paper.doc";
	destination = "unittest/files/paper_copy.doc";
	EXPECT_TRUE(bump::FileSystem::renameFile(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isFile(destination));
	EXPECT_FALSE(bump::FileSystem::exists(source));
	EXPECT_FALSE(bump::FileSystem::isFile(source));
	source = "unittest/symlink_directory/help.pdf";
	destination = "unittest/help_copy.pdf";
	EXPECT_TRUE(bump::FileSystem::renameFile(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isFile(destination));
	EXPECT_FALSE(bump::FileSystem::exists(source));
	EXPECT_FALSE(bump::FileSystem::isFile(source));

	// Rename a file symlink
	source = "unittest/symlink_files/archive.tar.gz";
	destination = "unittest/symlink_files/archive_copy.tar.gz";
	EXPECT_TRUE(bump::FileSystem::renameFile(source, destination));
}

TEST_F(FileSystemTest, testCreateSymbolicLink)
{
	//=====================================================================================
	//									   FILES
	//=====================================================================================

	// Create a valid relative path file symlink
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/files/new_symlinks"));
	bump::String source = "unittest/files/output.txt";
	bump::String relative_source = "../output.txt";
	bump::String destination = "unittest/files/new_symlinks/output_copy.txt";
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(relative_source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isFile(source));
	EXPECT_TRUE(bump::FileSystem::exists(bump::FileInfo(destination).canonicalPath()));

	// Test an incorrectly built relative path file symlink. It is really important
	// to note that all the tests will pass except for the last one. We get the canonical
	// path to the symlink's target to see if the symlink is actually valid.
	source = "unittest/files/archive.tar.gz";
	destination = "unittest/files/new_symlinks/archive_copy.tar.gz";
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isFile(source));
	EXPECT_THROW(bump::FileInfo(destination).canonicalPath(), bump::FileSystemError);

	// Try to create some symlink files with bad source paths (creation will succeed but
	// the target path will be invalid)
	source = "unittest/not valid/archive.tar.gz";
	destination = "unittest/files/new_symlinks/my_new_archive.tar.gz";
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(source, destination));
	EXPECT_THROW(bump::FileInfo(destination).canonicalPath(), bump::FileSystemError);
	source = "unittest/files/archive.tar.gz.whoops";
	destination = "unittest/files/new_symlinks/archive.tar.gz.whoops";
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(source, destination));
	EXPECT_THROW(bump::FileInfo(destination).canonicalPath(), bump::FileSystemError);

	// Try to create some symlink files with bad destination paths
	source = "does/not/matter/here.txt";
	destination = "unittest/files/do/not/exist/here_copy.txt";
	EXPECT_FALSE(bump::FileSystem::createSymbolicLink(source, destination));
	source = "unittest/files/output.txt";
	destination = "some/random/directory/output_copy.txt";
	EXPECT_FALSE(bump::FileSystem::createSymbolicLink(source, destination));

	//=====================================================================================
	//									 DIRECTORIES
	//=====================================================================================

	// Create a valid relative path directory symlink
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/files/testing"));
	source = "unittest/files/testing";
	relative_source = "../files/testing";
	destination = "unittest/regular_directory/copied_testing";
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(relative_source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isDirectory(source));
	EXPECT_TRUE(bump::FileSystem::exists(bump::FileInfo(destination).canonicalPath()));

	// Test an incorrectly built relative path directory symlink. It is really important
	// to note that all the tests will pass except for the last one. We get the canonical
	// path to the symlink's target to see if the symlink is actually valid.
	source = "unittest/files/testing";
	destination = "unittest/regular_directory/copied_testing_again";
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isDirectory(source));
	EXPECT_THROW(bump::FileInfo(destination).canonicalPath(), bump::FileSystemError);

	// Try to create some symlink directories with bad source paths (creation will succeed but
	// the target path will be invalid)
	source = "unittest/not valid";
	destination = "unittest/files/testing/why not";
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(source, destination));
	EXPECT_THROW(bump::FileInfo(destination).canonicalPath(), bump::FileSystemError);
	source = "unittest/still/not/valid";
	destination = "unittest/files/testing/again";
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(source, destination));
	EXPECT_THROW(bump::FileInfo(destination).canonicalPath(), bump::FileSystemError);

	// Try to create some symlink directories with bad destination paths
	source = "does/not/matter/at/all";
	destination = "unittest/files/do/not/exist";
	EXPECT_FALSE(bump::FileSystem::createSymbolicLink(source, destination));
	source = "unittest/files";
	destination = "some/random/directory";
	EXPECT_FALSE(bump::FileSystem::createSymbolicLink(source, destination));
}

TEST_F(FileSystemTest, testRemoveSymbolicLink)
{
	// Create a new symlink file and remove it
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/files/new_symlinks"));
	bump::String source = "unittest/files/output.txt";
	bump::String relative_source = "../output.txt";
	bump::String destination = "unittest/files/new_symlinks/output_copy.txt";
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(relative_source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isFile(source));
	EXPECT_TRUE(bump::FileSystem::exists(bump::FileInfo(destination).canonicalPath()));
	EXPECT_TRUE(bump::FileSystem::removeSymbolicLink(destination));
	EXPECT_FALSE(bump::FileSystem::exists(destination));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isFile(source));

	// Create a new symlink directory and remove it
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/files/testing"));
	source = "unittest/files/testing";
	relative_source = "../files/testing";
	destination = "unittest/regular_directory/copied_testing";
	EXPECT_TRUE(bump::FileSystem::createSymbolicLink(relative_source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isDirectory(source));
	EXPECT_TRUE(bump::FileSystem::exists(bump::FileInfo(destination).canonicalPath()));
	EXPECT_TRUE(bump::FileSystem::removeSymbolicLink(destination));
	EXPECT_FALSE(bump::FileSystem::exists(destination));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isDirectory(source));

	// Try to remove some files, fails since they are not symlinks
	bump::String path = "unittest/files/output.txt";
	EXPECT_FALSE(bump::FileSystem::removeSymbolicLink(path));
	path = "unittest/files/archive.tar.gz";
	EXPECT_FALSE(bump::FileSystem::removeSymbolicLink(path));

	// Try to remove some directories, fails since path isn't a symlink
	path = "unittest/files";
	EXPECT_FALSE(bump::FileSystem::removeSymbolicLink(path));
	path = "unittest/regular_directory";
	EXPECT_FALSE(bump::FileSystem::removeSymbolicLink(path));

	// Try to remove some paths that don't exist
	path = "unittest/I do not exist/file4.txt";
	EXPECT_FALSE(bump::FileSystem::removeSymbolicLink(path));
	path = "unittest/I do not exist/Test";
	EXPECT_FALSE(bump::FileSystem::removeSymbolicLink(path));

	// Try to remove some files with a parent path symlink, fails since the files
	// themselves are not symlinks
	path = "unittest/symlink_directory/paper.doc";
	EXPECT_FALSE(bump::FileSystem::removeSymbolicLink(path));
	path = "unittest/symlink_directory/help.pdf";
	EXPECT_FALSE(bump::FileSystem::removeSymbolicLink(path));
}

TEST_F(FileSystemTest, testCopySymbolicLink)
{
	// Copy a symlink file to the same directory
	bump::String source = "unittest/symlink_files/output.txt";
	bump::String destination = "unittest/symlink_files/output_copy.txt";
	EXPECT_TRUE(bump::FileSystem::copySymbolicLink(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(source));
	EXPECT_TRUE(bump::FileSystem::exists(bump::FileInfo(destination).canonicalPath()));

	// Copy a symlink file to a different directory. This will all go fine but the
	// target path will be wrong since it is a relative path. You can only copy symlinks
	// with absolute paths to avoid this issue.
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/files/new_symlinks"));
	source = "unittest/symlink_files/output.txt";
	destination = "unittest/files/new_symlinks/output_copy.txt";
	EXPECT_TRUE(bump::FileSystem::copySymbolicLink(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(source));
	EXPECT_THROW(bump::FileInfo(destination).canonicalPath(), bump::FileSystemError);

	// Copy a symlink directory to the same directory
	source = "unittest/symlink_directory";
	destination = "unittest/symlink_directory_copy";
	EXPECT_TRUE(bump::FileSystem::copySymbolicLink(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(source));
	EXPECT_TRUE(bump::FileSystem::exists(bump::FileInfo(destination).canonicalPath()));

	// Copy a symlink directory to a different directory. This will all go fine but the
	// target path will be wrong since it is a relative path. You can only copy symlinks
	// with absolute paths to avoid this issue.
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/files/new_symlink_directory"));
	source = "unittest/symlink_directory";
	destination = "unittest/files/new_symlink_directory/symlink_directory_copy";
	EXPECT_TRUE(bump::FileSystem::copySymbolicLink(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_TRUE(bump::FileSystem::exists(source));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(source));
	EXPECT_THROW(bump::FileInfo(destination).canonicalPath(), bump::FileSystemError);

	// Try to copy a regular file
	source = "unittest/files/output.txt";
	destination = "unittest/files/output_copy.txt";
	EXPECT_FALSE(bump::FileSystem::copySymbolicLink(source, destination));

	// Try to copy a regular directory
	source = "unittest/files";
	destination = "unittest/files_copied";
	EXPECT_FALSE(bump::FileSystem::copySymbolicLink(source, destination));

	// Try to copy an invalid file
	source = "unittest/files/does_not_exist.txt";
	destination = "unittest/files/does_not_exist_copy.txt";
	EXPECT_FALSE(bump::FileSystem::copySymbolicLink(source, destination));

	// Try to copy and invalid directory
	source = "unittest/does/not/exist";
	destination = "unittest/does_not_exist_copy";
	EXPECT_FALSE(bump::FileSystem::copySymbolicLink(source, destination));

	// Try to copy a symlink file to an invalid destination
	source = "unittest/symlink_files/output.txt";
	destination = "unittest/does/not/exist/output_copy.txt";
	EXPECT_FALSE(bump::FileSystem::copySymbolicLink(source, destination));

	// Try to copy a symlink directory to an invalid destination
	source = "unittest/symlink_directory";
	destination = "unittest/does/not/exist/symlink_directory_copy";
	EXPECT_FALSE(bump::FileSystem::copySymbolicLink(source, destination));
}

TEST_F(FileSystemTest, testRenameSymbolicLink)
{
	// Rename a symlink file to the same directory
	bump::String source = "unittest/symlink_files/output.txt";
	bump::String destination = "unittest/symlink_files/output_copy.txt";
	EXPECT_TRUE(bump::FileSystem::renameSymbolicLink(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_FALSE(bump::FileSystem::exists(source));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(source));
	EXPECT_TRUE(bump::FileSystem::exists(bump::FileInfo(destination).canonicalPath()));

	// Rename a symlink file to a different directory. This will all go fine but the
	// target path will be wrong since it is a relative path. You can only rename symlinks
	// with absolute paths to avoid this issue.
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/files/new_symlinks"));
	source = "unittest/symlink_files/output_copy.txt";
	destination = "unittest/files/new_symlinks/output_copy_copy.txt";
	EXPECT_TRUE(bump::FileSystem::renameSymbolicLink(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_FALSE(bump::FileSystem::exists(source));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(source));
	EXPECT_THROW(bump::FileInfo(destination).canonicalPath(), bump::FileSystemError);

	// Rename a symlink directory to the same directory
	source = "unittest/symlink_directory";
	destination = "unittest/symlink_directory_copy";
	EXPECT_TRUE(bump::FileSystem::renameSymbolicLink(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_FALSE(bump::FileSystem::exists(source));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(source));
	EXPECT_TRUE(bump::FileSystem::exists(bump::FileInfo(destination).canonicalPath()));

	// Rename a symlink directory to a different directory. This will all go fine but the
	// target path will be wrong since it is a relative path. You can only rename symlinks
	// with absolute paths to avoid this issue.
	EXPECT_TRUE(bump::FileSystem::createDirectory("unittest/files/new_symlink_directory"));
	source = "unittest/symlink_directory_copy";
	destination = "unittest/files/new_symlink_directory/symlink_directory_copy_copy";
	EXPECT_TRUE(bump::FileSystem::renameSymbolicLink(source, destination));
	EXPECT_TRUE(bump::FileSystem::exists(destination));
	EXPECT_TRUE(bump::FileSystem::isSymbolicLink(destination));
	EXPECT_FALSE(bump::FileSystem::exists(source));
	EXPECT_FALSE(bump::FileSystem::isSymbolicLink(source));
	EXPECT_THROW(bump::FileInfo(destination).canonicalPath(), bump::FileSystemError);

	// Try to rename a regular file
	source = "unittest/files/output.txt";
	destination = "unittest/files/output_copy.txt";
	EXPECT_FALSE(bump::FileSystem::renameSymbolicLink(source, destination));

	// Try to rename a regular directory
	source = "unittest/files";
	destination = "unittest/files_copied";
	EXPECT_FALSE(bump::FileSystem::renameSymbolicLink(source, destination));

	// Try to rename an invalid file
	source = "unittest/files/does_not_exist.txt";
	destination = "unittest/files/does_not_exist_copy.txt";
	EXPECT_FALSE(bump::FileSystem::renameSymbolicLink(source, destination));

	// Try to rename and invalid directory
	source = "unittest/does/not/exist";
	destination = "unittest/does_not_exist_copy";
	EXPECT_FALSE(bump::FileSystem::renameSymbolicLink(source, destination));

	// Try to rename a symlink file to an invalid destination
	source = "unittest/symlink_files/output.txt";
	destination = "unittest/does/not/exist/output_copy.txt";
	EXPECT_FALSE(bump::FileSystem::renameSymbolicLink(source, destination));

	// Try to rename a symlink directory to an invalid destination
	source = "unittest/symlink_directory";
	destination = "unittest/does/not/exist/symlink_directory_copy";
	EXPECT_FALSE(bump::FileSystem::renameSymbolicLink(source, destination));
}

TEST_F(FileSystemTest, testSetPermissions)
{
	// Set permissions on a valid file
	bump::FileSystem::Permissions permissions = (bump::FileSystem::OWNER_READ |
												 bump::FileSystem::OWNER_WRITE |
												 bump::FileSystem::OWNER_EXE |
												 bump::FileSystem::GROUP_READ |
												 bump::FileSystem::OTHERS_READ);
	EXPECT_TRUE(bump::FileSystem::setPermissions("unittest/files/output.txt", permissions));
	bump::FileSystem::Permissions actual_permissions = bump::FileSystem::permissions("unittest/files/output.txt");
	EXPECT_TRUE(actual_permissions & bump::FileSystem::OWNER_READ);
	EXPECT_TRUE(actual_permissions & bump::FileSystem::OWNER_WRITE);
	EXPECT_TRUE(actual_permissions & bump::FileSystem::OWNER_EXE);
	EXPECT_TRUE(actual_permissions & bump::FileSystem::GROUP_READ);
	EXPECT_FALSE(actual_permissions & bump::FileSystem::GROUP_WRITE);
	EXPECT_FALSE(actual_permissions & bump::FileSystem::GROUP_EXE);
	EXPECT_TRUE(actual_permissions & bump::FileSystem::OTHERS_READ);
	EXPECT_FALSE(actual_permissions & bump::FileSystem::OTHERS_WRITE);
	EXPECT_FALSE(actual_permissions & bump::FileSystem::OTHERS_EXE);

	// Set permissions on a valid directory
	permissions = (bump::FileSystem::OWNER_READ | bump::FileSystem::OWNER_WRITE | bump::FileSystem::OWNER_EXE);
	EXPECT_TRUE(bump::FileSystem::setPermissions("unittest/files", permissions));
	actual_permissions = bump::FileSystem::permissions("unittest/files");
	EXPECT_TRUE(actual_permissions & bump::FileSystem::OWNER_READ);
	EXPECT_TRUE(actual_permissions & bump::FileSystem::OWNER_WRITE);
	EXPECT_TRUE(actual_permissions & bump::FileSystem::OWNER_EXE);
	EXPECT_FALSE(actual_permissions & bump::FileSystem::GROUP_READ);
	EXPECT_FALSE(actual_permissions & bump::FileSystem::GROUP_WRITE);
	EXPECT_FALSE(actual_permissions & bump::FileSystem::GROUP_EXE);
	EXPECT_FALSE(actual_permissions & bump::FileSystem::OTHERS_READ);
	EXPECT_FALSE(actual_permissions & bump::FileSystem::OTHERS_WRITE);
	EXPECT_FALSE(actual_permissions & bump::FileSystem::OTHERS_EXE);

	// Set permissions on an invalid file
	EXPECT_FALSE(bump::FileSystem::setPermissions("unittest/files/not_valid.txt", permissions));

	// Set permissions on an invalid directory
	EXPECT_FALSE(bump::FileSystem::setPermissions("unittest/not valid", permissions));
}

TEST_F(FileSystemTest, testPermissions)
{
	// Get the permissions of a valid file
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions("unittest/files/output.txt");
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_READ);
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_WRITE);
	EXPECT_FALSE(permissions & bump::FileSystem::OWNER_EXE);
	EXPECT_TRUE(permissions & bump::FileSystem::GROUP_READ);
	EXPECT_FALSE(permissions & bump::FileSystem::GROUP_WRITE);
	EXPECT_FALSE(permissions & bump::FileSystem::GROUP_EXE);
	EXPECT_TRUE(permissions & bump::FileSystem::OTHERS_READ);
	EXPECT_FALSE(permissions & bump::FileSystem::OTHERS_WRITE);
	EXPECT_FALSE(permissions & bump::FileSystem::OTHERS_EXE);

	// Get the permissions of a valid directory
	permissions = bump::FileSystem::permissions("unittest/files");
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_READ);
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_WRITE);
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_EXE);
	EXPECT_TRUE(permissions & bump::FileSystem::GROUP_READ);
	EXPECT_FALSE(permissions & bump::FileSystem::GROUP_WRITE);
	EXPECT_TRUE(permissions & bump::FileSystem::GROUP_EXE);
	EXPECT_TRUE(permissions & bump::FileSystem::OTHERS_READ);
	EXPECT_FALSE(permissions & bump::FileSystem::OTHERS_WRITE);
	EXPECT_TRUE(permissions & bump::FileSystem::OTHERS_EXE);

	// Get the permissions on an invalid file
	EXPECT_THROW(bump::FileSystem::permissions("unittest/files/not_valid.txt"), bump::FileSystemError);

	// Set permissions on an invalid directory
	EXPECT_THROW(bump::FileSystem::permissions("unittest/not valid"), bump::FileSystemError);
}

TEST_F(FileSystemTest, testSetIsReadableByOwner)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OWNER_READ);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_READ);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OWNER_READ);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_READ);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByOwner(path, permissions));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByOwner(path, permissions));
}

TEST_F(FileSystemTest, testSetIsWritableByOwner)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OWNER_WRITE);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_WRITE);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OWNER_WRITE);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_WRITE);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByOwner(path, permissions));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByOwner(path, permissions));
}

TEST_F(FileSystemTest, testSetIsExecutableByOwner)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OWNER_EXE);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_EXE);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OWNER_EXE);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OWNER_EXE);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByOwner(path, permissions));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByOwner(path, permissions));
}

TEST_F(FileSystemTest, testSetIsReadableByGroup)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::GROUP_READ);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::GROUP_READ);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::GROUP_READ);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::GROUP_READ);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByGroup(path, permissions));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByGroup(path, permissions));
}

TEST_F(FileSystemTest, testSetIsWritableByGroup)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::GROUP_WRITE);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::GROUP_WRITE);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::GROUP_WRITE);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::GROUP_WRITE);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByGroup(path, permissions));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByGroup(path, permissions));
}

TEST_F(FileSystemTest, testSetIsExecutableByGroup)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::GROUP_EXE);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::GROUP_EXE);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::GROUP_EXE);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::GROUP_EXE);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByGroup(path, permissions));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByGroup(path, permissions));
}

TEST_F(FileSystemTest, testSetIsReadableByOthers)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OTHERS_READ);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OTHERS_READ);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OTHERS_READ);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OTHERS_READ);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByOthers(path, permissions));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByOthers(path, permissions));
}

TEST_F(FileSystemTest, testSetIsWritableByOthers)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OTHERS_WRITE);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OTHERS_WRITE);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OTHERS_WRITE);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OTHERS_WRITE);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByOthers(path, permissions));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByOthers(path, permissions));
}

TEST_F(FileSystemTest, testSetIsExecutableByOthers)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OTHERS_EXE);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OTHERS_EXE);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE(permissions & bump::FileSystem::OTHERS_EXE);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE(permissions & bump::FileSystem::OTHERS_EXE);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByOthers(path, permissions));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByOthers(path, permissions));
}

TEST_F(FileSystemTest, testSetModifiedDate)
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

	// Set the modified date on a file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setModifiedDate(path, time));
	std::time_t modified_date = bump::FileInfo(path).modifiedDate();
	EXPECT_EQ(time, modified_date);

	// Set the modified date on a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setModifiedDate(path, time));
	modified_date = bump::FileInfo(path).modifiedDate();
	EXPECT_EQ(time, modified_date);

	// Set the modified date on a invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setModifiedDate(path, time));

	// Set the modified date on a invalid directory
	path = "unittest/negative_ghostrider";
	EXPECT_FALSE(bump::FileSystem::setModifiedDate(path, time));
}

TEST_F(FileSystemTest, testModifiedDate)
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
	std::time_t modified_date = bump::FileSystem::modifiedDate(path);
	EXPECT_EQ(time, modified_date);

	// Test a directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setModifiedDate(path, time));
	modified_date = modified_date = bump::FileSystem::modifiedDate(path);
	EXPECT_EQ(time, modified_date);

	// Test a file symlink
	path = "unittest/symlink_files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setModifiedDate(path, time));
	modified_date = modified_date = bump::FileSystem::modifiedDate(path);
	EXPECT_EQ(time, modified_date);

	// Test a directory symlink
	path = "unittest/symlink_directory";
	EXPECT_TRUE(bump::FileSystem::setModifiedDate(path, time));
	modified_date = modified_date = bump::FileSystem::modifiedDate(path);
	EXPECT_EQ(time, modified_date);
}

}	// End of bumpTest namespace
