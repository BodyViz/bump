//
//  FileSystem.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

// Bump headers
#include <bump/Exception.h>
#include <bump/FileSystem.h>

// C++ headers
#include <fstream>

namespace bump {

namespace FileSystem {

String join(const String& path1, const String& path2)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	return joined_path.string();
}

String join(const String& path1, const String& path2, const String& path3)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	return joined_path.string();
}

String join(const String& path1, const String& path2, const String& path3, const String& path4)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	return joined_path.string();
}

String join(const String& path1, const String& path2, const String& path3, const String& path4, const String& path5)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	return joined_path.string();
}

String join(const String& path1, const String& path2, const String& path3, const String& path4, const String& path5,
			const String& path6)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	joined_path /= path6;
	return joined_path.string();
}

String join(const String& path1, const String& path2, const String& path3, const String& path4, const String& path5,
			const String& path6, const String& path7)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	joined_path /= path6;
	joined_path /= path7;
	return joined_path.string();
}

String join(const String& path1, const String& path2, const String& path3, const String& path4, const String& path5,
			const String& path6, const String& path7, const String& path8)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	joined_path /= path6;
	joined_path /= path7;
	joined_path /= path8;
	return joined_path.string();
}

String join(const String& path1, const String& path2, const String& path3, const String& path4, const String& path5,
			const String& path6, const String& path7, const String& path8, const String& path9)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	joined_path /= path6;
	joined_path /= path7;
	joined_path /= path8;
	joined_path /= path9;
	return joined_path.string();
}

//====================================================================================
//                                System Path Methods
//====================================================================================

bool setCurrentPath(const String& path)
{
	// Set the current path
	try
	{
		boost::filesystem::current_path(boost::filesystem::path(path));
		return true;
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

String currentPath()
{
	return boost::filesystem::current_path().string();
}

String temporaryPath()
{
	return boost::filesystem::temp_directory_path().string();
}

//====================================================================================
//                               Path Query Methods
//====================================================================================

bool exists(const String& path)
{
	FileInfo path_info(path);
	return path_info.exists();
}

bool isDirectory(const String& path)
{
	FileInfo path_info(path);
	return path_info.isDirectory();
}

bool isFile(const String& path)
{
	FileInfo path_info(path);
	return path_info.isFile();
}

bool isSymbolicLink(const String& path)
{
	FileInfo path_info(path);
	return path_info.isSymbolicLink();
}

//====================================================================================
//                                 Directory Methods
//====================================================================================

bool createDirectory(const String& path)
{
	try
	{
		return boost::filesystem::create_directory(boost::filesystem::path(path));
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool createFullDirectoryPath(const String& path)
{
	return boost::filesystem::create_directories(boost::filesystem::path(path));
}

bool removeDirectory(const String& path)
{
	// Fail if the path is not a directory
	if (!FileInfo(path).isDirectory())
	{
		return false;
	}

	try
	{
		return boost::filesystem::remove(boost::filesystem::path(path));
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool removeDirectoryAndContents(const String& path)
{
	// Fail if the path is not a directory
	if (!FileInfo(path).isDirectory())
	{
		return false;
	}

	try
	{
		return boost::filesystem::remove_all(boost::filesystem::path(path));
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool copyDirectory(const String& source, const String& destination)
{
	// Fail if the source path is not a directory
	if (!FileInfo(source).isDirectory())
	{
		return false;
	}

	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::copy(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool copyDirectoryAndContents(const String& source, const String& destination)
{
	// Fail if the source path is not a directory
	if (!FileInfo(source).isDirectory())
	{
		return false;
	}

	// Create a FileInfo objects for the source and destination
	FileInfo source_info(source);
	FileInfo destination_info(destination);

	// Make sure the destination does not exist
	if (destination_info.exists())
	{
		return false;
	}

	// Create the destination directory
	bool created_destination_directory = createFullDirectoryPath(destination);
	if (!created_destination_directory)
	{
		return false;
	}

	// Iterate through the local source directory
	FileInfoList local_source_files = directoryInfoList(source);
	BOOST_FOREACH(const FileInfo& local_source_file, local_source_files)
	{
		bool copied_successfully;

		// Attempt to copy all types of file system objects
		if (local_source_file.isDirectory())
		{
			// Create the local destination directory path
			String filename = local_source_file.filename();
			String local_destination_directory = join(destination, filename);

			// Copy the local source directory to the local destination directory
			copied_successfully = copyDirectoryAndContents(local_source_file.absolutePath(), local_destination_directory);
		}
		else if (local_source_file.isSymbolicLink())
		{
			// Create the local destination symbolic link
			String filename = local_source_file.filename();
			String local_destination_file = join(destination, filename);

			// Copy the local source symbolic link to the local destination
			copied_successfully = copySymbolicLink(local_source_file.absolutePath(), local_destination_file);
		}
		else // local_source_info.isFile()
		{
			// Create the local destination filepath
			String filename = local_source_file.filename();
			String local_destination_file = join(destination, filename);

			// Copy the local source file to the local destination
			copied_successfully = copyFile(local_source_file.absolutePath(), local_destination_file);
		}

		// Fail if we did not copy the file system object successfully
		if (!copied_successfully)
		{
			return false;
		}
	}

	return true;
}

bool renameDirectory(const String& source, const String& destination)
{
	// Fail if the source path is not a directory
	if (!FileInfo(source).isDirectory())
	{
		return false;
	}

	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::rename(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

StringList directoryList(const String& path)
{
	// Throw an exception if the path does not exist
	if (!FileInfo(path).exists())
	{
		String msg = String("The following path is not valid: %1").arg(path);
		throw FileSystemError(msg, BUMP_LOCATION);
	}

	// Throw an exception if the path is not a directory
	if (!FileInfo(path).isDirectory())
	{
		String msg = String("The following path is not a directory: %1").arg(path);
		throw FileSystemError(msg, BUMP_LOCATION);
	}

	// Create a path and two directory iterators
	boost::filesystem::path directory_path(path);
	boost::filesystem::directory_iterator iter(directory_path);
	boost::filesystem::directory_iterator end_iter;

	// Iterate through the directory collecting all the item paths as strings
	StringSet directory_set;
	BOOST_FOREACH(const boost::filesystem::path& item, std::make_pair(iter, end_iter))
	{
		directory_set.insert(item.string());
	}

	// Build a string list from the sorted string set
	StringList directory_list;
	BOOST_FOREACH(const String& item, directory_set)
	{
		directory_list.push_back(item);
	}

	return directory_list;
}

FileInfoList directoryInfoList(const String& path)
{
	// Throw an exception if the path does not exist
	if (!FileInfo(path).exists())
	{
		String msg = String("The following path is not valid: %1").arg(path);
		throw FileSystemError(msg, BUMP_LOCATION);
	}

	// Throw an exception if the path is not a directory
	if (!FileInfo(path).isDirectory())
	{
		String msg = String("The following path is not a directory: %1").arg(path);
		throw FileSystemError(msg, BUMP_LOCATION);
	}

	// Create a path and two directory iterators
	boost::filesystem::path directory_path(path);
	boost::filesystem::directory_iterator iter(directory_path);
	boost::filesystem::directory_iterator end_iter;

	// Iterate through the directory collecting all the item paths as strings
	StringSet directory_set;
	BOOST_FOREACH(const boost::filesystem::path& item, std::make_pair(iter, end_iter))
	{
		directory_set.insert(item.string());
	}

	// Build a file info list from the sorted string set
	FileInfoList directory_list;
	BOOST_FOREACH(const String& item, directory_set)
	{
		FileInfo item_info(item);
		directory_list.push_back(item_info);
	}

	return directory_list;
}

//====================================================================================
//                                   File Methods
//====================================================================================

bool createFile(const String& path)
{
	// Make sure the file doesn't already exist
	FileInfo path_info(path);
	if (path_info.exists())
	{
		return false;
	}

	// Create the file and close it
	std::ofstream stream(path.c_str());
	bool success = !stream.fail();
	stream.close();

	return success;
}

bool removeFile(const String& path)
{
	// Fail if path is not a file
	if (!FileInfo(path).isFile())
	{
		return false;
	}

	return boost::filesystem::remove(boost::filesystem::path(path));
}

bool copyFile(const String& source, const String& destination)
{
	// Fail if source is not a file
	if (!FileInfo(source).isFile())
	{
		return false;
	}

	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::copy(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool renameFile(const String& source, const String& destination)
{
	// Fail if source is not a file
	if (!FileInfo(source).isFile())
	{
		return false;
	}

	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::rename(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

//====================================================================================
//                               Symbolic Link Methods
//====================================================================================

bool createSymbolicLink(const String& source, const String& destination)
{
	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		if (boost::filesystem::is_directory(source_path))
		{
			boost::filesystem::create_directory_symlink(source_path, destination_path);
		}
		else
		{
			boost::filesystem::create_symlink(source_path, destination_path);
		}

		return true;
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool removeSymbolicLink(const String& path)
{
	// Fail if path is not a symbolic link
	if (!FileInfo(path).isSymbolicLink())
	{
		return false;
	}

	try
	{
		return boost::filesystem::remove(boost::filesystem::path(path));
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool copySymbolicLink(const String& source, const String& destination)
{
	// Fail if source is not a symbolic link
	if (!FileInfo(source).isSymbolicLink())
	{
		return false;
	}

	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::copy_symlink(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool renameSymbolicLink(const String& source, const String& destination)
{
	// Fail if source is not a symbolic link
	if (!FileInfo(source).isSymbolicLink())
	{
		return false;
	}

	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::rename(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

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
		boost::filesystem::permissions(boost::filesystem::path(path), boost_permissions);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& e)
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
	boost::filesystem::file_status status = boost::filesystem::status(boost::filesystem::path(path));
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
	catch (const FileSystemError& e)
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
	catch (const FileSystemError& e)
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
	catch (const FileSystemError& e)
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
	catch (const FileSystemError& e)
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
	catch (const FileSystemError& e)
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
	catch (const FileSystemError& e)
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
	catch (const FileSystemError& e)
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
	catch (const FileSystemError& e)
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
	catch (const FileSystemError& e)
	{
		return false;
	}

	isExecutable ? permissions |= OTHERS_EXE : permissions &= ~OTHERS_EXE;
	return setPermissions(path, permissions);
}

//====================================================================================
//                                  Date Methods
//====================================================================================

bool setModifiedDate(const String& path, const std::time_t& date)
{
	// Fail if path does NOT exist
	if (!exists(path))
	{
		return false;
	}

	try
	{
		boost::filesystem::last_write_time(boost::filesystem::path(path), date);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

}	// End of FileSystem namespace

}	// End of bump namespace
