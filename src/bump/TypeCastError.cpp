//
//	TypeCastError.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/TypeCastError.h>

namespace bump {

TypeCastError::TypeCastError(const String& description, const String& location) throw() :
	RuntimeError("bump::TypeCastError", description, location)
{
	;
}

TypeCastError::~TypeCastError() throw()
{
	;
}

}	// End of bump namespace
