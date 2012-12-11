//
//  bumpFileSystem.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/foreach.hpp>

// Bump headers
#include <bump/Exception.h>
#include <bump/FileInfo.h>
#include <bump/FileSystem.h>

/**
 * Demonstrates how to use the join path methods.
 */
void joinPathsDemo()
{
	std::cout << "\n============================ JOIN PATHS DEMO ============================\n" << std::endl;

	//=========================================================================================
	// Sometimes you need to join file paths together. The bump::FileSystem API is very helpful
	// when it comes to this task. It supports joining up to 9 individual strings together into
	// a single path.
	//=========================================================================================

	// Join two paths
	bump::String path = bump::FileSystem::join("/Users/username", "Desktop");
	std::cout << "- \"" << path << "\"" << std::endl;

	// Join five paths
	path = bump::FileSystem::join("/", "opt", "local", "bin", "ls");
	std::cout << "- \"" << path << "\"" << std::endl;

	// Join the current path with a filename
	path = bump::FileSystem::join(bump::FileSystem::currentPath(), "example_file.txt");
	std::cout << "- \"" << path << "\"" << std::endl;
}

/**
 * Demonstrates how to use the system path methods.
 */
void systemPathsDemo()
{
	std::cout << "\n=========================== SYSTEM PATHS DEMO ===========================\n" << std::endl;

	//=========================================================================================
	// The system paths methods all you to query the file system for the current path (a.k.a.
	// current working directory) as well as the temporary path set for the file system. These
	// methods can come in very handy for certain situations.
	//=========================================================================================

	// Get the current path
	bump::String current_path = bump::FileSystem::currentPath();
	std::cout << "- Current Path:     " << current_path << std::endl;

	// Set the current path to something else by creating a new directory
	bump::String new_current_path = bump::FileSystem::join(current_path, "Test Directory");
	bump::FileSystem::createDirectory(new_current_path);
	bump::FileSystem::setCurrentPath(new_current_path);
	new_current_path = bump::FileSystem::currentPath();
	std::cout << "- New Current Path: " << new_current_path << std::endl;

	// Set the current path back to the original one
	bump::FileSystem::setCurrentPath(current_path);
	std::cout << "- Current Path:     " << current_path << std::endl;

	// Get the temporary path
	bump::String temp_path = bump::FileSystem::temporaryPath();
	std::cout << "- Temp Path:        " << temp_path << std::endl;
}

/**
 * Demonstrates how to use the path query methods.
 */
void pathQueriesDemo()
{
	std::cout << "\n=========================== PATH QUERIES DEMO ===========================\n" << std::endl;

	//=========================================================================================
	// The path query methods are just quick ways to figure out if the file system object
	// exists or what type of object it actually is. You can also use the bump::FileInfo
	// class to get this information as well. The methods are provided in both locations
	// simply for convenience.
	//=========================================================================================

	// Get the current path and query it
	bump::String current_path = bump::FileSystem::currentPath();
	bool exists = bump::FileSystem::exists(current_path);
	bool is_directory = bump::FileSystem::isDirectory(current_path);
	bool is_file = bump::FileSystem::isFile(current_path);
	bool is_symlink = bump::FileSystem::isSymbolicLink(current_path);
	std::cout << current_path << std::endl;
	std::cout << "- Exists:           " << (exists ? "YES" : "NO") << std::endl;
	std::cout << "- Is Directory:     " << (is_directory ? "YES" : "NO") << std::endl;
	std::cout << "- Is File:          " << (is_file ? "YES" : "NO") << std::endl;
	std::cout << "- Is Symlink:       " << (is_symlink ? "YES" : "NO") << std::endl;

	// Make a file and query it
	bump::String filepath = "test_file.pdf";
	bump::FileSystem::createFile(filepath);
	exists = bump::FileSystem::exists(filepath);
	is_directory = bump::FileSystem::isDirectory(filepath);
	is_file = bump::FileSystem::isFile(filepath);
	is_symlink = bump::FileSystem::isSymbolicLink(filepath);
	std::cout << "\n" << filepath << std::endl;
	std::cout << "- Exists:           " << (exists ? "YES" : "NO") << std::endl;
	std::cout << "- Is Directory:     " << (is_directory ? "YES" : "NO") << std::endl;
	std::cout << "- Is File:          " << (is_file ? "YES" : "NO") << std::endl;
	std::cout << "- Is Symlink:       " << (is_symlink ? "YES" : "NO") << std::endl;

	// Make a file symlink and query it
	bump::String symlink = "test_file_symlink.pdf";
	bump::FileSystem::createSymbolicLink(filepath, symlink);
	exists = bump::FileSystem::exists(symlink);
	is_directory = bump::FileSystem::isDirectory(symlink);
	is_file = bump::FileSystem::isFile(symlink);
	is_symlink = bump::FileSystem::isSymbolicLink(symlink);
	std::cout << "\n" << symlink << std::endl;
	std::cout << "- Exists:           " << (exists ? "YES" : "NO") << std::endl;
	std::cout << "- Is Directory:     " << (is_directory ? "YES" : "NO") << std::endl;
	std::cout << "- Is File:          " << (is_file ? "YES" : "NO") << std::endl;
	std::cout << "- Is Symlink:       " << (is_symlink ? "YES" : "NO") << std::endl;

	// Cleanup all the stuff we made
	bump::FileSystem::removeFile(filepath);
	bump::FileSystem::removeSymbolicLink(symlink);
}

/**
 * Demonstrates how to use the directory methods.
 */
void directoriesDemo()
{
	std::cout << "\n=========================== DIRECTORIES DEMO ============================\n" << std::endl;

	//=========================================================================================
	// The directories methods allow you to create and remove directories as well as copy and
	// rename them. These are very standard operations. In addition to these basic methods,
	// the bump::FileSystem API also allows you to remove and copy directories that aren't
	// already empty. These can be incredibly useful in many situations. Finally, there are
	// also directory listing methods allowing you to get a list of paths or bump::FileInfo
	// objects contained within the directory.
	//=========================================================================================

	std::cout << "Basic Methods" << std::endl;

	// Create a directory
	bump::FileSystem::createDirectory("Test Directory");
	std::cout << "- Created Directory: \"Test Directory\"" << std::endl;

	// Rename the directory
	bump::FileSystem::renameDirectory("Test Directory", "Renamed Directory");
	std::cout << "- Renamed Directory: \"Test Directory\" to \"Renamed Directory\"" << std::endl;

	// Copy the directory
	bump::FileSystem::copyDirectory("Renamed Directory", "Copied Directory");
	std::cout << "- Copied Directory:  \"Renamed Directory\" to \"Copied Directory\"" << std::endl;

	// Remove the directories
	bump::FileSystem::removeDirectory("Renamed Directory");
	std::cout << "- Removed Directory: \"Renamed Directory\"" << std::endl;
	bump::FileSystem::removeDirectory("Copied Directory");
	std::cout << "- Removed Directory: \"Copied Directory\"" << std::endl;

	std::cout << "\nAdvanced Methods" << std::endl;

	// Create a directory with files inside
	bump::FileSystem::createDirectory("Test Directory");
	std::cout << "- Created Directory: \"Test Directory\"" << std::endl;
	bump::FileSystem::createFile("Test Directory/paper.doc");
	std::cout << "- Created File:      \"Test Directory/paper.doc\"" << std::endl;
	bump::FileSystem::createFile("Test Directory/help.pdf");
	std::cout << "- Created File:      \"Test Directory/help.pdf\"" << std::endl;

	// List all the files inside the directory
	std::cout << "- Items inside       \"Test Directory\":" << std::endl;
	bump::StringList directory_items = bump::FileSystem::directoryList("Test Directory");
	BOOST_FOREACH(const bump::String& directory_item, directory_items)
	{
		std::cout << "\t- Relative Path: \"" << directory_item << "\"" << std::endl;
		std::cout << "\t- Absolute Path: \"" << bump::FileInfo(directory_item).absolutePath() << "\"" << std::endl;
	}

	// Copy the directory and it's contents
	bump::FileSystem::copyDirectoryAndContents("Test Directory", "Copied Directory");
	std::cout << "- Copied Directory and Contents: \"Test Directory\" to \"Copied Directory\"" << std::endl;

	// Remove the directories and all their contents
	bump::FileSystem::removeDirectoryAndContents("Test Directory");
	std::cout << "- Removed Directory and Contents: \"Test Directory\"" << std::endl;
	bump::FileSystem::removeDirectoryAndContents("Copied Directory");
	std::cout << "- Removed Directory and Contents: \"Copied Directory\"" << std::endl;
}

/**
 * Demonstrates how to use the file methods.
 */
void filesDemo()
{
	std::cout << "\n============================== FILES DEMO ===============================\n" << std::endl;

	//=========================================================================================
	// The files methods allow you to create and remove files as well as copy and rename them.
	//=========================================================================================

	// Create a regular file and a hidden file
	bump::FileSystem::createFile("output.txt");
	bump::FileSystem::createFile(".hidden_file.doc");
	std::cout << "- Created File: \"output.txt\"" << std::endl;
	std::cout << "- Created File: \".hidden_file.doc\"" << std::endl;

	// Rename the files
	bump::FileSystem::renameFile("output.txt", "output_renamed.txt");
	bump::FileSystem::renameFile(".hidden_file.doc", ".hidden_file_renamed.doc");
	std::cout << "- Renamed File: \"output.txt\" to \"output_renamed.txt\"" << std::endl;
	std::cout << "- Renamed File: \".hidden_file.doc\" to \".hidden_file_renamed.doc\"" << std::endl;

	// Copy the renamed files back to their original names
	bump::FileSystem::copyFile("output_renamed.txt", "output.txt");
	bump::FileSystem::copyFile(".hidden_file_renamed.doc", ".hidden_file.doc");
	std::cout << "- Copied File:  \"output_renamed.txt\" to \"output.txt\"" << std::endl;
	std::cout << "- Copied File:  \".hidden_file_renamed.doc\" to \".hidden_file.doc\"" << std::endl;

	// Remove the files
	bump::FileSystem::removeFile("output.txt");
	bump::FileSystem::removeFile("output_renamed.txt");
	bump::FileSystem::removeFile(".hidden_file.doc");
	bump::FileSystem::removeFile(".hidden_file_renamed.doc");
	std::cout << "- Removed File: \"output.txt\"" << std::endl;
	std::cout << "- Removed File: \"output_renamed.txt\"" << std::endl;
	std::cout << "- Removed File: \".hidden_file.doc\"" << std::endl;
	std::cout << "- Removed File: \".hidden_file_renamed.doc\"" << std::endl;
}

/**
 * Demonstrates how to use the symbolic link methods.
 */
void symbolicLinksDemo()
{
	std::cout << "\n========================== SYMBOLIC LINKS DEMO ==========================\n" << std::endl;

	//=========================================================================================
	// The symbolic link methods allow you to create and remove files as well as copy and
	// rename them.
	//=========================================================================================

	// Create a file symbolic link
	bump::FileSystem::createFile("output.txt");
	bump::FileSystem::createSymbolicLink("output.txt", "output_symlink.txt");
	std::cout << "- Created File: \"output.txt\"" << std::endl;
	std::cout << "- Created File Symlink: \"output_symlink.txt\" -> \"output.txt\"" << std::endl;

	// Create a directory symbolic link
	bump::FileSystem::createDirectory("Files");
	bump::FileSystem::createSymbolicLink("Files", "Files Symlink");
	std::cout << "- Created Directory: \"Files\"" << std::endl;
	std::cout << "- Created Directory Symlink: \"Files Symlink\" -> \"Files\"" << std::endl;

	// Rename the symbolic links
	bump::FileSystem::renameSymbolicLink("output_symlink.txt", "output_symlink_renamed.txt");
	bump::FileSystem::renameSymbolicLink("Files Symlink", "Files Symlink Renamed");
	std::cout << "- Renamed: \"output_symlink.txt\" to \"output_symlink_renamed.txt\"" << std::endl;
	std::cout << "- Renamed: \"Files Symlink\" to \"Files Symlink Renamed\"" << std::endl;

	// Copy the symbolic links
	bump::FileSystem::copySymbolicLink("output_symlink_renamed.txt", "output_symlink_copied.txt");
	bump::FileSystem::copySymbolicLink("Files Symlink Renamed", "Files Symlink Copied");
	std::cout << "- Renamed: \"output_symlink_renamed.txt\" to \"output_symlink_copied.txt\"" << std::endl;
	std::cout << "- Renamed: \"Files Symlink Renamed\" to \"Files Symlink Copied\"" << std::endl;

	// Remove the symbolic links
	bump::FileSystem::removeSymbolicLink("output_symlink_renamed.txt");
	bump::FileSystem::removeSymbolicLink("output_symlink_copied.txt");
	bump::FileSystem::removeSymbolicLink("Files Renamed");
	bump::FileSystem::removeSymbolicLink("Files Copied");
	std::cout << "- Removed Symlink: \"output_symlink_renamed.txt\"" << std::endl;
	std::cout << "- Removed Symlink: \"output_symlink_copied.txt\"" << std::endl;
	std::cout << "- Removed Symlink: \"Files Renamed\"" << std::endl;
	std::cout << "- Removed Symlink: \"Files Copied\"" << std::endl;

	// Remove the file and directory
	bump::FileSystem::removeFile("output.txt");
	bump::FileSystem::removeDirectory("Files");
	std::cout << "- Removed File: \"output.txt\"" << std::endl;
	std::cout << "- Removed Directory: \"Files\"" << std::endl;
}

/**
 * Demonstrates how to use the permissions methods.
 */
void permissionsDemo()
{
	std::cout << "\n============================ PERMISSIONS DEMO ===========================\n" << std::endl;

	//=========================================================================================
	// The permissions methods allow you to read all the permissions in regards to a file,
	// directory or symbolic link. Additionally, you can modify the permissions using the
	// bump::FileSystem API.
	//=========================================================================================

	// Create a file
	bump::FileSystem::createFile("output.txt");
	std::cout << "Created File: \"output.txt\"" << std::endl;

	// Read the permissions using the bump::FileSystem permissions method
	bump::FileSystem::Permissions permissions = bump::FileSystem::permissions("output.txt");
	std::cout << "- Is readable by owner: " << (permissions & bump::FileSystem::OWNER_READ ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by owner: " << (permissions & bump::FileSystem::OWNER_WRITE ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by owner: " << (permissions & bump::FileSystem::OWNER_EXE ? "YES" : "NO") << std::endl;
	std::cout << "- Is readable by group: " << (permissions & bump::FileSystem::GROUP_READ ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by group: " << (permissions & bump::FileSystem::GROUP_WRITE ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by group: " << (permissions & bump::FileSystem::GROUP_EXE ? "YES" : "NO") << std::endl;
	std::cout << "- Is readable by others: " << (permissions & bump::FileSystem::OTHERS_READ ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by others: " << (permissions & bump::FileSystem::OTHERS_WRITE ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by others: " << (permissions & bump::FileSystem::OTHERS_EXE ? "YES" : "NO") << std::endl;

	// Read the permissions using the bump::FileInfo convenience methods
	std::cout << "\nPermissions using bump::FileInfo API for \"output.txt\"" << std::endl;
	bump::FileInfo file_info("output.txt");
	std::cout << "- Is readable by owner: " << (file_info.isReadableByOwner() ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by owner: " << (file_info.isWritableByOwner() ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by owner: " << (file_info.isExecutableByOwner() ? "YES" : "NO") << std::endl;
	std::cout << "- Is readable by group: " << (file_info.isReadableByGroup() ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by group: " << (file_info.isWritableByGroup() ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by group: " << (file_info.isExecutableByGroup() ? "YES" : "NO") << std::endl;
	std::cout << "- Is readable by others: " << (file_info.isReadableByOthers() ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by others: " << (file_info.isWritableByOthers() ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by others: " << (file_info.isExecutableByOthers() ? "YES" : "NO") << std::endl;

	// Set the permissions using the bump::FileSystem setPermissions method
	bump::FileSystem::Permissions new_permissions = (bump::FileSystem::OWNER_ALL |
													 bump::FileSystem::GROUP_READ |
													 bump::FileSystem::OTHERS_READ);
	bump::FileSystem::setPermissions("output.txt", new_permissions);
	std::cout << "\nChanged permissions for \"output.txt\"" << std::endl;
	std::cout << "- Is readable by owner: " << (file_info.isReadableByOwner() ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by owner: " << (file_info.isWritableByOwner() ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by owner: " << (file_info.isExecutableByOwner() ? "YES" : "NO") << std::endl;
	std::cout << "- Is readable by group: " << (file_info.isReadableByGroup() ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by group: " << (file_info.isWritableByGroup() ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by group: " << (file_info.isExecutableByGroup() ? "YES" : "NO") << std::endl;
	std::cout << "- Is readable by others: " << (file_info.isReadableByOthers() ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by others: " << (file_info.isWritableByOthers() ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by others: " << (file_info.isExecutableByOthers() ? "YES" : "NO") << std::endl;

	// Set the permissions using the bump::FileSystem convenience methods. These are useful if you
	// just want to change a single permission without changing any of the other permissions. If you
	// want to change all the permissions, then the bump::FileSystem::setPermissions() method is
	// what you want to use.
	bump::FileSystem::setIsReadableByOwner("output.txt", true);
	bump::FileSystem::setIsWritableByOwner("output.txt", true);
	bump::FileSystem::setIsExecutableByOwner("output.txt", true);
	bump::FileSystem::setIsReadableByGroup("output.txt", false);
	bump::FileSystem::setIsWritableByGroup("output.txt", false);
	bump::FileSystem::setIsExecutableByGroup("output.txt", false);
	bump::FileSystem::setIsReadableByOthers("output.txt", false);
	bump::FileSystem::setIsWritableByOthers("output.txt", false);
	bump::FileSystem::setIsExecutableByOthers("output.txt", false);
	std::cout << "\nChanged permissions for \"output.txt\" using convenience methods" << std::endl;
	std::cout << "- Is readable by owner: " << (file_info.isReadableByOwner() ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by owner: " << (file_info.isWritableByOwner() ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by owner: " << (file_info.isExecutableByOwner() ? "YES" : "NO") << std::endl;
	std::cout << "- Is readable by group: " << (file_info.isReadableByGroup() ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by group: " << (file_info.isWritableByGroup() ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by group: " << (file_info.isExecutableByGroup() ? "YES" : "NO") << std::endl;
	std::cout << "- Is readable by others: " << (file_info.isReadableByOthers() ? "YES" : "NO") << std::endl;
	std::cout << "- Is writable by others: " << (file_info.isWritableByOthers() ? "YES" : "NO") << std::endl;
	std::cout << "- Is executable by others: " << (file_info.isExecutableByOthers() ? "YES" : "NO") << std::endl;
}

/**
 * Demonstrates how to use the dates methods.
 */
void datesDemo()
{
	std::cout << "\n=============================== DATES DEMO ==============================\n" << std::endl;

	//=========================================================================================
	// The dates methods allow you to read the modified date of a file system object as well
	// as set it.
	//=========================================================================================

	// Create a file
	bump::FileSystem::createFile("output.txt");
	std::cout << "- Created File: \"output.txt\"" << std::endl;

	// Read the modified date
	std::time_t modified_date = bump::FileSystem::modifiedDate("output.txt");
	bump::String date_str = std::asctime(std::localtime(&modified_date));
	std::cout << "- Modified Date: " << date_str.trimmed() << std::endl;

	// Set the modified date
	std::tm time_obj;
	time_obj.tm_sec = 42;
	time_obj.tm_min = 11;
	time_obj.tm_hour = 21;
	time_obj.tm_mday = 19;
	time_obj.tm_mon = 10;
	time_obj.tm_year = 89;
	time_obj.tm_wday = 3;
	std::time_t time = std::mktime(&time_obj);
	bump::FileSystem::setModifiedDate("output.txt", time);
	modified_date = bump::FileSystem::modifiedDate("output.txt");
	date_str = std::asctime(std::localtime(&modified_date));
	std::cout << "- New Modified Date: " << date_str.trimmed() << std::endl;

	// Remove the file
	bump::FileSystem::removeFile("output.txt");
	std::cout << "- Removed File: \"output.txt\"" << std::endl;
}

/**
 * This example demonstrates how to use the Bump FileSystem API.
 *
 * The FileSystem namespace is used to manipulate file system objects such as files,
 * directories and symbolic links. It is also used to query information about these
 * types of objects, rename them, copy them and even recursively remove them.
 *
 * The following is a breakdown of all the functionality of the FileSystem API:
 *
 *    - Join Paths (join, etc.)
 *    - System Paths (currentPath, setCurrentPath, temporaryPath, etc.)
 *    - Path Queries (exists, isDirectory, isFile, isSymbolicLink, etc.)
 *    - Directories (createDirectory, removeDirectory, directoryInfoList, etc.)
 *    - Files (createFile, renameFile, removeFile, copyFile, etc.)
 *    - Symbolic Links (createSymbolicLink, removeSymbolicLink, renameSymbolicLink, etc.)
 *    - Permissions (setPermissions, permissions, setIsReadableByUser, setIsExecutableByOwner, etc.)
 *    - Dates (setModifiedDate, modifiedDate, etc.)
 */
int main(int argc, char **argv)
{
	// Run all the demo functions
	joinPathsDemo();
	systemPathsDemo();
	pathQueriesDemo();
	directoriesDemo();
	filesDemo();
	symbolicLinksDemo();
	permissionsDemo();
	datesDemo();

    return 0;
}
