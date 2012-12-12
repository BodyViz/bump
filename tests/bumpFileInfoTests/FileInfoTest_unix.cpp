//
//	FileInfoTest_unix.cpp
//	Bump
//
//	Created by Christian Noon on 12/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Environment.h>
#include <bump/FileInfo.h>
#include <bump/FileSystemError.h>

// bumpTest headers
#include "FileInfoTest.h"

namespace bumpTest {

TEST_F(FileInfoTest, testFileSize)
{
	// Test valid files
	EXPECT_EQ(0, bump::FileInfo("unittest/files/output.txt").fileSize());
	EXPECT_EQ(129, bump::FileInfo("unittest/files/info.xml").fileSize());

	// Test valid file symlinks
	EXPECT_EQ(0, bump::FileInfo("unittest/symlink_files/output.txt").fileSize());
	EXPECT_EQ(129, bump::FileInfo("unittest/symlink_files/info.xml").fileSize());

	// Test valid directories
	EXPECT_THROW(bump::FileInfo("unittest/files").fileSize(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/symlink_files").fileSize(), bump::FileSystemError);

	// Test valid directory symlink
	EXPECT_THROW(bump::FileInfo("unittest/symlink_directory").fileSize(), bump::FileSystemError);

	// Test invalid paths
	EXPECT_THROW(bump::FileInfo("unittest/does/not/exist/output.txt").fileSize(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/try/again").fileSize(), bump::FileSystemError);
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
}

TEST_F(FileInfoTest, testOwnerId)
{
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
}

TEST_F(FileInfoTest, testGroup)
{
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
}

TEST_F(FileInfoTest, testGroupId)
{
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
}

}	// End of bumpTest namespace
