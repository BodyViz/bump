//
//	FileSystemTest_unix.cpp
//	Bump
//
//	Created by Christian Noon on 12/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/FileSystem.h>
#include <bump/FileSystemError.h>

// bumpTest headers
#include "FileSystemTest.h"

namespace bumpTest {

TEST_F(FileSystemTest, testSetPermissions)
{
	// Set permissions on a valid file
	bump::FileSystem::Permissions permissions = (bump::FileSystem::OWNER_ALL |
												 bump::FileSystem::GROUP_READ |
												 bump::FileSystem::OTHERS_READ);
	EXPECT_TRUE(bump::FileSystem::setPermissions("unittest/files/output.txt", permissions));
	bump::FileSystem::Permissions actual_permissions = bump::FileSystem::permissions("unittest/files/output.txt");
	EXPECT_TRUE((actual_permissions & bump::FileSystem::OWNER_READ) != 0);
	EXPECT_TRUE((actual_permissions & bump::FileSystem::OWNER_WRITE) != 0);
	EXPECT_TRUE((actual_permissions & bump::FileSystem::OWNER_EXE) != 0);
	EXPECT_TRUE((actual_permissions & bump::FileSystem::GROUP_READ) != 0);
	EXPECT_FALSE((actual_permissions & bump::FileSystem::GROUP_WRITE) != 0);
	EXPECT_FALSE((actual_permissions & bump::FileSystem::GROUP_EXE) != 0);
	EXPECT_TRUE((actual_permissions & bump::FileSystem::OTHERS_READ) != 0);
	EXPECT_FALSE((actual_permissions & bump::FileSystem::OTHERS_WRITE) != 0);
	EXPECT_FALSE((actual_permissions & bump::FileSystem::OTHERS_EXE) != 0);

	// Set permissions on a valid directory
	permissions = (bump::FileSystem::OWNER_READ | bump::FileSystem::OWNER_WRITE | bump::FileSystem::OWNER_EXE);
	EXPECT_TRUE(bump::FileSystem::setPermissions("unittest/files", permissions));
	actual_permissions = bump::FileSystem::permissions("unittest/files");
	EXPECT_TRUE((actual_permissions & bump::FileSystem::OWNER_READ) != 0);
	EXPECT_TRUE((actual_permissions & bump::FileSystem::OWNER_WRITE) != 0);
	EXPECT_TRUE((actual_permissions & bump::FileSystem::OWNER_EXE) != 0);
	EXPECT_FALSE((actual_permissions & bump::FileSystem::GROUP_READ) != 0);
	EXPECT_FALSE((actual_permissions & bump::FileSystem::GROUP_WRITE) != 0);
	EXPECT_FALSE((actual_permissions & bump::FileSystem::GROUP_EXE) != 0);
	EXPECT_FALSE((actual_permissions & bump::FileSystem::OTHERS_READ) != 0);
	EXPECT_FALSE((actual_permissions & bump::FileSystem::OTHERS_WRITE) != 0);
	EXPECT_FALSE((actual_permissions & bump::FileSystem::OTHERS_EXE) != 0);

	// Set permissions on an invalid file
	EXPECT_FALSE(bump::FileSystem::setPermissions("unittest/files/not_valid.txt", permissions));

	// Set permissions on an invalid directory
	EXPECT_FALSE(bump::FileSystem::setPermissions("unittest/not valid", permissions));
}

TEST_F(FileSystemTest, testPermissions)
{
	// Get the permissions of a valid file
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions("unittest/files/output.txt");
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_READ) != 0);
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_WRITE) != 0);
	EXPECT_FALSE((permissions & bump::FileSystem::OWNER_EXE) != 0);
	EXPECT_TRUE((permissions & bump::FileSystem::GROUP_READ) != 0);
	EXPECT_FALSE((permissions & bump::FileSystem::GROUP_WRITE) != 0);
	EXPECT_FALSE((permissions & bump::FileSystem::GROUP_EXE) != 0);
	EXPECT_TRUE((permissions & bump::FileSystem::OTHERS_READ) != 0);
	EXPECT_FALSE((permissions & bump::FileSystem::OTHERS_WRITE) != 0);
	EXPECT_FALSE((permissions & bump::FileSystem::OTHERS_EXE) != 0);

	// Get the permissions of a valid directory
	permissions = bump::FileSystem::permissions("unittest/files");
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_READ) != 0);
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_WRITE) != 0);
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_EXE) != 0);
	EXPECT_TRUE((permissions & bump::FileSystem::GROUP_READ) != 0);
	EXPECT_FALSE((permissions & bump::FileSystem::GROUP_WRITE) != 0);
	EXPECT_TRUE((permissions & bump::FileSystem::GROUP_EXE) != 0);
	EXPECT_TRUE((permissions & bump::FileSystem::OTHERS_READ) != 0);
	EXPECT_FALSE((permissions & bump::FileSystem::OTHERS_WRITE) != 0);
	EXPECT_TRUE((permissions & bump::FileSystem::OTHERS_EXE) != 0);

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
	EXPECT_FALSE((permissions & bump::FileSystem::OWNER_READ) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_READ) != 0);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OWNER_READ) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_READ) != 0);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByOwner(path, true));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByOwner(path, true));
}

TEST_F(FileSystemTest, testSetIsWritableByOwner)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OWNER_WRITE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_WRITE) != 0);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OWNER_WRITE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_WRITE) != 0);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByOwner(path, true));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByOwner(path, true));
}

TEST_F(FileSystemTest, testSetIsExecutableByOwner)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OWNER_EXE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_EXE) != 0);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OWNER_EXE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOwner(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OWNER_EXE) != 0);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByOwner(path, true));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByOwner(path, true));
}

TEST_F(FileSystemTest, testSetIsReadableByGroup)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::GROUP_READ) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::GROUP_READ) != 0);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::GROUP_READ) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::GROUP_READ) != 0);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByGroup(path, true));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByGroup(path, true));
}

TEST_F(FileSystemTest, testSetIsWritableByGroup)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::GROUP_WRITE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::GROUP_WRITE) != 0);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::GROUP_WRITE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::GROUP_WRITE) != 0);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByGroup(path, true));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByGroup(path, true));
}

TEST_F(FileSystemTest, testSetIsExecutableByGroup)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::GROUP_EXE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::GROUP_EXE) != 0);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::GROUP_EXE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByGroup(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::GROUP_EXE) != 0);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByGroup(path, true));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByGroup(path, true));
}

TEST_F(FileSystemTest, testSetIsReadableByOthers)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OTHERS_READ) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OTHERS_READ) != 0);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OTHERS_READ) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsReadableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OTHERS_READ) != 0);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByOthers(path, true));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsReadableByOthers(path, true));
}

TEST_F(FileSystemTest, testSetIsWritableByOthers)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OTHERS_WRITE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OTHERS_WRITE) != 0);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OTHERS_WRITE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsWritableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OTHERS_WRITE) != 0);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByOthers(path, true));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsWritableByOthers(path, true));
}

TEST_F(FileSystemTest, testSetIsExecutableByOthers)
{
	// Set permissions on a valid file
	bump::String path = "unittest/files/output.txt";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, false));
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OTHERS_EXE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OTHERS_EXE) != 0);

	// Set permissions on a valid directory
	path = "unittest/files";
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, false));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_FALSE((permissions & bump::FileSystem::OTHERS_EXE) != 0);
	EXPECT_TRUE(bump::FileSystem::setIsExecutableByOthers(path, true));
	permissions = bump::FileSystem::permissions(path);
	EXPECT_TRUE((permissions & bump::FileSystem::OTHERS_EXE) != 0);

	// Set permissions on an invalid file
	path = "unittest/files/not_valid.txt";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByOthers(path, true));

	// Set permissions on an invalid directory
	path = "unittest/not valid";
	EXPECT_FALSE(bump::FileSystem::setIsExecutableByOthers(path, true));
}

}	// End of bumpTest namespace
