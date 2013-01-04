//
//	Exception.h
//	Bump
//
//	Created by Christian Noon on 11/14/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_EXCEPTION_H
#define BUMP_EXCEPTION_H

// Boost headers
#include <boost/current_function.hpp>

// Bump headers
#include <bump/Export.h>
#include <bump/String.h>

/**
 * The BUMP_LOCATION is used in exceptions to place the function name, filename and line number directly
 * into the description for the exception. This makes everything much easier to debug when exceptions are
 * actually thrown.
 */
#define BUMP_LOCATION bump::String("Function: ") + BOOST_CURRENT_FUNCTION + " File: " + __FILE__ + " Line: " + bump::String(__LINE__)

namespace bump {

/**
 * A base class exception supporting both logic and runtime errors.
 *
 * The following is a list of the common Bump Exception Hierarchy:
 * - Exception - PROTECTED (base class exception supporting both logic and runtime errors)
 *     - LogicError - PROTECTED (when error condition could be detected prior to running the application)
 *         - InvalidArgumentError - PUBLIC (when parameter passed into a function is invalid)
 *     - RuntimeError - PROTECTED (when error condition can only be caught at runtime)
 *         - NotImplementedError - PUBLIC (when a function, method or scope has not yet been implemented)
 *         - OutOfRangeError - PUBLIC (when container encounters an out-of-range error)
 *         - StringSearchError - PUBLIC (when a string search algorithm is started and cannot find anything when it should)
 *         - TypeCastError - PUBLIC (when runtime cannot type cast an object as requested)
 */
class BUMP_EXPORT Exception
{
public:

	/**
	 * Destructor.
	 */
	virtual ~Exception() throw();

	/**
	 * Creates a string representation of all known information about the exception.
	 *
	 * @return A string representation of all known information about the exception.
	 */
	virtual String description() const throw();

	/**
	 * Appends the description and location onto a new line of the message.
	 *
	 * This is VERY useful when you are going to re-thrown an exception and wish
	 * to tack on some additional information to the exception's description.
	 *
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	void extendDescription(const String& description, const String& location);

protected:

	/**
	 * @internal
	 * Constructor.
	 *
	 * @param className The class name of the sub-class exception.
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	Exception(const String& className, const String& description, const String& location) throw();

	// Instance member variables
	String			_className;			/**< @internal The class name of the exception. */
	StringList		_descriptions;		/**< @internal A list of descriptions each time an exception is thrown or re-thrown. */
};

/**
 * A abstract, protected exception class containing error subclasses whose error condition could be
 * detected prior to running the application.
 */
class BUMP_EXPORT LogicError : public Exception
{
public:

	/**
	 * Destructor.
	 */
	virtual ~LogicError() throw();

protected:

	/**
	 * @internal
	 * Constructor.
	 *
	 * @param className The class name of the sub-class exception.
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	LogicError(const String& className, const String& description, const String& location) throw();
};

/**
 * An abstract, protected exception class containing error subclasses whose error condition can only
 * be detected at runtime.
 */
class BUMP_EXPORT RuntimeError : public Exception
{
public:

	/**
	 * Destructor.
	 */
	virtual ~RuntimeError() throw();

protected:

	/**
	 * @internal
	 * Constructor.
	 *
	 * @param className The class name of the sub-class exception.
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	RuntimeError(const String& className, const String& description, const String& location) throw();
};

}	// End of bump namespace

#endif	// End of BUMP_EXCEPTION_H
