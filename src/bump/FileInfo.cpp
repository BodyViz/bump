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
#include <bump/Exception.h>
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

unsigned long long FileInfo::fileSize() const
{
	// Throw a FileSystemError if the path is not valid
	_validatePath();

	// Throw a FileSystemError if the path is not a file
	if (!isFile())
	{
		String msg = String("The following path is not a file: %1").arg(_path.string());
		throw FileSystemError(msg, BUMP_LOCATION);
	}

	return boost::filesystem::file_size(_path);
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

bool FileInfo::isEmpty() const
{
	_validatePath();
	return boost::filesystem::is_empty(_path);
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

String FileInfo::absolutePath() const
{
	return boost::filesystem::absolute(_path).string();
}

String FileInfo::canonicalPath() const
{
	_validatePath();
	return boost::filesystem::canonical(_path).string();
}

String FileInfo::parentPath() const
{
	return _path.parent_path().string();
}

String FileInfo::basename() const
{
	if (isDirectory())
	{
		return filename();
	}
	else
	{
		String basename = _path.stem().string();
		if (basename.startsWith("."))
		{
			String temp = basename.right(basename.length() - 1);
			if (temp.contains("."))
			{
				basename = basename.left(temp.indexOf(".") + 1);
			}
		}
		else
		{
			if (basename.contains("."))
			{
				basename = basename.left(basename.indexOf("."));
			}
		}

		return basename;
	}
}

String FileInfo::completeBasename() const
{
	if (isDirectory())
	{
		return filename();
	}
	else
	{
		return _path.stem().string();
	}
}

String FileInfo::extension() const
{
	if (isDirectory())
	{
		return String();
	}
	else
	{
		String extension = _path.extension().string();
		if (extension.startsWith("."))
		{
			extension = extension.section(1);
		}

		return extension;
	}
}

String FileInfo::completeExtension() const
{
	if (isDirectory())
	{
		return String();
	}
	else
	{
		String filename = this->filename();
		String basename = this->basename() << ".";
		return filename.remove(basename);
	}
}

String FileInfo::filename() const
{
	return _path.filename().string();
}

void FileInfo::_validatePath() const
{
	if (!boost::filesystem::exists(_path))
	{
		String msg = String("The following path is invalid: %1").arg(_path.string());
		throw FileSystemError(msg, BUMP_LOCATION);
	}
}
