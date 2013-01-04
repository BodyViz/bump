//
//	Exception.cpp
//	Bump
//
//	Created by Christian Noon on 1/3/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Exception.h>

namespace bump {

//====================================================================================
//                                      Exception
//====================================================================================

Exception::Exception(const String& className, const String& description, const String& location) throw() :
	_className(className)
{
	// Add the description
	extendDescription(description, location);
}

Exception::~Exception() throw()
{
	;
}

String Exception::description() const throw()
{
	return String::join(_descriptions, "\n");
}

void Exception::extendDescription(const String& description, const String& location)
{
	String new_description;
	new_description << _className << ": \"" << description << "\" " << location;
	_descriptions.push_back(new_description);
}

//====================================================================================
//                                       LogicError
//====================================================================================

LogicError::LogicError(const String& className, const String& description, const String& location) throw() :
	Exception(className, description, location)
{
	;
}

LogicError::~LogicError() throw()
{
	;
}

//====================================================================================
//                                    RuntimeError
//====================================================================================

RuntimeError::RuntimeError(const String& className, const String& description, const String& location) throw() :
	Exception(className, description, location)
{
	;
}

RuntimeError::~RuntimeError() throw()
{
	;
}

}	// End of bump namespace
