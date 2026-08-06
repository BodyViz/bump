//
//	Version.cpp
//	Bump
//
//	Created by Christian Noon on 11/7/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#include <bump/Version.h>

namespace bump {

bump::String version() {
    bump::String version;
    version << BUMP_MAJOR_VERSION << "." << BUMP_MINOR_VERSION << "."
            << BUMP_PATCH_VERSION;

    return version;
}

bump::String majorVersion() { return BUMP_MAJOR_VERSION; }

bump::String minorVersion() { return BUMP_MINOR_VERSION; }

bump::String patchVersion() { return BUMP_PATCH_VERSION; }

bump::String soVersion() { return BUMP_SO_VERSION; }

bump::String libraryName() { return "Bump Library"; }

}  // namespace bump
