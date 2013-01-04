//
//	NotImplementedError.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/NotImplementedError.h>

namespace bump {

NotImplementedError::NotImplementedError(const String& description, const String& location) throw() :
	RuntimeError("bump::NotImplementedError", description, location)
{
	;
}

NotImplementedError::~NotImplementedError() throw()
{
	;
}

}	// End of bump namespace
