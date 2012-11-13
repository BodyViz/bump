//
//	Version.cpp
//	Bump
//
//	Created by Christian Noon on 11/7/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#include <bump/Version.h>

bump::String bump::bumpGetVersion()
{
	static bool shouldInitialize = true;
	static bump::String bumpVersion;
	if (shouldInitialize)
	{
		if (BUMP_SOVERSION == 0)
		{
			bumpVersion << BUMP_MAJOR_VERSION << "." << BUMP_MINOR_VERSION << "." << BUMP_PATCH_VERSION;
		}
		else
		{
			bumpVersion << BUMP_MAJOR_VERSION << "." << BUMP_MINOR_VERSION << "." << BUMP_PATCH_VERSION << "-" << BUMP_SOVERSION;
		}

		shouldInitialize = false;
	}

	return bumpVersion;
}

bump::String bump::bumpGetSOVersion()
{
	static bool shouldInitialize = true;
	static bump::String bumpSOVersion;
	if (shouldInitialize)
	{
		bumpSOVersion << BUMP_SOVERSION;
		shouldInitialize = false;
	}

	return bumpSOVersion;
}

bump::String bump::bumpGetLibraryName()
{
	return "Bump Library";
}
