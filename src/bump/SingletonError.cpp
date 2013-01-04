//
//	SingletonError.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/SingletonError.h>

namespace bump {

SingletonError::SingletonError(const String& description, const String& location) throw() :
	RuntimeError("bump::SingletonError", description, location)
{
	;
}

SingletonError::~SingletonError() throw()
{
	;
}

}	// End of bump namespace
