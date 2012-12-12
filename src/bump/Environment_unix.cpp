//
//	Enviroment_unix.cpp
//	Bump
//
//	Created by Christian Noon on 12/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Environment.h>
#include <bump/String.h>

namespace bump {

namespace Environment {

bool setEnvironmentVariable(const String& name, const String& value, bool overwrite)
{
	int result = setenv(name.c_str(), value.c_str(), overwrite);
	return result == 0;
}

bool unsetEnvironmentVariable(const String& name)
{
	int result = unsetenv(name.c_str());
	return result == 0;
}

String currentUsername()
{
	// On Unix, we use the "USER" and "USERNAME" environment variables. First try the "USER" environment variable.
	String username = environmentVariable("USER");
	if (!username.isEmpty())
	{
		return username;
	}

	// Now try the "USERNAME" environment variable since the "USER" environment variable was empty
	username = environmentVariable("USERNAME");
	return username;
}

}	// End of Environment namespace

}	// End of bump namespace
