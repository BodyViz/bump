//
//	TypeCastError.h
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#ifndef BUMP_TYPE_CAST_ERROR_H
#define BUMP_TYPE_CAST_ERROR_H

// Bump headers
#include <bump/Exception.h>

namespace bump {

/**
 * A public runtime error class which is used when the runtime cannot type cast an object
 * as requested.
 */
class BUMP_EXPORT TypeCastError : public RuntimeError
{
public:

	/**
	 * Constructor.
	 *
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	TypeCastError(const String& description, const String& location) throw();

	/**
	 * Destructor.
	 */
	~TypeCastError() throw();
};

}	// End of bump namespace

#endif	// End of BUMP_TYPE_CAST_ERROR_H
