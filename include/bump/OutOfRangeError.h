//
//	OutOfRangeError.h
//	Bump
//
//	Created by Christian Noon on 1/3/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#ifndef BUMP_OUT_OF_RANGE_ERROR_H
#define BUMP_OUT_OF_RANGE_ERROR_H

// Bump headers
#include <bump/Exception.h>

namespace bump {

/**
 * A public runtime error class which is used when a container class receives an out-of-range
 * request from the runtime.
 */
class BUMP_EXPORT OutOfRangeError : public RuntimeError
{
public:

	/**
	 * Constructor.
	 *
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	OutOfRangeError(const String& description, const String& location) throw();

	/**
	 * Destructor.
	 */
	~OutOfRangeError() throw();
};

}	// End of bump namespace

#endif	// End of BUMP_OUT_OF_RANGE_ERROR_H
