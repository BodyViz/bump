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
 *    - Directory Modification (createDirectory, removeDirectory, directoryInfoList, etc.)
 *    - File Modification (createFile, renameFile, removeFile, copyFile, etc.)
 *    - Permissions Modification (setIsReadableByUser, setIsExecutableByOwner, etc.)
 *    - Date Modification (setDateModified, etc.)
 */
namespace FileSystem {

/**
 * Sets the current working directory path.
 *
 * @param The path to set the current working directory to.
 */
extern BUMP_EXPORT void setCurrentPath(const String& path);

/**
 * Returns the current working directory path.
 *
 * @return The absolute path of the current working directory.
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
