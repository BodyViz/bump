//
//	FileSystemError.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/FileSystemError.h>

namespace bump {

FileSystemError::FileSystemError(const String& description, const String& location) throw() :
	RuntimeError("bump::FileSystemError", description, location)
{
	;
}

FileSystemError::~FileSystemError() throw()
{
	;
}

}	// End of bump namespace
