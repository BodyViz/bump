//
//	FileInfoTest_win.cpp
//	Bump
//
//	Created by Christian Noon on 12/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/FileInfo.h>
#include <bump/FileSystemError.h>
#include <bump/NotImplementedError.h>

// bumpTest headers
#include "FileInfoTest.h"

namespace bumpTest {

TEST_F(FileInfoTest, testFileSize)
{
	// Test valid files
	EXPECT_EQ(0, bump::FileInfo("unittest/files/output.txt").fileSize());
	EXPECT_EQ(130, bump::FileInfo("unittest/files/info.xml").fileSize());

	// Test valid file symlinks
	EXPECT_EQ(0, bump::FileInfo("unittest/symlink_files/output.txt").fileSize());
	EXPECT_EQ(130, bump::FileInfo("unittest/symlink_files/info.xml").fileSize());

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

	// Test invalid paths
	EXPECT_THROW(bump::FileInfo("unittest/not/valid/output.txt").isEmpty(), bump::FileSystemError);
	EXPECT_THROW(bump::FileInfo("unittest/not/valid").isEmpty(), bump::FileSystemError);
	
	// Test an empty path (which ends up being the current path)
	EXPECT_FALSE(bump::FileInfo("").isEmpty());
}

TEST_F(FileInfoTest, testIsReadableByUser)
{
	EXPECT_THROW(bump::FileInfo("").isReadableByUser(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsWritableByUser)
{
	EXPECT_THROW(bump::FileInfo("").isWritableByUser(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsExecutableByUser)
{
	EXPECT_THROW(bump::FileInfo("").isExecutableByUser(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsReadableByOwner)
{
	EXPECT_THROW(bump::FileInfo("").isReadableByOwner(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsWritableByOwner)
{
	EXPECT_THROW(bump::FileInfo("").isWritableByOwner(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsExecutableByOwner)
{
	EXPECT_THROW(bump::FileInfo("").isExecutableByOwner(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsReadableByGroup)
{
	EXPECT_THROW(bump::FileInfo("").isReadableByGroup(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsWritableByGroup)
{
	EXPECT_THROW(bump::FileInfo("").isWritableByGroup(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsExecutableByGroup)
{
	EXPECT_THROW(bump::FileInfo("").isExecutableByGroup(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsReadableByOthers)
{
	EXPECT_THROW(bump::FileInfo("").isReadableByOthers(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsWritableByOthers)
{
	EXPECT_THROW(bump::FileInfo("").isWritableByOthers(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testIsExecutableByOthers)
{
	EXPECT_THROW(bump::FileInfo("").isWritableByOthers(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testOwner)
{
	EXPECT_THROW(bump::FileInfo("").owner(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testOwnerId)
{
	EXPECT_THROW(bump::FileInfo("").ownerId(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testGroup)
{
	EXPECT_THROW(bump::FileInfo("").group(), bump::NotImplementedError);
}

TEST_F(FileInfoTest, testGroupId)
{
	EXPECT_THROW(bump::FileInfo("").groupId(), bump::NotImplementedError);
}

}	// End of bumpTest namespace
