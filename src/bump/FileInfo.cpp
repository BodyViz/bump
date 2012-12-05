//
//  FileInfo.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/filesystem.hpp>

// Bump headers
#include <bump/FileInfo.h>

using namespace bump;

FileInfo::FileInfo(const String& path) :
	_path(path)
{
	;
}

FileInfo::~FileInfo()
{
	;
}

bool FileInfo::exists() const
{
	return boost::filesystem::exists(_path);
}

bool FileInfo::isAbsolute() const
{
	return _path.has_root_path();
}

bool FileInfo::isRelative() const
{
	return !_path.has_root_path();
}

bool FileInfo::isDirectory() const
{
	return boost::filesystem::is_directory(_path);
}

bool FileInfo::isFile() const
{
	return boost::filesystem::is_regular_file(_path);
}

bool FileInfo::isSymbolicLink() const
{
	return boost::filesystem::is_symlink(_path);
}

bool FileInfo::isHidden() const
{
	// It is not a hidden file if it isn't even a file
	if (exists())
	{
		String filename = _path.filename().string();
		return filename.startsWith(".");
	}

	return false;
}
