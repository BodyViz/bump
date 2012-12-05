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
 *    - Directories (createDirectory, removeDirectory, directoryInfoList, etc.)
 *    - Files (createFile, renameFile, removeFile, copyFile, etc.)
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

}	// End of FileSystem namespace

}	// End of bump namespace

#endif	// End of BUMP_FILE_SYSTEM_H
