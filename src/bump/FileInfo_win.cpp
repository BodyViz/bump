//
//  FileInfo_win.cpp
//  Bump
//
//  Created by Christian Noon on 12/12/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/FileInfo.h>
#include <bump/NotImplementedError.h>

using namespace bump;

//====================================================================================
//                           Permissions Query Methods
//====================================================================================

bool FileInfo::isReadableByUser() const
{
	String msg = "The bump::FileInfo::isReadableByUser() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isWritableByUser() const
{
	String msg = "The bump::FileInfo::isWritableByUser() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isExecutableByUser() const
{
	String msg = "The bump::FileInfo::isExecutableByUser() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isReadableByOwner() const
{
	String msg = "The bump::FileInfo::isReadableByOwner() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isWritableByOwner() const
{
	String msg = "The bump::FileInfo::isWritableByOwner() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isExecutableByOwner() const
{
	String msg = "The bump::FileInfo::isExecutableByOwner() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isReadableByGroup() const
{
	String msg = "The bump::FileInfo::isReadableByGroup() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isWritableByGroup() const
{
	String msg = "The bump::FileInfo::isWritableByGroup() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isExecutableByGroup() const
{
	String msg = "The bump::FileInfo::isExecutableByGroup() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isReadableByOthers() const
{
	String msg = "The bump::FileInfo::isReadableByOthers() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isWritableByOthers() const
{
	String msg = "The bump::FileInfo::isWritableByOthers() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

bool FileInfo::isExecutableByOthers() const
{
	String msg = "The bump::FileInfo::isExecutableByOthers() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

String FileInfo::owner() const
{
	String msg = "The bump::FileInfo::owner() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

unsigned int FileInfo::ownerId() const
{
	String msg = "The bump::FileInfo::ownerId() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

String FileInfo::group() const
{
	String msg = "The bump::FileInfo::group() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}

unsigned int FileInfo::groupId() const
{	
	String msg = "The bump::FileInfo::groupId() method is not implemented on Windows";
	throw NotImplementedError(msg, BUMP_LOCATION);
}
