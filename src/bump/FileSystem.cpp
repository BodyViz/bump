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
#include <bump/FileSystem.h>
#include <bump/FileSystemError.h>

// C++ headers
#include <fstream>

namespace bump {

namespace FileSystem {

//====================================================================================
//                               Path Coversion Methods
//====================================================================================

String convertToWindowsPath(String path)
{
	// Replace a forward slash next to a backward slash with a forward slash
	String converted = path.replace("/\\", "/");

	// Replace a backward slash next to a forward slash with a forward slash
	converted = path.replace("\\/", "/");

	// Replace all duplicate forward slashes with a single forward slash
	converted = path.replace("///", "/");
	converted = path.replace("//", "/");

	// Replace all duplicate backward slashes with a single backward slash
	converted = path.replace("\\\\\\", "\\");
	converted = path.replace("\\\\", "\\");

	// Convert all forward slashes to backward slashes
	converted = path.replace("/", "\\");

	return converted;
}

String convertToUnixPath(String path)
{
	// Replace a forward slash next to a backward slash with a forward slash
	String converted = path.replace("/\\", "/");

	// Replace a backward slash next to a forward slash with a forward slash
	converted = path.replace("\\/", "/");

	// Replace all duplicate forward slashes with a single forward slash
	converted = path.replace("///", "/");
	converted = path.replace("//", "/");

	// Replace all duplicate backward slashes with a single backward slash
	converted = path.replace("\\\\\\", "\\");
	converted = path.replace("\\\\", "\\");

	// Convert all backward slashes to forward slashes
	converted = path.replace("\\", "/");

	return converted;
}

String join(const String& path1, const String& path2)
{
	boost::filesystem::path joined_path(path1.c_str());
	joined_path /= path2.c_str();
	return convertToUnixPath(joined_path.string());
}

String join(const String& path1, const String& path2, const String& path3)
{
	boost::filesystem::path joined_path(path1.c_str());
	joined_path /= path2.c_str();
	joined_path /= path3.c_str();
	return convertToUnixPath(joined_path.string());
}

String join(const String& path1, const String& path2, const String& path3, const String& path4)
{
	boost::filesystem::path joined_path(path1.c_str());
	joined_path /= path2.c_str();
	joined_path /= path3.c_str();
	joined_path /= path4.c_str();
	return convertToUnixPath(joined_path.string());
}

String join(const String& path1, const String& path2, const String& path3, const String& path4, const String& path5)
{
	boost::filesystem::path joined_path(path1.c_str());
	joined_path /= path2.c_str();
	joined_path /= path3.c_str();
	joined_path /= path4.c_str();
	joined_path /= path5.c_str();
	return convertToUnixPath(joined_path.string());
}

String join(const String& path1, const String& path2, const String& path3, const String& path4, const String& path5,
			const String& path6)
{
	boost::filesystem::path joined_path(path1.c_str());
	joined_path /= path2.c_str();
	joined_path /= path3.c_str();
	joined_path /= path4.c_str();
	joined_path /= path5.c_str();
	joined_path /= path6.c_str();
	return convertToUnixPath(joined_path.string());
}

String join(const String& path1, const String& path2, const String& path3, const String& path4, const String& path5,
			const String& path6, const String& path7)
{
	boost::filesystem::path joined_path(path1.c_str());
	joined_path /= path2.c_str();
	joined_path /= path3.c_str();
	joined_path /= path4.c_str();
	joined_path /= path5.c_str();
	joined_path /= path6.c_str();
	joined_path /= path7.c_str();
	return convertToUnixPath(joined_path.string());
}

String join(const String& path1, const String& path2, const String& path3, const String& path4, const String& path5,
			const String& path6, const String& path7, const String& path8)
{
	boost::filesystem::path joined_path(path1.c_str());
	joined_path /= path2.c_str();
	joined_path /= path3.c_str();
	joined_path /= path4.c_str();
	joined_path /= path5.c_str();
	joined_path /= path6.c_str();
	joined_path /= path7.c_str();
	joined_path /= path8.c_str();
	return convertToUnixPath(joined_path.string());
}

String join(const String& path1, const String& path2, const String& path3, const String& path4, const String& path5,
			const String& path6, const String& path7, const String& path8, const String& path9)
{
	boost::filesystem::path joined_path(path1.c_str());
	joined_path /= path2.c_str();
	joined_path /= path3.c_str();
	joined_path /= path4.c_str();
	joined_path /= path5.c_str();
	joined_path /= path6.c_str();
	joined_path /= path7.c_str();
	joined_path /= path8.c_str();
	joined_path /= path9.c_str();
	return convertToUnixPath(joined_path.string());
}

//====================================================================================
//                                System Path Methods
//====================================================================================

bool setCurrentPath(const String& path)
{
	// Set the current path
	try
	{
		boost::filesystem::current_path(boost::filesystem::path(path.c_str()));
		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
	{
		return false;
	}
}

String currentPath()
{
	String path = boost::filesystem::current_path().string();
	return convertToUnixPath(path);
}

String temporaryPath()
{
	String path = boost::filesystem::temp_directory_path().string();
	return convertToUnixPath(path);
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
		return boost::filesystem::create_directory(boost::filesystem::path(path.c_str()));
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
	{
		return false;
	}
}

bool createFullDirectoryPath(const String& path)
{
	return boost::filesystem::create_directories(boost::filesystem::path(path.c_str()));
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
		return boost::filesystem::remove(boost::filesystem::path(path.c_str()));
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
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
		boost::filesystem::remove_all(boost::filesystem::path(path.c_str()));
		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
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
		boost::filesystem::path source_path(source.c_str());
		boost::filesystem::path destination_path(destination.c_str());
		boost::filesystem::copy(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
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
	BOOST_FOREACH (const FileInfo& local_source_file, local_source_files)
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
		boost::filesystem::path source_path(source.c_str());
		boost::filesystem::path destination_path(destination.c_str());
		boost::filesystem::rename(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
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
	boost::filesystem::path directory_path(path.c_str());
	boost::filesystem::directory_iterator iter(directory_path);
	boost::filesystem::directory_iterator end_iter;

	// Iterate through the directory collecting all the item paths as strings
	StringSet directory_set;
	BOOST_FOREACH (const boost::filesystem::path& item, std::make_pair(iter, end_iter))
	{
		String unix_item_str = convertToUnixPath(item.string());
		directory_set.insert(unix_item_str);
	}

	// Build a string list from the sorted string set
	StringList directory_list;
	BOOST_FOREACH (const String& item, directory_set)
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
	boost::filesystem::path directory_path(path.c_str());
	boost::filesystem::directory_iterator iter(directory_path);
	boost::filesystem::directory_iterator end_iter;

	// Iterate through the directory collecting all the item paths as strings
	StringSet directory_set;
	BOOST_FOREACH (const boost::filesystem::path& item, std::make_pair(iter, end_iter))
	{
		String unix_item_str = convertToUnixPath(item.string());
		directory_set.insert(unix_item_str);
	}

	// Build a file info list from the sorted string set
	FileInfoList directory_list;
	BOOST_FOREACH (const String& item, directory_set)
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

	return boost::filesystem::remove(boost::filesystem::path(path.c_str()));
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
		boost::filesystem::path source_path(source.c_str());
		boost::filesystem::path destination_path(destination.c_str());
		boost::filesystem::copy(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
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
		boost::filesystem::path source_path(source.c_str());
		boost::filesystem::path destination_path(destination.c_str());
		boost::filesystem::rename(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
	{
		return false;
	}
}

//====================================================================================
//                               Symbolic Link Methods
//====================================================================================

bool createDirectorySymbolicLink(const String& source, const String& destination)
{
	try
	{
		// Convert the source path to the preferred OS
		boost::filesystem::path source_path(boost::filesystem::path(source.c_str()).make_preferred().string());
		boost::filesystem::path destination_path(destination.c_str());

		// Create the directory symlink
		boost::filesystem::create_directory_symlink(source_path, destination_path);

		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
	{
		return false;
	}
}

bool createFileSymbolicLink(const String& source, const String& destination)
{
	try
	{
		// Convert the source path to the preferred OS
		boost::filesystem::path source_path(boost::filesystem::path(source.c_str()).make_preferred().string());
		boost::filesystem::path destination_path(destination.c_str());

		// Create the file symlink
		boost::filesystem::create_symlink(source_path, destination_path);

		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
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
		return boost::filesystem::remove(boost::filesystem::path(path.c_str()));
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
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
		boost::filesystem::path source_path(source.c_str());
		boost::filesystem::path destination_path(destination.c_str());
		boost::filesystem::copy_symlink(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
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
		boost::filesystem::path source_path(source.c_str());
		boost::filesystem::path destination_path(destination.c_str());
		boost::filesystem::rename(source_path, destination_path);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
	{
		return false;
	}
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
		boost::filesystem::last_write_time(boost::filesystem::path(path.c_str()), date);
		return true;
	}
	catch (const boost::filesystem::filesystem_error& /*e*/)
	{
		return false;
	}
}

std::time_t modifiedDate(const String& path)
{
	FileInfo info(path);
	return info.modifiedDate();
}

}	// End of FileSystem namespace

}	// End of bump namespace
