//
//  FileSystem.h
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_FILE_SYSTEM_H
#define BUMP_FILE_SYSTEM_H

// Bump headers
#include <bump/Export.h>
#include <bump/FileInfo.h>
#include <bump/String.h>

namespace bump {

/**
 * The FileSystem allows users to modify the file system in almost every
 * way possible. The following is a breakdown of the functionality of the
 * FileSystem API:
 *    - Join Paths (join(), etc.)
 *    - System Paths (currentPath(), setCurrentPath(), temporaryPath(), etc.)
 *    - Path Queries (exists(), isDirectory(), isFile(), isSymbolicLink(), etc.)
 *    - Directories (createDirectory(), removeDirectory(), directoryInfoList(), etc.)
 *    - Files (createFile(), renameFile(), removeFile(), copyFile(), etc.)
 *    - Symbolic Links (createSymbolicLink(), removeSymbolicLink(), renameSymbolicLink(), etc.)
 *    - Permissions (setPermissions(), permissions(), setIsReadableByUser(), setIsExecutableByOwner(), etc.)
 *    - Dates (setModifiedDate(), modifiedDate(), etc.)
 */
namespace FileSystem {

/**
 * Defines the types of permissions that can be set.
 */
enum Permission
{
	OWNER_READ		= 0x0001,
	OWNER_WRITE		= 0x0002,
	OWNER_EXE		= 0x0004,
	OWNER_ALL		= OWNER_READ | OWNER_WRITE | OWNER_EXE,
	GROUP_READ		= 0x0008,
	GROUP_WRITE		= 0x0010,
	GROUP_EXE		= 0x0020,
	GROUP_ALL		= GROUP_READ | GROUP_WRITE | GROUP_EXE,
	OTHERS_READ		= 0x0040,
	OTHERS_WRITE	= 0x0080,
	OTHERS_EXE		= 0x0100,
	OTHERS_ALL		= OTHERS_READ | OTHERS_WRITE | OTHERS_EXE,
	ALL_ALL			= OWNER_ALL | GROUP_ALL | OTHERS_ALL
};

// Typedefs
typedef unsigned int Permissions; /**< Defines a Permissions wrapper allowing Permission objects to be OR'd together. */

//====================================================================================
//                               Path Coversion Methods
//====================================================================================

/**
 * Converts the path to a Windows path by replacing forward slashes with backslashes.
 *
 * @param path The path to convert to a Windows path.
 * @return The converted Windows path.
 */
BUMP_EXPORT String convertToWindowsPath(String path);

/**
 * Converts the path to a Unix path by replacing backslashes with forward slashes.
 *
 * @param path The path to convert to a Unix path.
 * @return The converted Unix path.
 */
BUMP_EXPORT String convertToUnixPath(String path);

//====================================================================================
//                                 Join Path Methods
//====================================================================================

/**
 * Joins the two strings together to form a single path.
 *
 * Important to note that a unix style path is returned. For example:
 *
 * @code
 *   bump::FileSystem::join("/home/username", "Desktop");          // returns "/home/username/Desktop"
 *   bump::FileSystem::join("C:/Program Files", "Visual Studio");  // returns "C:/Program Files/Visual Studio"
 *   bump::FileSystem::join("C:\\Program Files", "Visual Studio"); // returns "C:/Program Files/Visual Studio"
 * @endcode
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @return The joined version of the strings forming a single path.
 */
BUMP_EXPORT String join(const String& path1, const String& path2);

/**
 * Joins the three strings together to form a single path.
 *
 * Important to note that a unix style path is returned.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @return The joined version of the strings forming a single path.
 */
BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3);

/**
 * Joins the four strings together to form a single path.
 *
 * Important to note that a unix style path is returned.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @param path4 The fourth portion of the path.
 * @return The joined version of the strings forming a single path.
 */
BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4);

/**
 * Joins the five strings together to form a single path.
 *
 * Important to note that a unix style path is returned.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @param path4 The fourth portion of the path.
 * @param path5 The fifth portion of the path.
 * @return The joined version of the strings forming a single path.
 */
BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5);

/**
 * Joins the six strings together to form a single path.
 *
 * Important to note that a unix style path is returned.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @param path4 The fourth portion of the path.
 * @param path5 The fifth portion of the path.
 * @param path6 The sixth portion of the path.
 * @return The joined version of the strings forming a single path.
 */
BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6);

/**
 * Joins the seven strings together to form a single path.
 *
 * Important to note that a unix style path is returned.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @param path4 The fourth portion of the path.
 * @param path5 The fifth portion of the path.
 * @param path6 The sixth portion of the path.
 * @param path7 The seventh portion of the path.
 * @return The joined version of the strings forming a single path.
 */
BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6, const String& path7);

/**
 * Joins the eight strings together to form a single path.
 *
 * Important to note that a unix style path is returned.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @param path4 The fourth portion of the path.
 * @param path5 The fifth portion of the path.
 * @param path6 The sixth portion of the path.
 * @param path7 The seventh portion of the path.
 * @param path8 The eighth portion of the path.
 * @return The joined version of the strings forming a single path.
 */
BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6, const String& path7, const String& path8);

/**
 * Joins the nine strings together to form a single path.
 *
 * Important to note that a unix style path is returned.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @param path4 The fourth portion of the path.
 * @param path5 The fifth portion of the path.
 * @param path6 The sixth portion of the path.
 * @param path7 The seventh portion of the path.
 * @param path8 The eighth portion of the path.
 * @param path9 The ninth portion of the path.
 * @return The joined version of the strings forming a single path.
 */
BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6, const String& path7, const String& path8,
						const String& path9);

//====================================================================================
//                                System Path Methods
//====================================================================================

/**
 * Sets the current working directory path.
 *
 * @param path The path to set the current working directory to.
 * @return True if the current path was changed successfully, false otherwise.
 */
BUMP_EXPORT bool setCurrentPath(const String& path);

/**
 * Returns the current working directory path as a unix path.
 *
 * @return path The absolute path of the current working directory.
 */
BUMP_EXPORT String currentPath();

/**
 * Returns the temporary path for the operating system as a unix path.
 *
 * @return The temporary path for the operating system.
 */
BUMP_EXPORT String temporaryPath();

//====================================================================================
//                               Path Query Methods
//====================================================================================

/**
 * Returns whether the path exists.
 *
 * @param path The path to check if points to a valid file system object.
 * @return True if the path exists, false otherwise.
 */
BUMP_EXPORT bool exists(const String& path);

/**
 * Returns whether the path points to a directory.
 *
 * @param path The path to check if points to a valid directory.
 * @return True if the path points to a directory, false othwerwise.
 */
BUMP_EXPORT bool isDirectory(const String& path);

/**
 * Returns whether the path points to a file.
 *
 * @param path The path to check if points to a valid file.
 * @return True if the path points to a file, false othwerwise.
 */
BUMP_EXPORT bool isFile(const String& path);

/**
 * Returns whether the path points to a symbolic link.
 *
 * @param path The path to check if points to a valid symbolic link.
 * @return True if the path points to a symbolic link, false othwerwise.
 */
BUMP_EXPORT bool isSymbolicLink(const String& path);

//====================================================================================
//                                 Directory Methods
//====================================================================================

/**
 * Creates the directory specified.
 *
 * @param path The path of the directory to create.
 * @return True if the directory was created successfully, false otherwise.
 */
BUMP_EXPORT bool createDirectory(const String& path);

/**
 * Creates the full path for the directory specified.
 *
 * Each directory specified in the full path will be attempted to be created.
 *
 * @param path The path of the directory to create.
 * @return True if the entire path was created successfully, false otherwise.
 */
BUMP_EXPORT bool createFullDirectoryPath(const String& path);

/**
 * Removes the specified directory if it is empty.
 *
 * @see removeDirectoryAndContents() can remove a directory that is not empty.
 *
 * @param path The path of the directory to remove.
 * @return True if the directory was removed successfully, false otherwise.
 */
BUMP_EXPORT bool removeDirectory(const String& path);

/**
 * Removes the specified directory's contents recursively, then removes the directory itself.
 *
 * @param path The path of the directory to remove.
 * @return True if the directory and it's contents were removed successfully, false otherwise.
 */
BUMP_EXPORT bool removeDirectoryAndContents(const String& path);

/**
 * Copies the source directory over to the destination directory.
 *
 * It is important to not that the contents of the source directory will not be copied
 * to the destination directory using this method.
 *
 * @see copyDirectoryAndContents() can copy a directory along with all it's contents.
 *
 * @param source The source directory to copy.
 * @param destination The destination directory to copy the source directory to.
 * @return True if the source directory was copied successfully, false otherwise.
 */
BUMP_EXPORT bool copyDirectory(const String& source, const String& destination);

/**
 * Copies the source directory and all contents over to the destination directory.
 *
 * @param source The source directory to copy.
 * @param destination The destination directory to copy the source directory to.
 * @return True if the source directory and all contents were copied successfully, false otherwise.
 */
BUMP_EXPORT bool copyDirectoryAndContents(const String& source, const String& destination);

/**
 * Renames the source directory to the destination directory.
 *
 * @param source The source directory to rename.
 * @param destination The destination directory to rename the source directory to.
 * @return True if the source directory was renamed successfully, false otherwise.
 */
BUMP_EXPORT bool renameDirectory(const String& source, const String& destination);

/**
 * Creates a list of file system object paths contained within the directory.
 *
 * @throw bump::FileSystemError When the path does not exist.
 * @throw bump::FileSystemError When the path is not a directory.
 *
 * @param path The path of the directory.
 * @return A string list of all the file system object paths contained within the directory.
 */
BUMP_EXPORT StringList directoryList(const String& path);

/**
 * Creates a list of FileInfo objects contained within the directory.
 *
 * @throw bump::FileSystemError When the path does not exist.
 * @throw bump::FileSystemError When the path is not a directory.
 *
 * @param path The path of the directory.
 * @return A file info list of all the objects contained within the directory.
 */
BUMP_EXPORT FileInfoList directoryInfoList(const String& path);

//====================================================================================
//                                   File Methods
//====================================================================================

/**
 * Creates the file specified.
 *
 * @param path The path of the file to create.
 * @return True if the file was created successfully, false otherwise.
 */
BUMP_EXPORT bool createFile(const String& path);

/**
 * Removes the file specified.
 *
 * @param path The path of the file to remove.
 * @return True if the file was removed successfully, false otherwise.
 */
BUMP_EXPORT bool removeFile(const String& path);

/**
 * Copies the source file over to the destination filepath.
 *
 * @param source The source file to copy.
 * @param destination The destination file to copy the source file to.
 * @return True if the source file was copied successfully, false otherwise.
 */
BUMP_EXPORT bool copyFile(const String& source, const String& destination);

/**
 * Renames the source file to the destination filepath.
 *
 * @param source The source file to rename.
 * @param destination The destination file to rename the source file to.
 * @return True if the source file was renamed successfully, false otherwise.
 */
BUMP_EXPORT bool renameFile(const String& source, const String& destination);

//====================================================================================
//                               Symbolic Link Methods
//====================================================================================

/**
 * Creates the symbolic link from the specified directory.
 *
 * This method works best and is easiest to use when both source and destination are
 * absolute paths. When they are relative, things are a bit trickier. Make sure that
 * the destination path is relative to the current path. Then the source path needs
 * to be relative to the destination path, not the current path.
 *
 * @param source The path of the original directory.
 * @param destination The path of the symbolic link to create.
 * @return True if the symbolic link was created successfully, false otherwise.
 */
BUMP_EXPORT bool createDirectorySymbolicLink(const String& source, const String& destination);

/**
 * Creates the symbolic link from the specified source file.
 *
 * This method works best and is easiest to use when both source and destination are
 * absolute paths. When they are relative, things are a bit trickier. Make sure that
 * the destination path is relative to the current path. Then the source path needs
 * to be relative to the destination path, not the current path.
 *
 * @param source The path of the original file.
 * @param destination The path of the symbolic link to create.
 * @return True if the symbolic link was created successfully, false otherwise.
 */
BUMP_EXPORT bool createFileSymbolicLink(const String& source, const String& destination);

/**
 * Removes the symbolic link.
 *
 * @param path The path of the symbolic link to remove.
 * @return True if the symbolic link was removed successfully, false otherwise.
 */
BUMP_EXPORT bool removeSymbolicLink(const String& path);

/**
 * Copies the source symbolic link over over to the destination symbolic link.
 *
 * @param source The source symbolic link to copy.
 * @param destination The destination symbolic link to copy the source symbolic link to.
 * @return True if the source symbolic link was copied successfully, false otherwise.
 */
BUMP_EXPORT bool copySymbolicLink(const String& source, const String& destination);

/**
 * Renames the source symbolic link to the destination filepath.
 *
 * @param source The source symbolic link to rename.
 * @param destination The destination symbolic link to rename the source symbolic link to.
 * @return True if the source symbolic link was renamed successfully, false otherwise.
 */
BUMP_EXPORT bool renameSymbolicLink(const String& source, const String& destination);

//====================================================================================
//                                Permissions Methods
//====================================================================================

/**
 * Replaces the permissions for the file or directory at path with the ones specified.
 *
 * It is important to note that if path if a symbolic link, on Unix operating systems,
 * the symbolic link will be resolved and the permissions will actually be changed on
 * the file or directory that the symbolic link points to. On Windows, the symbolic link
 * permissions are actually modified. However, this should be a very rare case though
 * since modifying permissions of a symbolic link should not need to happen very often.
 *
 * @todo Add support for Windows.
 *
 * @throw A bump::NotImplementedError on Windows.
 *
 * @param path The path of the file or directory to change the permissions on.
 * @param permissions The permissions to change on the file or directory that path points to.
 * @return True if the permissions were changed successfully, false otherwise.
 */
BUMP_EXPORT bool setPermissions(const String& path, Permissions permissions);

/**
 * Returns the permissions for the file or directory at path.
 *
 * @todo Add support for Windows.
 *
 * @throw bump::FileSystemError When the path does not exist.
 * @throw A bump::NotImplementedError on Windows.
 *
 * @param path The path of the file or directory to get the permissions for.
 * @return The permissions of the file or directory that path points to.
 */
BUMP_EXPORT Permissions permissions(const String& path);

/**
 * Enables/disables the owner readable permission's bit for the file or directory at path.
 *
 * @todo Add support for Windows.
 *
 * @throw A bump::NotImplementedError on Windows.
 *
 * @param path The path of the file or directory to set the permissions on.
 * @param isReadable Whether to set the path to be readable or not.
 * @return True if the permissions were changed successfully, false otherwise.
 */
BUMP_EXPORT bool setIsReadableByOwner(const String& path, bool isReadable);

/**
 * Enables/disables the owner writable permission's bit for the file or directory at path.
 *
 * @todo Add support for Windows.
 *
 * @throw A bump::NotImplementedError on Windows.
 *
 * @param path The path of the file or directory to set the permissions on.
 * @param isWritable Whether to set the path to be writable or not.
 * @return True if the permissions were changed successfully, false otherwise.
 */
BUMP_EXPORT bool setIsWritableByOwner(const String& path, bool isWritable);

/**
 * Enables/disables the owner executable permission's bit for the file or directory at path.
 *
 * @todo Add support for Windows.
 *
 * @throw A bump::NotImplementedError on Windows.
 *
 * @param path The path of the file or directory to set the permissions on.
 * @param isExecutable Whether to set the path to be executable or not.
 * @return True if the permissions were changed successfully, false otherwise.
 */
BUMP_EXPORT bool setIsExecutableByOwner(const String& path, bool isExecutable);

/**
 * Enables/disables the group readable permission's bit for the file or directory at path.
 *
 * @todo Add support for Windows.
 *
 * @throw A bump::NotImplementedError on Windows.
 *
 * @param path The path of the file or directory to set the permissions on.
 * @param isReadable Whether to set the path to be readable or not.
 * @return True if the permissions were changed successfully, false otherwise.
 */
BUMP_EXPORT bool setIsReadableByGroup(const String& path, bool isReadable);

/**
 * Enables/disables the group writable permission's bit for the file or directory at path.
 *
 * @todo Add support for Windows.
 *
 * @throw A bump::NotImplementedError on Windows.
 *
 * @param path The path of the file or directory to set the permissions on.
 * @param isWritable Whether to set the path to be writable or not.
 * @return True if the permissions were changed successfully, false otherwise.
 */
BUMP_EXPORT bool setIsWritableByGroup(const String& path, bool isWritable);

/**
 * Enables/disables the group executable permission's bit for the file or directory at path.
 *
 * @todo Add support for Windows.
 *
 * @throw A bump::NotImplementedError on Windows.
 *
 * @param path The path of the file or directory to set the permissions on.
 * @param isExecutable Whether to set the path to be executable or not.
 * @return True if the permissions were changed successfully, false otherwise.
 */
BUMP_EXPORT bool setIsExecutableByGroup(const String& path, bool isExecutable);

/**
 * Enables/disables the others readable permission's bit for the file or directory at path.
 *
 * @todo Add support for Windows.
 *
 * @throw A bump::NotImplementedError on Windows.
 *
 * @param path The path of the file or directory to set the permissions on.
 * @param isReadable Whether to set the path to be readable or not.
 * @return True if the permissions were changed successfully, false otherwise.
 */
BUMP_EXPORT bool setIsReadableByOthers(const String& path, bool isReadable);

/**
 * Enables/disables the others writable permission's bit for the file or directory at path.
 *
 * @todo Add support for Windows.
 *
 * @throw A bump::NotImplementedError on Windows.
 *
 * @param path The path of the file or directory to set the permissions on.
 * @param isWritable Whether to set the path to be writable or not.
 * @return True if the permissions were changed successfully, false otherwise.
 */
BUMP_EXPORT bool setIsWritableByOthers(const String& path, bool isWritable);

/**
 * Enables/disables the others executable permission's bit for the file or directory at path.
 *
 * @todo Add support for Windows.
 *
 * @throw A bump::NotImplementedError on Windows.
 * 
 * @param path The path of the file or directory to set the permissions on.
 * @param isExecutable Whether to set the path to be executable or not.
 * @return True if the permissions were changed successfully, false otherwise.
 */
BUMP_EXPORT bool setIsExecutableByOthers(const String& path, bool isExecutable);

//====================================================================================
//                                  Date Methods
//====================================================================================

/**
 * Sets the modified date for the file or directory at path.
 *
 * @param path The path of the file or directory to set the modified date for.
 * @param date The new modified date as a time to set the file or directory to.
 * @return True if the modified date was changed successfully, false otherwise.
 */
BUMP_EXPORT bool setModifiedDate(const String& path, const std::time_t& date);

/**
 * Returns the modified date for the file or directory at path.
 *
 * @throw bump::FileSystemError When the path does not exist.
 *
 * @param path The path of the file or directory to set the modified date for.
 * @return The date the file system object was last modified.
 */
BUMP_EXPORT std::time_t modifiedDate(const String& path);

}	// End of FileSystem namespace

}	// End of bump namespace

#endif	// End of BUMP_FILE_SYSTEM_H
