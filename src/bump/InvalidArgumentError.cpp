//
//	InvalidArgumentError.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/InvalidArgumentError.h>

namespace bump {

InvalidArgumentError::InvalidArgumentError(const String& description, const String& location) throw() :
	LogicError("bump::InvalidArgumentError", description, location)
{
	;
}

InvalidArgumentError::~InvalidArgumentError() throw()
{
	;
}

}	// End of bump namespace
