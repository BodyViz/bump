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

String FileSystem::join(const String& path1, const String& path2)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	joined_path /= path6;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6, const String& path7)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	joined_path /= path6;
	joined_path /= path7;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6, const String& path7, const String& path8)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	joined_path /= path6;
	joined_path /= path7;
	joined_path /= path8;
	return joined_path.string();
}

String FileSystem::join(const String& path1, const String& path2, const String& path3, const String& path4,
						const String& path5, const String& path6, const String& path7, const String& path8,
						const String& path9)
{
	boost::filesystem::path joined_path(path1);
	joined_path /= path2;
	joined_path /= path3;
	joined_path /= path4;
	joined_path /= path5;
	joined_path /= path6;
	joined_path /= path7;
	joined_path /= path8;
	joined_path /= path9;
	return joined_path.string();
}

void FileSystem::setCurrentPath(const String& path)
{
	// Make sure the path is valid
	boost::filesystem::path new_path(path);
	if (!boost::filesystem::exists(new_path))
	{
		String msg = String("The following path is invalid: %1").arg(path);
		throw FileSystemError(msg, BUMP_LOCATION);
	}

	// Set the current path
	boost::filesystem::current_path(boost::filesystem::path(path));
}

String FileSystem::currentPath()
{
	return boost::filesystem::current_path().string();
}

String FileSystem::temporaryPath()
{
	return boost::filesystem::temp_directory_path().string();
}
