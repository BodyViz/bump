//
//	InvalidArgumentError.h
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#ifndef BUMP_INVALID_ARGUMENT_ERROR_H
#define BUMP_INVALID_ARGUMENT_ERROR_H

// Bump headers
#include <bump/Exception.h>

namespace bump {

/**
 * A public logic error class which is used when a parameter passed into a function is invalid.
 */
class BUMP_EXPORT InvalidArgumentError : public LogicError
{
public:

	/**
	 * Constructor.
	 *
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	InvalidArgumentError(const String& description, const String& location) throw();

	/**
	 * Destructor.
	 */
	~InvalidArgumentError() throw();
};

}	// End of bump namespace

#endif	// End of BUMP_INVALID_ARGUMENT_ERROR_H
