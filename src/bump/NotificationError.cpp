//
//	NotificationError.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/NotificationError.h>

namespace bump {

NotificationError::NotificationError(const String& description, const String& location) throw() :
	RuntimeError("bump::NotificationError", description, location)
{
	;
}

NotificationError::~NotificationError() throw()
{
	;
}

}	// End of bump namespace
