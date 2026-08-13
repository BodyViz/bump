//
//	StringSearchError.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#include <bump/StringSearchError.h>

namespace bump {

StringSearchError::StringSearchError(const String& description,
                                     const String& location)
    : RuntimeError("bump::StringSearchError", description, location) {
    ;
}

}  // namespace bump
