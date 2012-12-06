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
#include <bump/String.h>

namespace bump {

/**
 * The FileSystem allows users to modify the file system in almost every
 * way possible. The following is a breakdown of the functionality of the
 * FileSystem API:
 *
 *    - Join Paths (join, etc.)
 *    - System Paths (currentPath, setCurrentPath, temporaryPath, etc.)
 *    - Path Queries (exists, isDirectory, isFile, isSymbolicLink, etc.)
 *    - Directories (createDirectory, removeDirectory, directoryInfoList, etc.)
 *    - Files (createFile, renameFile, removeFile, copyFile, etc.)
 *    - Symbolic Links (createSymbolicLink, removeSymbolicLink, renameSymbolicLink, etc.)
 *    - Permissions (setIsReadableByUser, setIsExecutableByOwner, etc.)
 *    - Dates (setDateModified, etc.)
 */
namespace FileSystem {

//====================================================================================
//                                 Join Path Methods
//====================================================================================

/**
 * Joins the two strings together to form a single path.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @return The joined version of the strings forming a single path.
 */
extern BUMP_EXPORT String join(const String& path1, const String& path2);

/**
 * Joins the three strings together to form a single path.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @return The joined version of the strings forming a single path.
 */
extern BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3);

/**
 * Joins the four strings together to form a single path.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @param path4 The fourth portion of the path.
 * @return The joined version of the strings forming a single path.
 */
extern BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4);

/**
 * Joins the five strings together to form a single path.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @param path4 The fourth portion of the path.
 * @param path5 The fifth portion of the path.
 * @return The joined version of the strings forming a single path.
 */
extern BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4,
							   const String& path5);

/**
 * Joins the six strings together to form a single path.
 *
 * @param path1 The first portion of the path.
 * @param path2 The second portion of the path.
 * @param path3 The third portion of the path.
 * @param path4 The fourth portion of the path.
 * @param path5 The fifth portion of the path.
 * @param path6 The sixth portion of the path.
 * @return The joined version of the strings forming a single path.
 */
extern BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4,
							   const String& path5, const String& path6);

/**
 * Joins the seven strings together to form a single path.
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
extern BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4,
							   const String& path5, const String& path6, const String& path7);

/**
 * Joins the eight strings together to form a single path.
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
extern BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4,
							   const String& path5, const String& path6, const String& path7, const String& path8);

/**
 * Joins the nine strings together to form a single path.
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
extern BUMP_EXPORT String join(const String& path1, const String& path2, const String& path3, const String& path4,
							   const String& path5, const String& path6, const String& path7, const String& path8,
							   const String& path9);

//====================================================================================
//                                System Path Methods
//====================================================================================

/**
 * Sets the current working directory path.
 *
 * @param path The path to set the current working directory to.
 */
extern BUMP_EXPORT void setCurrentPath(const String& path);

/**
 * Returns the current working directory path.
 *
 * @return path The absolute path of the current working directory.
 */
extern BUMP_EXPORT String currentPath();

/**
 * Returns the temporary path for the operating system.
 *
 * @return The temporary path for the operating system.
 */
extern BUMP_EXPORT String temporaryPath();

//====================================================================================
//                               Path Query Methods
//====================================================================================

/**
 * Returns whether the path exists.
 *
 * @param path The path to check if points to a valid file system object.
 * @return True if the path exists, false otherwise.
 */
extern BUMP_EXPORT bool exists(const String& path);

/**
 * Returns whether the path points to a directory.
 *
 * @param path The path to check if points to a valid directory.
 * @return True if the path points to a directory, false othwerwise.
 */
extern BUMP_EXPORT bool isDirectory(const String& path);

/**
 * Returns whether the path points to a file.
 *
 * @param path The path to check if points to a valid file.
 * @return True if the path points to a file, false othwerwise.
 */
extern BUMP_EXPORT bool isFile(const String& path);

/**
 * Returns whether the path points to a symbolic link.
 *
 * @param path The path to check if points to a valid symbolic link.
 * @return True if the path points to a symbolic link, false othwerwise.
 */
extern BUMP_EXPORT bool isSymbolicLink(const String& path);

//====================================================================================
//                                 Directory Methods
//====================================================================================

/**
 * Creates the directory specified.
 *
 * @param path The path of the directory to create.
 * @return True if the directory was created successfully, false otherwise.
 */
extern BUMP_EXPORT bool createDirectory(const String& path);

/**
 * Creates the full path for the directory specified.
 *
 * Each directory specified in the full path will be attempted to be created.
 *
 * @param path The path of the directory to create.
 * @return True if the entire path was created successfully, false otherwise.
 */
extern BUMP_EXPORT bool createFullDirectoryPath(const String& path);

/**
 * Removes the specified directory if it is empty.
 *
 * @see removeDirectoryAndContents() can remove a directory that is not empty.
 * @param path The path of the directory to remove.
 * @return True if the directory was removed successfully, false otherwise.
 */
extern BUMP_EXPORT bool removeDirectory(const String& path);

/**
 * Removes the specified directory's contents recursively, then removes the directory itself.
 *
 * @param path The path of the directory to remove.
 * @return True if the directory and it's contents were removed successfully, false otherwise.
 */
extern BUMP_EXPORT bool removeDirectoryAndContents(const String& path);

/**
 * Copies the source directory over to the destination directory.
 *
 * It is important to not that the contents of the source directory will not be copied
 * to the destination directory using this method.
 *
 * @see copyDirectoryAndContents() can copy a directory along with all it's contents.
 * @param source The source directory to copy.
 * @param destination The destination directory to copy the source directory to.
 * @return True if the source directory was copied successfully, false otherwise.
 */
extern BUMP_EXPORT bool copyDirectory(const String& source, const String& destination);

/**
 * Copies the source directory and all contents over to the destination directory.
 *
 * @param source The source directory to copy.
 * @param destination The destination directory to copy the source directory to.
 * @return True if the source directory and all contents were copied successfully, false otherwise.
 */
extern BUMP_EXPORT bool copyDirectoryAndContents(const String& source, const String& destination);

/**
 * Renames the source directory to the destination directory.
 *
 * @param source The source directory to rename.
 * @param destination The destination directory to rename the source directory to.
 * @return True if the source directory was renamed successfully, false otherwise.
 */
extern BUMP_EXPORT bool renameDirectory(const String& source, const String& destination);

/**
 * Creates a list of file system object paths contained within the directory.
 *
 * @param path The path of the directory.
 * @return A string list of all the file system object paths contained within the directory.
 */
extern BUMP_EXPORT StringList directoryList(const String& path);

/**
 * Creates a list of FileInfo objects contained within the directory.
 *
 * @param path The path of the directory.
 * @return A file info list of all the objects contained within the directory.
 */
extern BUMP_EXPORT FileInfoList directoryInfoList(const String& path);

//====================================================================================
//                                   File Methods
//====================================================================================

/**
 * Creates the file specified.
 *
 * @param path The path of the file to create.
 * @return True if the file was created successfully, false otherwise.
 */
extern BUMP_EXPORT bool createFile(const String& path);

/**
 * Removes the file specified.
 *
 * @param path The path of the file to remove.
 * @return True if the file was removed successfully, false otherwise.
 */
extern BUMP_EXPORT bool removeFile(const String& path);

/**
 * Copies the source file over to the destination filepath.
 *
 * @param source The source file to copy.
 * @param destination The destination file to copy the source file to.
 * @return True if the source file was copied successfully, false otherwise.
 */
extern BUMP_EXPORT bool copyFile(const String& source, const String& destination);

/**
 * Renames the source file to the destination filepath.
 *
 * @param source The source file to rename.
 * @param destination The destination file to rename the source file to.
 * @return True if the source file was renamed successfully, false otherwise.
 */
extern BUMP_EXPORT bool renameFile(const String& source, const String& destination);

//====================================================================================
//                               Symbolic Link Methods
//====================================================================================

/**
 * Creates the symbolic link from the specified source file or directory.
 *
 * @param source The path of the original file or directory.
 * @param destination The path of the symbolic link to create.
 * @return True if the symbolic link was created successfully, false otherwise.
 */
extern BUMP_EXPORT bool createSymbolicLink(const String& source, const String& destination);

/**
 * Removes the symbolic link.
 *
 * @param path The path of the symbolic link to remove.
 * @return True if the symbolic link was removed successfully, false otherwise.
 */
extern BUMP_EXPORT bool removeSymbolicLink(const String& path);

/**
 * Copies the source symbolic link over over to the destination symbolic link.
 *
 * @param source The source symbolic link to copy.
 * @param destination The destination symbolic link to copy the source symbolic link to.
 * @return True if the source symbolic link was copied successfully, false otherwise.
 */
extern BUMP_EXPORT bool copySymbolicLink(const String& source, const String& destination);

/**
 * Renames the source symbolic link to the destination filepath.
 *
 * @param source The source symbolic link to rename.
 * @param destination The destination symbolic link to rename the source symbolic link to.
 * @return True if the source symbolic link was renamed successfully, false otherwise.
 */
extern BUMP_EXPORT bool renameSymbolicLink(const String& source, const String& destination);

}	// End of FileSystem namespace

}	// End of bump namespace

#endif	// End of BUMP_FILE_SYSTEM_H
