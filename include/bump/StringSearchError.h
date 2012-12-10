//
//	StringSearchError.h
//	Bump
//
//	Created by Christian Noon on 12/10/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_STRING_SEARCH_ERROR_H
#define BUMP_STRING_SEARCH_ERROR_H

// Bump headers
#include <bump/Exception.h>

namespace bump {

/**
 * A public runtime error class which is used when a string search algorithm is started and cannot
 * find anything even though it should.
 */
class BUMP_EXPORT StringSearchError : public RuntimeError
{
public:

	/**
	 * Constructor.
	 *
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	StringSearchError(const String& description, const String& location) throw() :
		RuntimeError("bump::~StringSearchError", description, location)
	{
		;
	}

	/**
	 * Destructor.
	 */
	~StringSearchError() throw() {}
};

}	// End of bump namespace

#endif	// End of BUMP_STRING_SEARCH_ERROR_H
