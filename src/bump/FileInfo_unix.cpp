//
//  FileInfo_unix.cpp
//  Bump
//
//  Created by Christian Noon on 12/12/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/filesystem.hpp>

// Bump headers
#include <bump/Environment.h>
#include <bump/FileInfo.h>
#include <bump/FileSystem.h>
#include <bump/FileSystemError.h>

// Unix headers
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

using namespace bump;

//====================================================================================
//                           Permissions Query Methods
//====================================================================================

bool FileInfo::isReadableByUser() const
{
	// Figure out if we're the owner of the file
	String owner;
	try
	{
		owner = this->owner();
	}
	catch (const bump::FileSystemError& /*e*/)
	{
		return false;
	}

	// Find the current user and compare against the owner
	String current_user = Environment::currentUsername();
	if (owner == current_user)
	{
		return this->isReadableByOwner();
	}
	else
	{
		return this->isReadableByOthers();
	}
}

bool FileInfo::isWritableByUser() const
{
	// Figure out if we're the owner of the file
	String owner;
	try
	{
		owner = this->owner();
	}
	catch (const bump::FileSystemError& /*e*/)
	{
		return false;
	}

	// Find the current user and compare against the owner
	String current_user = Environment::currentUsername();
	if (owner == current_user)
	{
		return this->isWritableByOwner();
	}
	else
	{
		return this->isWritableByOthers();
	}
}

bool FileInfo::isExecutableByUser() const
{
	// Figure out if we're the owner of the file
	String owner;
	try
	{
		owner = this->owner();
	}
	catch (const bump::FileSystemError& /*e*/)
	{
		return false;
	}

	// Find the current user and compare against the owner
	String current_user = Environment::currentUsername();
	if (owner == current_user)
	{
		return this->isExecutableByOwner();
	}
	else
	{
		return this->isExecutableByOthers();
	}
}

bool FileInfo::isReadableByOwner() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_readable = (permissions & boost::filesystem::owner_read) != 0;

	return is_readable;
}

bool FileInfo::isWritableByOwner() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_writable = (permissions & boost::filesystem::owner_write) != 0;

	return is_writable;
}

bool FileInfo::isExecutableByOwner() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_executable = (permissions & boost::filesystem::owner_exe) != 0;

	return is_executable;
}

bool FileInfo::isReadableByGroup() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_readable = (permissions & boost::filesystem::group_read) != 0;

	return is_readable;
}

bool FileInfo::isWritableByGroup() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_writable = (permissions & boost::filesystem::group_write) != 0;

	return is_writable;
}

bool FileInfo::isExecutableByGroup() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_executable = (permissions & boost::filesystem::group_exe) != 0;

	return is_executable;
}

bool FileInfo::isReadableByOthers() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_readable = (permissions & boost::filesystem::others_read) != 0;

	return is_readable;
}

bool FileInfo::isWritableByOthers() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_writable = (permissions & boost::filesystem::others_write) != 0;

	return is_writable;
}

bool FileInfo::isExecutableByOthers() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_executable = (permissions & boost::filesystem::others_exe) != 0;

	return is_executable;
}

String FileInfo::owner() const
{
	// Make sure we have a valid path
	_validatePath();

	// Since we're on unix, use the native unix calls to dig out the username
	String filepath = this->canonicalPath();
	struct stat info;
	stat(filepath.c_str(), &info);
	struct passwd* password_uid = getpwuid(info.st_uid);

	return password_uid->pw_name;
}

unsigned int FileInfo::ownerId() const
{
	// Make sure we have a valid path
	_validatePath();

	// Since we're on unix, use the native unix calls to dig out the user id
	String filepath = this->canonicalPath();
	struct stat info;
	stat(filepath.c_str(), &info);
	struct passwd* password_uid = getpwuid(info.st_uid);

	return password_uid->pw_uid;
}

String FileInfo::group() const
{
	// Make sure we have a valid path
	_validatePath();

	// Since we're on unix, use the native unix calls to dig out the group name
	String filepath = this->canonicalPath();
	struct stat info;
	stat(filepath.c_str(), &info);
	struct group* group_uid = getgrgid(info.st_gid);

	return group_uid->gr_name;
}

unsigned int FileInfo::groupId() const
{	
	// Make sure we have a valid path
	_validatePath();

	// Since we're on unix, use the native unix calls to dig out the group id
	String filepath = this->canonicalPath();
	struct stat info;
	stat(filepath.c_str(), &info);
	struct group* group_uid = getgrgid(info.st_gid);

	return group_uid->gr_gid;
}
