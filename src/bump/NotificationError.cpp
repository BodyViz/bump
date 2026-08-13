//
//	NotificationError.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#include <bump/NotificationError.h>

namespace bump {

NotificationError::NotificationError(const String& description,
                                     const String& location)
    : RuntimeError("bump::NotificationError", description, location) {
    ;
}

}  // namespace bump
