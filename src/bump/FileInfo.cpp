//
//  FileInfo.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/filesystem.hpp>

// Bump headers
#include <bump/Environment.h>
#include <bump/Exception.h>
#include <bump/FileInfo.h>

// Unix headers
#ifndef _WIN32
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#endif

using namespace bump;

FileInfo::FileInfo(const String& path) :
	_path(path)
{
	;
}

FileInfo::~FileInfo()
{
	;
}

//====================================================================================
//                              Path Query Methods
//====================================================================================

bool FileInfo::exists() const
{
	// First use the exists function
	bool exists = boost::filesystem::exists(_path);
	if (exists)
	{
		return true;
	}

	// Sometimes the exists function doesn't work properly for symbolic links, so
	// let's use the symlink check as well.
	if (isSymbolicLink())
	{
		return true;
	}

	return false;
}

unsigned long long FileInfo::fileSize() const
{
	// Throw a FileSystemError if the path is not valid
	_validatePath();

	// Throw a FileSystemError if the path is not a file
	if (!isFile())
	{
		String msg = String("The following path is not a file: %1").arg(_path.string());
		throw FileSystemError(msg, BUMP_LOCATION);
	}

	return boost::filesystem::file_size(_path);
}

bool FileInfo::isAbsolute() const
{
	return _path.has_root_path();
}

bool FileInfo::isRelative() const
{
	return !_path.has_root_path();
}

bool FileInfo::isDirectory() const
{
	return boost::filesystem::is_directory(_path);
}

bool FileInfo::isFile() const
{
	return boost::filesystem::is_regular_file(_path);
}

bool FileInfo::isSymbolicLink() const
{
	return boost::filesystem::is_symlink(_path);
}

bool FileInfo::isEmpty() const
{
	// Make sure the path is valid
	_validatePath();

	// Try to check if the path is empty. This can fail in the event that we don't have
	// the proper permissions to read the file system object.
	try
	{
		return boost::filesystem::is_empty(_path);
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		throw FileSystemError("Do not have permission to check if empty", BUMP_LOCATION);
	}
}

bool FileInfo::isHidden() const
{
	// It is not a hidden file if it isn't even a file
	if (exists())
	{
		String filename = _path.filename().string();
		return filename.startsWith(".");
	}

	return false;
}

//====================================================================================
//                          Path Decomposition Methods
//====================================================================================

String FileInfo::absolutePath() const
{
	return boost::filesystem::absolute(_path).string();
}

String FileInfo::canonicalPath() const
{
	_validatePath();
	return boost::filesystem::canonical(_path).string();
}

String FileInfo::parentPath() const
{
	return _path.parent_path().string();
}

String FileInfo::path() const
{
	return _path.string();
}

String FileInfo::basename() const
{
	if (isDirectory())
	{
		return filename();
	}
	else
	{
		String basename = _path.stem().string();
		if (basename.startsWith("."))
		{
			String temp = basename.right(basename.length() - 1);
			if (temp.contains("."))
			{
				basename = basename.left(temp.indexOf(".") + 1);
			}
		}
		else
		{
			if (basename.contains("."))
			{
				basename = basename.left(basename.indexOf("."));
			}
		}

		return basename;
	}
}

String FileInfo::completeBasename() const
{
	if (isDirectory())
	{
		return filename();
	}
	else
	{
		return _path.stem().string();
	}
}

String FileInfo::extension() const
{
	if (isDirectory())
	{
		return String();
	}
	else
	{
		String extension = _path.extension().string();
		if (extension.startsWith("."))
		{
			extension = extension.section(1);
		}

		return extension;
	}
}

String FileInfo::completeExtension() const
{
	if (isDirectory())
	{
		return String();
	}
	else
	{
		String filename = this->filename();
		if (filename.contains("."))
		{
			String basename = this->basename() << ".";
			return filename.remove(basename);
		}
		else
		{
			return String();
		}
	}
}

String FileInfo::filename() const
{
	return _path.filename().string();
}

//====================================================================================
//                           Permissions Query Methods
//====================================================================================

bool FileInfo::isReadableByUser() const
{
	// If on windows, simply return the owner permissions
#ifdef _WIN32
	return this->isReadableByOwner();
#endif

	// Since we're not on windows, we need to figure out if we're the owner of the file
	String owner = this->owner();
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
	// If on windows, simply return the owner permissions
#ifdef _WIN32
	return this->isWritableByOwner();
#endif

	// Since we're not on windows, we need to figure out if we're the owner of the file
	String owner = this->owner();
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
	// If on windows, simply return the owner permissions
#ifdef _WIN32
	return this->isExecutableByOwner();
#endif

	// Since we're not on windows, we need to figure out if we're the owner of the file
	String owner = this->owner();
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
	bool is_readable = permissions & boost::filesystem::owner_read;

	return is_readable;
}

bool FileInfo::isWritableByOwner() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_writable = permissions & boost::filesystem::owner_write;

	return is_writable;
}

bool FileInfo::isExecutableByOwner() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_executable = permissions & boost::filesystem::owner_exe;

	return is_executable;
}

bool FileInfo::isReadableByGroup() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_readable = permissions & boost::filesystem::group_read;

	return is_readable;
}

bool FileInfo::isWritableByGroup() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_writable = permissions & boost::filesystem::group_write;

	return is_writable;
}

bool FileInfo::isExecutableByGroup() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_executable = permissions & boost::filesystem::group_exe;

	return is_executable;
}

bool FileInfo::isReadableByOthers() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_readable = permissions & boost::filesystem::others_read;

	return is_readable;
}

bool FileInfo::isWritableByOthers() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_writable = permissions & boost::filesystem::others_write;

	return is_writable;
}

bool FileInfo::isExecutableByOthers() const
{
	boost::filesystem::file_status status = boost::filesystem::status(_path);
	boost::filesystem::perms permissions = status.permissions();
	bool is_executable = permissions & boost::filesystem::others_exe;

	return is_executable;
}

String FileInfo::owner() const
{
	// Send back an empty string if we're on windows
#ifdef _WIN32
	return String();
#endif

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
	// Send back -1 if we're on windows
#ifdef _WIN32
	return -1;
#endif

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
	// Send back an empty string if we're on windows
#ifdef _WIN32
	return String();
#endif

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
	// Send back -1 if we're on windows
#ifdef _WIN32
	return -1;
#endif

	// Make sure we have a valid path
	_validatePath();

	// Since we're on unix, use the native unix calls to dig out the group id
	String filepath = this->canonicalPath();
	struct stat info;
	stat(filepath.c_str(), &info);
	struct group* group_uid = getgrgid(info.st_gid);
	return group_uid->gr_gid;
}

//====================================================================================
//                              Date Query Methods
//====================================================================================

std::time_t FileInfo::modifiedDate() const
{
	_validatePath();
	return boost::filesystem::last_write_time(_path);
}

void FileInfo::_validatePath() const
{
	if (!boost::filesystem::exists(_path))
	{
		String msg = String("The following path is invalid: %1").arg(_path.string());
		throw FileSystemError(msg, BUMP_LOCATION);
	}
}
