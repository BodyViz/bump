//
//	Exception.cpp
//	Bump
//
//	Created by Christian Noon on 1/3/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#include <bump/Exception.h>

namespace bump {

//=============================================================================
//                                      Exception
//=============================================================================

Exception::Exception(const String& className, const String& description,
                     const String& location)
    : _className(className) {
    // Add the description
    extendDescription(description, location);
}

String Exception::description() const { return _description; }

const char* Exception::what() const noexcept { return _description.c_str(); }

void Exception::extendDescription(const String& description,
                                  const String& location) {
    if (!_description.isEmpty()) {
        _description << "\n";
    }

    _description << _className << ": \"" << description << "\" " << location;
}

//=============================================================================
//                                       LogicError
//=============================================================================

LogicError::LogicError(const String& className, const String& description,
                       const String& location)
    : Exception(className, description, location) {
    ;
}

//=============================================================================
//                                    RuntimeError
//=============================================================================

RuntimeError::RuntimeError(const String& className, const String& description,
                           const String& location)
    : Exception(className, description, location) {
    ;
}

}  // namespace bump
