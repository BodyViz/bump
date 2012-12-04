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

bool FileInfo::isAbsolute()
{
	return _path.has_root_path();
}

bool FileInfo::isRelative()
{
	return !_path.has_root_path();
}

bool FileInfo::isDirectory()
{
	return boost::filesystem::is_directory(_path);
}

bool FileInfo::isFile()
{
	return boost::filesystem::is_regular_file(_path);
}

bool FileInfo::isSymbolicLink()
{
	return boost::filesystem::is_symlink(_path);
}
