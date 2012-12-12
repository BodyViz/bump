//
//	Enviroment.cpp
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Environment.h>
#include <bump/String.h>

namespace bump {

namespace Environment {

String environmentVariable(const String& name)
{
	char* value = getenv(name.c_str());
	return value == NULL ? String("") : String(value);
}

}	// End of Environment namespace

}	// End of bump namespace
