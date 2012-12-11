//
//	Enviroment.cpp
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/config.hpp>

// Bump headers
#include <bump/Environment.h>
#include <bump/String.h>

// Windows headers
#ifdef BOOST_WINDOWS
	#include <windows.h>
	#include <Lmcons.h>
#endif

namespace bump {

namespace Environment {

String environmentVariable(const String& name)
{
	char* value = getenv(name.c_str());
	return value == NULL ? String("") : String(value);
}

bool setEnvironmentVariable(const String& name, const String& value, bool overwrite)
{
#ifdef BOOST_WINDOWS
	int result = 0;
	bool exists = !environmentVariable(name).isEmpty();
	if (overwrite || !exists)
	{
		result = _putenv_s(name.c_str(), value.c_str());
	}
#else
	int result = setenv(name.c_str(), value.c_str(), overwrite);
#endif

	return result == 0;
}

bool unsetEnvironmentVariable(const String& name)
{
#ifdef BOOST_WINDOWS
	int result = _putenv_s(name.c_str(), "");
#else
	int result = unsetenv(name.c_str());
#endif

	return result == 0;
}

String currentUsername()
{
#ifdef BOOST_WINDOWS
	
	// On Windows, use the Windows calls
	char username[UNLEN+1];
	GetUserName(username, (LPDWORD)UNLEN+1);
	return username;

#else

	// On Unix, we use the "USER" and "USERNAME" environment variables. First try the "USER" environment variable.
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

}	// End of Environment namespace

}	// End of bump namespace
