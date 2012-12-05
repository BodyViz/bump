//
//	Enviroment.cpp
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Windows headers
#ifdef _WIN32
#include <windows.h>
#include <Lmcons.h>
#endif

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

String Environment::currentUsername()
{
#ifdef _WIN32
	// On windows, use the windows calls
	char username[UNLEN+1];
	GetUserName(username, UNLEN+1);
	return username;
#else
	// On unix, we use the "USER" and "USERNAME" environment variables. First try the "USER" environment variable.
	String username = environmentVariable("USER");
	if (!username.isEmpty())
	{
		return username;
	}

	// Now try the "USERNAME" environment variable since the "USER" environment variable was empty
	username = environmentVariable("USERNAME");
	return username;
#endif
}
