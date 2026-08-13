//
//	TypeCastError.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#include <bump/TypeCastError.h>

namespace bump {

TypeCastError::TypeCastError(const String& description, const String& location)
    : RuntimeError("bump::TypeCastError", description, location) {
    ;
}

}  // namespace bump
