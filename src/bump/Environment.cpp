//
//	Enviroment.cpp
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#include <bump/Environment.h>
#include <bump/String.h>

namespace bump {

namespace Environment {

String environmentVariable(const String& name) {
    char* value = getenv(name.c_str());
    return value == nullptr ? String("") : String(value);
}

}  // namespace Environment

}  // namespace bump
