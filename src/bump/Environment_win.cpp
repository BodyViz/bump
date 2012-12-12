//
//	Enviroment_win.cpp
//	Bump
//
//	Created by Christian Noon on 12/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Environment.h>
#include <bump/String.h>

// Windows headers
#include <windows.h>
#include <Lmcons.h>

namespace bump {

namespace Environment {

bool setEnvironmentVariable(const String& name, const String& value, bool overwrite)
{
	int result = 0;
	bool exists = !environmentVariable(name).isEmpty();
	if (overwrite || !exists)
	{
		result = _putenv_s(name.c_str(), value.c_str());
	}

	return result == 0;
}

bool unsetEnvironmentVariable(const String& name)
{
	int result = _putenv_s(name.c_str(), "");
	return result == 0;
}

String currentUsername()
{
	char username[UNLEN+1];
	GetUserName(username, (LPDWORD)UNLEN+1);
	return username;
}

}	// End of Environment namespace

}	// End of bump namespace
