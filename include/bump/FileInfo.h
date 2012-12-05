//
//  FileInfo.h
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_FILE_INFO_H
#define BUMP_FILE_INFO_H

// Boost headers
#include <boost/filesystem/path.hpp>

// Bump headers
#include <bump/Export.h>
#include <bump/String.h>

namespace bump {

/**
 * The FileInfo class is useful when you need information about a file system object.
 *
 * The various types of file system objects support are files, directories and symbolic
 * links. The four types of methods supported are:
 *
 *     - Path Query (fileSize, isRelative, isFile, etc.)
 *     - Path Decomposition (absolutePath, basename, filename, extension, etc.)
 *     - Permissions Query (isReadableByUser, owner, group, etc.)
 *     - Date Query (dateModified, etc.)
 *
 * It is important to note that all these methods are read-only. You cannot make changes to
 * file system objects using the FileInfo API. It is merely for investigative purposes.
 *
 * @see The FileSystem class for information on how to modify file system objects.
 */
class BUMP_EXPORT FileInfo
{
public:

	/**
	 * Constructor.
	 *
	 * @param path The absolute or relative path to the file system object to inspect.
	 */
	FileInfo(const String& path);

	/**
	 * Destructor.
	 */
	~FileInfo();

	//====================================================================================
	//                               Path Query Methods
	//====================================================================================

	/**
	 * Returns whether the path exists.
	 *
	 * @return True if the path exists, false otherwise.
	 */
	bool exists() const;

	/**
	 * Returns the file size of the path if it exists and is a file.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 * @throw bump::FileSystemError When the path is not a file.
	 * @return File size of path if exists and is file, otherwise returns -1.
	 */
	unsigned long long fileSize() const;

	/**
	 * Returns whether the path is an absolute path.
	 *
	 * @return True if the path is an absolute path, false otherwise.
	 */
	bool isAbsolute() const;

	/**
	 * Returns whether the path is a relative path.
	 *
	 * @return True if the path is an relative path, false otherwise.
	 */
	bool isRelative() const;

	/**
	 * Returns whether the path points to a directory.
	 *
	 * @return True if the path points to a directory, false othwerwise.
	 */
	bool isDirectory() const;

	/**
	 * Returns whether the path points to a file.
	 *
	 * @return True if the path points to a file, false othwerwise.
	 */
	bool isFile() const;

	/**
	 * Returns whether the path points to a symbolic link.
	 *
	 * @return True if the path points to a symbolic link, false othwerwise.
	 */
	bool isSymbolicLink() const;

	/**
	 * Returns whether the path points an empty directory or empty file.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 * @return True if the path points to an empty directory or empty file, false othwerwise.
	 */
	bool isEmpty() const;

	/**
	 * Returns whether the path points to a hidden file.
	 *
	 * @return True if the path points to a hidden file, false othwerwise.
	 */
	bool isHidden() const;

	//====================================================================================
	//                          Path Decomposition Methods
	//====================================================================================

	/**
	 * Returns the absolute path without cleaning the path or resolving symbolic links.
	 *
	 * @return The absolute path without cleaning the path or resolving symbolic links.
	 */
	String absolutePath() const;

	/**
	 * Returns the absolute path by resolving symbolic links, removing dot and dot-dot elements.
	 *
	 * @return The cleaned absolute path.
	 */
	String canonicalPath() const;

	/**
	 * Returns the parent path.
	 *
	 * @code
	 *   bump::FileInfo("/home/users/user/output.txt").parentPath(); // returns "/home/users/user"
	 * @endcode
	 *
	 * @return The parent path.
	 */
	String parentPath() const;

	/**
	 * Returns the basename of the file.
	 *
	 * @code
	 *   bump::FileInfo("output.txt").basename();    // returns "output"
	 *   bump::FileInfo("output.tar.gz").basename(); // returns "output"
	 * @endcode
	 *
	 * @return The basename of the file.
	 */
	String basename() const;

	/**
	 * Returns the complete basename of the file.
	 *
	 * @code
	 *   bump::FileInfo("output.txt").completeBasename();    // returns "output"
	 *   bump::FileInfo("output.tar.gz").completeBasename(); // returns "output.tar"
	 * @endcode
	 *
	 * @return The complete basename of the file.
	 */
	String completeBasename() const;

	/**
	 * Returns the extension of the file.
	 *
	 * @code
	 *   bump::FileInfo("output.txt").extension();    // returns "txt"
	 *   bump::FileInfo("output.tar.gz").extension(); // returns "gz"
	 * @endcode
	 *
	 * @return The extension of the file.
	 */
	String extension() const;

	/**
	 * Returns the complete extension of the file.
	 *
	 * @code
	 *   bump::FileInfo("output.txt").completeExtension();    // returns "txt"
	 *   bump::FileInfo("output.tar.gz").completeExtension(); // returns "tar.gz"
	 * @endcode
	 *
	 * @return The complete extension of the file.
	 */
	String completeExtension() const;

	/**
	 * Returns the filename of the directory or file.
	 *
	 * @code
	 *   bump::FileInfo("output.txt").filename();    // returns "output.txt"
	 *   bump::FileInfo("output.tar.gz").filename(); // returns "output.tar.gz"
	 * @endcode
	 *
	 * @return The filename of the file.
	 */
	String filename() const;

	//====================================================================================
	//                            Permissions Query Methods
	//====================================================================================

	/**
	 * Returns whether the path is readable by the current user based on the path's permissions.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 * @return True if the path is readable by the current user, false otherwise.
	 */
	bool isReadableByUser() const;

	/**
	 * Returns whether the path is writable by the current user based on the path's permissions.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 * @return True if the path is writable by the current user, false otherwise.
	 */
	bool isWritableByUser() const;

	/**
	 * Returns whether the path is executable by the current user based on the path's permissions.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 * @return True if the path is executable by the current user, false otherwise.
	 */
	bool isExecutableByUser() const;

	/**
	 * Returns whether the path is readable by the owner based on the path's permissions.
	 *
	 * @return True if the path is readable by the owner, false otherwise.
	 */
	bool isReadableByOwner() const;

	/**
	 * Returns whether the path is writable by the owner based on the path's permissions.
	 *
	 * @return True if the path is writable by the owner, false otherwise.
	 */
	bool isWritableByOwner() const;

	/**
	 * Returns whether the path is executable by the owner based on the path's permissions.
	 *
	 * @return True if the path is executable by the owner, false otherwise.
	 */
	bool isExecutableByOwner() const;

	/**
	 * Returns whether the path is readable by the group based on the path's permissions.
	 *
	 * @return True if the path is readable by the group, false otherwise.
	 */
	bool isReadableByGroup() const;

	/**
	 * Returns whether the path is writable by the group based on the path's permissions.
	 *
	 * @return True if the path is writable by the group, false otherwise.
	 */
	bool isWritableByGroup() const;

	/**
	 * Returns whether the path is executable by the group based on the path's permissions.
	 *
	 * @return True if the path is executable by the group, false otherwise.
	 */
	bool isExecutableByGroup() const;

	/**
	 * Returns whether the path is readable by the anyone based on the path's permissions.
	 *
	 * @return True if the path is readable by the anyone, false otherwise.
	 */
	bool isReadableByAnyone() const;

	/**
	 * Returns whether the path is writable by the anyone based on the path's permissions.
	 *
	 * @return True if the path is writable by the anyone, false otherwise.
	 */
	bool isWritableByAnyone() const;

	/**
	 * Returns whether the path is executable by the anyone based on the path's permissions.
	 *
	 * @return True if the path is executable by the anyone, false otherwise.
	 */
	bool isExecutableByAnyone() const;

	/**
	 * Returns the owner of the path. On Windows the return value is empty.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 * @return The owner of the path.
	 */
	String owner() const;

	/**
	 * Returns the owner id of the path. On Windows the return value is -1.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 * @return The owner of the path.
	 */
	unsigned int ownerId() const;

	/**
	 * Returns the group of the path. On Windows the return value is empty.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 * @return The group of the path.
	 */
	String group() const;

	/**
	 * Returns the group id of the path. On Windows the return value is -1.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 * @return The group of the path.
	 */
	unsigned int groupId() const;

	//====================================================================================
	//                                Date Query Methods
	//====================================================================================

	/**
	 * Returns the date the file system object was last modified.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 * @return The date the file system object was last modified.
	 */
	std::time_t dateModified() const;

protected:

	/**
	 * Validates that the path is valid.
	 *
	 * @throw bump::FileSystemError When the path does not exist.
	 */
	void _validatePath() const;

	// Instance member variables
	boost::filesystem::path		_path; /**< The boost "path" used to support the FileInfo API. */
};

}	// End of bump namespace

#endif	// End of BUMP_FILE_INFO_H
