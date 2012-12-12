//
//	FileSystemTest_win.cpp
//	Bump
//
//	Created by Christian Noon on 12/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/FileSystem.h>
#include <bump/NotImplementedError.h>

// bumpTest headers
#include "FileSystemTest.h"

namespace bumpTest {

TEST_F(FileSystemTest, testSetPermissions)
{
	EXPECT_THROW(bump::FileSystem::setPermissions("", bump::FileSystem::ALL_ALL), bump::NotImplementedError);
}

TEST_F(FileSystemTest, testPermissions)
{
	EXPECT_THROW(bump::FileSystem::permissions(""), bump::NotImplementedError);
}

TEST_F(FileSystemTest, testSetIsReadableByOwner)
{
	EXPECT_THROW(bump::FileSystem::setIsReadableByOwner("", true), bump::NotImplementedError);
}

TEST_F(FileSystemTest, testSetIsWritableByOwner)
{
	EXPECT_THROW(bump::FileSystem::setIsWritableByOwner("", true), bump::NotImplementedError);
}

TEST_F(FileSystemTest, testSetIsExecutableByOwner)
{
	EXPECT_THROW(bump::FileSystem::setIsExecutableByOwner("", true), bump::NotImplementedError);
}

TEST_F(FileSystemTest, testSetIsReadableByGroup)
{
	EXPECT_THROW(bump::FileSystem::setIsReadableByGroup("", true), bump::NotImplementedError);
}

TEST_F(FileSystemTest, testSetIsWritableByGroup)
{
	EXPECT_THROW(bump::FileSystem::setIsWritableByGroup("", true), bump::NotImplementedError);
}

TEST_F(FileSystemTest, testSetIsExecutableByGroup)
{
	EXPECT_THROW(bump::FileSystem::setIsExecutableByGroup("", true), bump::NotImplementedError);
}

TEST_F(FileSystemTest, testSetIsReadableByOthers)
{
	EXPECT_THROW(bump::FileSystem::setIsReadableByOthers("", true), bump::NotImplementedError);
}

TEST_F(FileSystemTest, testSetIsWritableByOthers)
{
	EXPECT_THROW(bump::FileSystem::setIsWritableByOthers("", true), bump::NotImplementedError);
}

TEST_F(FileSystemTest, testSetIsExecutableByOthers)
{
	EXPECT_THROW(bump::FileSystem::setIsExecutableByOthers("", true), bump::NotImplementedError);
}

}	// End of bumpTest namespace
