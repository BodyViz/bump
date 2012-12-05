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
 * TODO
 */
class BUMP_EXPORT FileInfo
{
public:

	/**
	 * Constructor.
	 */
	FileInfo(const String& path);

	/**
	 * Destructor.
	 */
	~FileInfo();

	/**
	 *====================================================================================
	 *                              Path Query Methods
	 *====================================================================================
	 */

	/**
	 * Returns whether the path exists.
	 *
	 * @return true if the path exists, false otherwise.
	 */
	bool exists() const;

	/**
	 * Returns the file size of the path if it exists and is a file.
	 *
	 * Throws a bump::FileSystemError if the path does not exist.
	 * Throws a bump::FileSystemError if the path is not a file.
	 *
	 * @return file size of path if exists and is file, otherwise returns -1.
	 */
	unsigned long long fileSize() const;

	/**
	 * Returns whether the path is an absolute path.
	 *
	 * @return true if the path is an absolute path, false otherwise.
	 */
	bool isAbsolute() const;

	/**
	 * Returns whether the path is a relative path.
	 *
	 * @return true if the path is an relative path, false otherwise.
	 */
	bool isRelative() const;

	/**
	 * Returns whether the path points to a directory.
	 *
	 * @return true if the path points to a directory, false othwerwise.
	 */
	bool isDirectory() const;

	/**
	 * Returns whether the path points to a file.
	 *
	 * @return true if the path points to a file, false othwerwise.
	 */
	bool isFile() const;

	/**
	 * Returns whether the path points to a symbolic link.
	 *
	 * @return true if the path points to a symbolic link, false othwerwise.
	 */
	bool isSymbolicLink() const;

	/**
	 * Returns whether the path points an empty directory or empty file.
	 *
	 * Throws bump::FileSystemError if the path does not exist.
	 *
	 * @return true if the path points to an empty directory or empty file, false othwerwise.
	 */
	bool isEmpty() const;

	/**
	 * Returns whether the path points to a hidden file.
	 *
	 * @return true if the path points to a hidden file, false othwerwise.
	 */
	bool isHidden() const;

	/**
	 *====================================================================================
	 *                          Path Decomposition Methods
	 *====================================================================================
	 */

	/**
	 * Returns the absolute path without cleaning the path or resolving symbolic links.
	 *
	 * @return the absolute path without cleaning the path or resolving symbolic links.
	 */
	String absolutePath() const;

	/**
	 * Returns the absolute path by resolving symbolic links, removing dot and dot-dot elements.
	 *
	 * @return the cleaned absolute path.
	 */
	String canonicalPath() const;

	/**
	 * Returns the parent path, i.e. /home/users/user/output.txt == /home/users/user.
	 *
	 * @return the parent path.
	 */
	String parentPath() const;

	/**
	 * Returns the basename of the file, i.e. output.txt == output and output.tar.gz == output.
	 *
	 * @return the basename of the file.
	 */
	String basename() const;

	/**
	 * Returns the complete basename of the file, i.e. output.txt == output and output.tar.gz == output.tar.
	 *
	 * @return the complete basename of the file.
	 */
	String completeBasename() const;

	/**
	 * Returns the extension of the file, i.e. output.txt == txt and output.tar.gz == gz.
	 *
	 * @return the extension of the file.
	 */
	String extension() const;

	/**
	 * Returns the complete extension of the file, i.e. output.txt == txt and output.tar.gz == tar.gz.
	 *
	 * @return the complete extension of the file.
	 */
	String completeExtension() const;

	/**
	 * Returns the filename of the file, i.e. output.txt == output.txt and output.tar.gz == output.tar.gz.
	 *
	 * @return the filename of the file.
	 */
	String filename() const;

protected:

	/**
	 * Validates that the path is valid.
	 *
	 * Throws a bump::FileSystemError if the path is not valid.
	 */
	void _validatePath() const;

	/** Instance member variables. */
	boost::filesystem::path _path;
};

}	// End of bump namespace

#endif	// End of BUMP_FILE_INFO_H
