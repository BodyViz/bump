//
//	NotificationError.h
//	Bump
//
//	Created by Christian Noon on 12/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_NOT_IMPLEMENTED_ERROR_H
#define BUMP_NOT_IMPLEMENTED_ERROR_H

// Bump headers
#include <bump/Exception.h>

namespace bump {

/**
 * A public runtime error class which is used when a function or method simply has not yet
 * been implemented and should not be used. This will generally be the case when there is
 * cross-platform code that has not yet been properly implemented on one of the platforms.
 */
class BUMP_EXPORT NotImplementedError : public RuntimeError
{
public:

	/**
	 * Constructor.
	 *
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	NotImplementedError(const String& description, const String& location) throw() :
		RuntimeError("bump::NotImplementedError", description, location)
	{
		;
	}

	/**
	 * Destructor.
	 */
	~NotImplementedError() throw() {}
};

}	// End of bump namespace

#endif	// End of BUMP_NOT_IMPLEMENTED_ERROR_H
