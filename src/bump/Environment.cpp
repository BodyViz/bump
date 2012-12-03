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

using namespace bump;

Environment::Environment()
{
	;
}

Environment::~Environment()
{
	;
}

String Environment::environmentVariable(const String& name)
{
	char* value = getenv(name.c_str());
	return value == NULL ? String("") : String(value);
}

bool Environment::setEnvironmentVariable(const String& name, const String& value, bool overwrite)
{
	int result = setenv(name.c_str(), value.c_str(), overwrite);
	return result == 0;
}

bool Environment::unsetEnvironmentVariable(const String& name)
{
	int result = unsetenv(name.c_str());
	return result == 0;
}
