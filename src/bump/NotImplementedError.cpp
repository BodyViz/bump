//
//	NotImplementedError.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#include <bump/NotImplementedError.h>

namespace bump {

NotImplementedError::NotImplementedError(const String& description,
                                         const String& location)
    : RuntimeError("bump::NotImplementedError", description, location) {
    ;
}

}  // namespace bump
