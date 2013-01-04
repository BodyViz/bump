//
//	OutOfRangeError.cpp
//	Bump
//
//	Created by Christian Noon on 1/3/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/OutOfRangeError.h>

namespace bump {

OutOfRangeError::OutOfRangeError(const String& description, const String& location) throw() :
	RuntimeError("bump::OutOfRangeError", description, location)
{
	;
}

OutOfRangeError::~OutOfRangeError() throw()
{
	;
}

}	// End of bump namespace
