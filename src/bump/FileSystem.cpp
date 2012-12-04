//
//  FileSystem.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/filesystem.hpp>

// Bump headers
#include <bump/Exception.h>
#include <bump/FileSystem.h>

using namespace bump;

FileSystem::FileSystem()
{
	;
}

FileSystem::~FileSystem()
{
	;
}

void FileSystem::setCurrentPath(const String& path)
{
	// Make sure the path is valid
	boost::filesystem::path new_path(path);
	if (!boost::filesystem::exists(new_path))
	{
		String msg = String("The following path is invalid and could not be set as the current path: %1").arg(path);
		throw FileSystemError(msg, BUMP_LOCATION);
	}

	// Set the current path
	boost::filesystem::current_path(boost::filesystem::path(path));
}

String FileSystem::currentPath()
{
	return boost::filesystem::current_path().string();
}
