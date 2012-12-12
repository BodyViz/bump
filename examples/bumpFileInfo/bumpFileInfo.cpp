//
//  bumpFileInfo.cpp
//  Bump
//
//  Created by Christian Noon on 12/7/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/config.hpp>

// Bump headers
#include <bump/FileInfo.h>
#include <bump/FileSystem.h>

/**
 * Prints out all the information about the bump::FileInfo object.
 */
void printInfo(const bump::FileInfo& fileInfo)
{
	std::cout << "\n================================= " << fileInfo.path() << " =================================" << std::endl;

	// Path query methods
	std::cout << "\nPath Queries" << std::endl;
	std::cout << "- Exists:                  " << (fileInfo.exists() ? "YES" : "NO") << std::endl;
	if (fileInfo.isFile())
		std::cout << "- File size:               " << fileInfo.fileSize() << " Bytes" << std::endl;
	std::cout << "- Is absolute:             " << (fileInfo.isAbsolute() ? "YES" : "NO") << std::endl;
	std::cout << "- Is relative:             " << (fileInfo.isRelative() ? "YES" : "NO") << std::endl;
	std::cout << "- Is a directory:          " << (fileInfo.isDirectory() ? "YES" : "NO") << std::endl;
	std::cout << "- Is a file:               " << (fileInfo.isFile() ? "YES" : "NO") << std::endl;
	std::cout << "- Is a symlink:            " << (fileInfo.isSymbolicLink() ? "YES" : "NO") << std::endl;
	std::cout << "- Is empty:                " << (fileInfo.isEmpty() ? "YES" : "NO") << std::endl;
	std::cout << "- Is hidden:               " << (fileInfo.isHidden() ? "YES" : "NO") << std::endl;

	// Path decomposition methods
	std::cout << "\nPath Decomposition" << std::endl;
	std::cout << "- Absolute path:           " << fileInfo.absolutePath() << std::endl;
	std::cout << "- Canonical path:          " << fileInfo.canonicalPath() << std::endl;
	std::cout << "- Parent path:             " << fileInfo.parentPath() << std::endl;
	std::cout << "- Basename:                " << fileInfo.basename() << std::endl;
	std::cout << "- CompleteBasename:        " << fileInfo.completeBasename() << std::endl;
	std::cout << "- Extension:               " << fileInfo.extension() << std::endl;
	std::cout << "- CompleteExtension:       " << fileInfo.completeExtension() << std::endl;
	std::cout << "- Filename:                " << fileInfo.filename() << std::endl;

#ifndef BOOST_WINDOWS
	
	// Permissions query methods (NOT implemented on Windows)
	std::cout << "\nPermissions Queries" << std::endl;
	std::cout << "- Is readable by user:     " << fileInfo.isReadableByUser() << std::endl;
	std::cout << "- Is writable by user:     " << fileInfo.isWritableByUser() << std::endl;
	std::cout << "- Is executable by user:   " << fileInfo.isExecutableByUser() << std::endl;
	std::cout << "- Is readable by owner:    " << fileInfo.isReadableByOwner() << std::endl;
	std::cout << "- Is writable by owner:    " << fileInfo.isWritableByOwner() << std::endl;
	std::cout << "- Is executable by owner:  " << fileInfo.isExecutableByOwner() << std::endl;
	std::cout << "- Is readable by group:    " << fileInfo.isReadableByGroup() << std::endl;
	std::cout << "- Is writable by group:    " << fileInfo.isWritableByGroup() << std::endl;
	std::cout << "- Is executable by group:  " << fileInfo.isExecutableByGroup() << std::endl;
	std::cout << "- Is readable by others:   " << fileInfo.isReadableByOthers() << std::endl;
	std::cout << "- Is writable by others:   " << fileInfo.isWritableByOthers() << std::endl;
	std::cout << "- Is executable by others: " << fileInfo.isExecutableByOthers() << std::endl;
	std::cout << "- Owner:                   " << fileInfo.owner() << std::endl;
	std::cout << "- Owner ID:                " << fileInfo.ownerId() << std::endl;
	std::cout << "- Group:                   " << fileInfo.group() << std::endl;
	std::cout << "- Group ID:                " << fileInfo.groupId() << std::endl;

#endif

	// Date query methods
	std::cout << "\nDate Queries" << std::endl;
	std::time_t date_modified = fileInfo.modifiedDate();
	bump::String date_str = std::asctime(std::localtime(&date_modified));
	std::cout << "- Date modified:           " << date_str.trimmed() << std::endl;
}

/**
 * This example demonstrates how to use the Bump FileInfo API.
 *
 * The FileInfo class is used to query about every kind of information you can think
 * of when it comes to file system objects (files, directories and symbolic links).
 * The class is very easy to use. Simply create a FileInfo object by passing it a
 * relative or absolute path, and query away.
 *
 * On another note, the entire FileInfo API is read-only. If you wish to make changes
 * to file system objects, then you are looking for the bump::FileSystem API.
 */
int main(int argc, char **argv)
{
	// Create a file and print out all the information about it
	bump::FileSystem::createFile("basic_file.txt");
	bump::FileInfo file_info("basic_file.txt");
	printInfo(file_info);

	// Create a directory and print out all the information about it
	bump::FileSystem::createDirectory("Test Directory");
	bump::FileInfo directory_info("Test Directory");
	printInfo(directory_info);

	// Create a file symbolic link and print out all the information about it
	bump::FileSystem::createFileSymbolicLink("basic_file.txt", "basic_file_symlink.txt");
	bump::FileInfo file_symlink_info("basic_file_symlink.txt");
	printInfo(file_symlink_info);

	// Create a directory symbolic link and print out all the information about it
	bump::FileSystem::createDirectorySymbolicLink("Test Directory", "Test Directory Symlink");
	bump::FileInfo directory_symlink_info("Test Directory Symlink");
	printInfo(directory_symlink_info);

	// Clean up all the file system objects we created
	bump::FileSystem::removeFile("basic_file.txt");
	bump::FileSystem::removeDirectory("Test Directory");
	bump::FileSystem::removeSymbolicLink("basic_file_symlink.txt");
	bump::FileSystem::removeSymbolicLink("Test Directory Symlink");

    return 0;
}
