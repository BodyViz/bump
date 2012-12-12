//
//  FileSystem_win.cpp
//  Bump
//
//  Created by Christian Noon on 12/12/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/FileSystem.h>
#include <bump/NotImplementedError.h>

namespace bump {

namespace FileSystem {

//====================================================================================
//                                Permissions Methods
//====================================================================================

bool setPermissions(const String& path, Permissions permissions)
{
	String msg = "The bump::FileSystem::setPermissions() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

Permissions permissions(const String& path)
{
	String msg = "The bump::FileSystem::permissions() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool setIsReadableByOwner(const String& path, bool isReadable)
{
	String msg = "The bump::FileSystem::setIsReadableByOwner() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool setIsWritableByOwner(const String& path, bool isWritable)
{
	String msg = "The bump::FileSystem::setIsWritableByOwner() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool setIsExecutableByOwner(const String& path, bool isExecutable)
{
	String msg = "The bump::FileSystem::setIsExecutableByOwner() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool setIsReadableByGroup(const String& path, bool isReadable)
{
	String msg = "The bump::FileSystem::setIsReadableByGroup() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool setIsWritableByGroup(const String& path, bool isWritable)
{
	String msg = "The bump::FileSystem::setIsWritableByGroup() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool setIsExecutableByGroup(const String& path, bool isExecutable)
{
	String msg = "The bump::FileSystem::setIsExecutableByGroup() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool setIsReadableByOthers(const String& path, bool isReadable)
{
	String msg = "The bump::FileSystem::setIsReadableByOthers() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool setIsWritableByOthers(const String& path, bool isWritable)
{
	String msg = "The bump::FileSystem::setIsWritableByOthers() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool setIsExecutableByOthers(const String& path, bool isExecutable)
{
	String msg = "The bump::FileSystem::setIsExecutableByOthers() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

}	// End of FileSystem namespace

}	// End of bump namespace
