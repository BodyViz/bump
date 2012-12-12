//
//  FileSystem_unix.cpp
//  Bump
//
//  Created by Christian Noon on 12/12/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/filesystem.hpp>

// Bump headers
#include <bump/FileSystem.h>
#include <bump/FileSystemError.h>

namespace bump {

namespace FileSystem {

//====================================================================================
//                                Permissions Methods
//====================================================================================

bool setPermissions(const String& path, Permissions permissions)
{
	// Fail if the path does NOT exist
	if (!exists(path))
	{
		return false;
	}

	// Create a new set of boost permissions matching the bump permissions
	boost::filesystem::perms boost_permissions = boost::filesystem::no_perms;
	if (permissions & OWNER_READ)
	{
        boost_permissions |= boost::filesystem::owner_read;
	}
    if (permissions & OWNER_WRITE)
	{
        boost_permissions |= boost::filesystem::owner_write;
	}
    if (permissions & OWNER_EXE)
	{
        boost_permissions |= boost::filesystem::owner_exe;
	}
    if (permissions & GROUP_READ)
	{
        boost_permissions |= boost::filesystem::group_read;
	}
    if (permissions & GROUP_WRITE)
	{
        boost_permissions |= boost::filesystem::group_write;
	}
    if (permissions & GROUP_EXE)
	{
        boost_permissions |= boost::filesystem::group_exe;
	}
    if (permissions & OTHERS_READ)
	{
        boost_permissions |= boost::filesystem::others_read;
	}
    if (permissions & OTHERS_WRITE)
	{
        boost_permissions |= boost::filesystem::others_write;
	}
    if (permissions & OTHERS_EXE)
	{
        boost_permissions |= boost::filesystem::others_exe;
	}

	// Use the boost filesystem to modify the permissions
	try
	{
		boost::filesystem::permissions(boost::filesystem::path(path.c_str()), boost_permissions);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
	{
		return false;
	}
}

Permissions permissions(const String& path)
{
	// Make sure the path exists or throw an exception
	if (!exists(path))
	{
		String msg = String("The following path is not valid: %1").arg(path);
		throw FileSystemError(msg, BUMP_LOCATION);
	}

	// Get the permissions using boost
	boost::filesystem::file_status status = boost::filesystem::status(boost::filesystem::path(path.c_str()));
	boost::filesystem::perms boost_permissions = status.permissions();

	// Create a bump permissions object by or'ing in all the boost permissions
	Permissions permissions = 0;
	if (boost_permissions & boost::filesystem::owner_read)
	{
        permissions |= OWNER_READ;
	}
	if (boost_permissions & boost::filesystem::owner_write)
	{
        permissions |= OWNER_WRITE;
	}
	if (boost_permissions & boost::filesystem::owner_exe)
	{
        permissions |= OWNER_EXE;
	}
	if (boost_permissions & boost::filesystem::group_read)
	{
        permissions |= GROUP_READ;
	}
	if (boost_permissions & boost::filesystem::group_write)
	{
        permissions |= GROUP_WRITE;
	}
	if (boost_permissions & boost::filesystem::group_exe)
	{
        permissions |= GROUP_EXE;
	}
	if (boost_permissions & boost::filesystem::others_read)
	{
        permissions |= OTHERS_READ;
	}
	if (boost_permissions & boost::filesystem::others_write)
	{
        permissions |= OTHERS_WRITE;
	}
	if (boost_permissions & boost::filesystem::others_exe)
	{
        permissions |= OTHERS_EXE;
	}

	return permissions;
}

bool setIsReadableByOwner(const String& path, bool isReadable)
{
	Permissions permissions;
	try
	{
		permissions = FileSystem::permissions(path);
	}
	catch (const FileSystemError& /*e*/)
	{
		return false;
	}

	isReadable ? permissions |= OWNER_READ : permissions &= ~OWNER_READ;
	return setPermissions(path, permissions);
}

bool setIsWritableByOwner(const String& path, bool isWritable)
{
	Permissions permissions;
	try
	{
		permissions = FileSystem::permissions(path);
	}
	catch (const FileSystemError& /*e*/)
	{
		return false;
	}

	isWritable ? permissions |= OWNER_WRITE : permissions &= ~OWNER_WRITE;
	return setPermissions(path, permissions);
}

bool setIsExecutableByOwner(const String& path, bool isExecutable)
{
	Permissions permissions;
	try
	{
		permissions = FileSystem::permissions(path);
	}
	catch (const FileSystemError& /*e*/)
	{
		return false;
	}

	isExecutable ? permissions |= OWNER_EXE : permissions &= ~OWNER_EXE;
	return setPermissions(path, permissions);
}

bool setIsReadableByGroup(const String& path, bool isReadable)
{
	Permissions permissions;
	try
	{
		permissions = FileSystem::permissions(path);
	}
	catch (const FileSystemError& /*e*/)
	{
		return false;
	}

	isReadable ? permissions |= GROUP_READ : permissions &= ~GROUP_READ;
	return setPermissions(path, permissions);
}

bool setIsWritableByGroup(const String& path, bool isWritable)
{
	Permissions permissions;
	try
	{
		permissions = FileSystem::permissions(path);
	}
	catch (const FileSystemError& /*e*/)
	{
		return false;
	}

	isWritable ? permissions |= GROUP_WRITE : permissions &= ~GROUP_WRITE;
	return setPermissions(path, permissions);
}

bool setIsExecutableByGroup(const String& path, bool isExecutable)
{
	Permissions permissions;
	try
	{
		permissions = FileSystem::permissions(path);
	}
	catch (const FileSystemError& /*e*/)
	{
		return false;
	}

	isExecutable ? permissions |= GROUP_EXE : permissions &= ~GROUP_EXE;
	return setPermissions(path, permissions);
}

bool setIsReadableByOthers(const String& path, bool isReadable)
{
	Permissions permissions;
	try
	{
		permissions = FileSystem::permissions(path);
	}
	catch (const FileSystemError& /*e*/)
	{
		return false;
	}

	isReadable ? permissions |= OTHERS_READ : permissions &= ~OTHERS_READ;
	return setPermissions(path, permissions);
}

bool setIsWritableByOthers(const String& path, bool isWritable)
{
	Permissions permissions;
	try
	{
		permissions = FileSystem::permissions(path);
	}
	catch (const FileSystemError& /*e*/)
	{
		return false;
	}

	isWritable ? permissions |= OTHERS_WRITE : permissions &= ~OTHERS_WRITE;
	return setPermissions(path, permissions);
}

bool setIsExecutableByOthers(const String& path, bool isExecutable)
{
	Permissions permissions;
	try
	{
		permissions = FileSystem::permissions(path);
	}
	catch (const FileSystemError& /*e*/)
	{
		return false;
	}

	isExecutable ? permissions |= OTHERS_EXE : permissions &= ~OTHERS_EXE;
	return setPermissions(path, permissions);
}

}	// End of FileSystem namespace

}	// End of bump namespace
