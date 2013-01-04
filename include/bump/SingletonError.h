//
//	SingletonError.h
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#ifndef BUMP_SINGLETON_ERROR_H
#define BUMP_SINGLETON_ERROR_H

// Bump headers
#include <bump/Exception.h>

namespace bump {

/**
 * A public runtime error class used when a singleton's instance method is accessed after it has
 * been destructed.
 */
class BUMP_EXPORT SingletonError : public RuntimeError
{
public:

	/**
	 * Constructor.
	 *
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	SingletonError(const String& description, const String& location) throw();

	/**
	 * Destructor.
	 */
	~SingletonError() throw();
};

}	// End of bump namespace

#endif	// End of BUMP_SINGLETON_ERROR_H
