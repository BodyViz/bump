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
#include <bump/FileInfo.h>
#include <bump/FileSystem.h>

// C++ headers
#include <fstream>

using namespace bump;

String FileSystem::join(const String& path1, const String& path2)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	joined_path /= path6;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6, const String& path7)
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

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6, const String& path7, const String& path8)
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

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6, const String& path7, const String& path8,
						const String& path9)
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

void FileSystem::setCurrentPath(const String& path)
{
	// Make sure the path is valid
	boost::filesystem::path new_path(path);
	if (!boost::filesystem::exists(new_path))
	{
		String msg = String("The following path is invalid: %1").arg(path);
		throw FileSystemError(msg, BUMP_LOCATION);
	}

	// Set the current path
	boost::filesystem::current_path(boost::filesystem::path(path));
}

String FileSystem::currentPath()
{
	return boost::filesystem::current_path().string();
}

String FileSystem::temporaryPath()
{
	return boost::filesystem::temp_directory_path().string();
}

//====================================================================================
//                               Path Query Methods
//====================================================================================

bool FileSystem::exists(const String& path)
{
	FileInfo path_info(path);
	return path_info.exists();
}

bool FileSystem::isDirectory(const String& path)
{
	FileInfo path_info(path);
	return path_info.isDirectory();
}

bool FileSystem::isFile(const String& path)
{
	FileInfo path_info(path);
	return path_info.isFile();
}

bool FileSystem::isSymbolicLink(const String& path)
{
	FileInfo path_info(path);
	return path_info.isSymbolicLink();
}

//====================================================================================
//                                 Directory Methods
//====================================================================================

bool FileSystem::createDirectory(const String& path)
{
	return boost::filesystem::create_directory(boost::filesystem::path(path));
}

bool FileSystem::createFullDirectoryPath(const String& path)
{
	return boost::filesystem::create_directories(boost::filesystem::path(path));
}

bool FileSystem::removeDirectory(const String& path)
{
	try
	{
		return boost::filesystem::remove(boost::filesystem::path(path));
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool FileSystem::removeDirectoryAndContents(const String& path)
{
	try
	{
		return boost::filesystem::remove_all(boost::filesystem::path(path));
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool FileSystem::copyDirectory(const String& source, const String& destination)
{
	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::copy(source_path, destination_path);
		return true;
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool FileSystem::copyDirectoryAndContents(const String& source, const String& destination)
{
	// Create a FileInfo objects for the source and destination
	FileInfo source_info(source);
	FileInfo destination_info(destination);

	// Make sure the source is a directory
	if (!source_info.isDirectory())
	{
		return false;
	}

	// Make sure the source exists
	if (!source_info.exists())
	{
		return false;
	}

	// Make sure the destination does not exist
	if (destination_info.exists())
	{
		return false;
	}

	// Create the destination directory
	bool created_destination_directory = FileSystem::createFullDirectoryPath(destination);
	if (!created_destination_directory)
	{
		return false;
	}

	// Iterate through the local source directory
	FileInfoList local_source_files = FileSystem::directoryInfoList(source);
	BOOST_FOREACH(const FileInfo& local_source_file, local_source_files)
	{
		bool copied_successfully;

		// Attempt to copy all types of file system objects
		if (local_source_file.isDirectory())
		{
			// Create the local destination directory path
			String filename = local_source_file.filename();
			String local_destination_directory = FileSystem::join(destination, filename);

			// Copy the local source directory to the local destination directory
			copied_successfully = FileSystem::copyDirectoryAndContents(local_source_file.absolutePath(), local_destination_directory);
		}
		else if (local_source_file.isSymbolicLink())
		{
			// Create the local destination symbolic link
			String filename = local_source_file.filename();
			String local_destination_file = FileSystem::join(destination, filename);

			// Copy the local source symbolic link to the local destination
			copied_successfully = FileSystem::copySymbolicLink(local_source_file.absolutePath(), local_destination_file);
		}
		else // local_source_info.isFile()
		{
			// Create the local destination filepath
			String filename = local_source_file.filename();
			String local_destination_file = FileSystem::join(destination, filename);

			// Copy the local source file to the local destination
			copied_successfully = FileSystem::copyFile(local_source_file.absolutePath(), local_destination_file);
		}

		// Fail if we did not copy the file system object successfully
		if (!copied_successfully)
		{
			return false;
		}
	}

	return true;
}

bool FileSystem::renameDirectory(const String& source, const String& destination)
{
	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::rename(source_path, destination_path);
		return true;
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

StringList FileSystem::directoryList(const String& path)
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

FileInfoList FileSystem::directoryInfoList(const String& path)
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

bool FileSystem::createFile(const String& path)
{
	// Make sure the file doesn't already exist
	FileInfo path_info(path);
	if (path_info.exists())
	{
		return false;
	}

	// Create the file and close it
	std::ofstream stream(path.c_str());
	stream.close();

	return true;
}

bool FileSystem::removeFile(const String& path)
{
	return boost::filesystem::remove(boost::filesystem::path(path));
}

bool FileSystem::copyFile(const String& source, const String& destination)
{
	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::copy(source_path, destination_path);
		return true;
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool FileSystem::renameFile(const String& source, const String& destination)
{
	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::rename(source_path, destination_path);
		return true;
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

//====================================================================================
//                               Symbolic Link Methods
//====================================================================================

bool FileSystem::createSymbolicLink(const String& source, const String& destination)
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
	catch (boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool FileSystem::removeSymbolicLink(const String& path)
{
	try
	{
		return boost::filesystem::remove(boost::filesystem::path(path));
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool FileSystem::copySymbolicLink(const String& source, const String& destination)
{
	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::copy_symlink(source_path, destination_path);
		return true;
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}

bool FileSystem::renameSymbolicLink(const String& source, const String& destination)
{
	try
	{
		boost::filesystem::path source_path(source);
		boost::filesystem::path destination_path(destination);
		boost::filesystem::rename(source_path, destination_path);
		return true;
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		return false;
	}
}
