//
//	Version.cpp
//	Bump
//
//	Created by Christian Noon on 11/7/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Version.h>

namespace bump {

String bumpGetVersion()
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

String bumpGetSOVersion()
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

String bumpGetLibraryName()
{
	return "Bump Library";
}

}	// End of bump namespace
