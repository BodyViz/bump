//
//	Exception.h
//	Bump
//
//	Created by Christian Noon on 11/14/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_EXCEPTION_H
#define BUMP_EXCEPTION_H

// Bump headers
#include <bump/Exception.h>
#include <bump/String.h>

/**
 *=============================================================================================================
 *
 *                                   Bump Exception Hierarchy
 *
 *	Exception - PROTECTED (base class exception supporting both logic and runtime errors)
 *	- LogicError - PROTECTED (when error condition could be detected prior to running the application)
 *		- InvalidArgumentError - PUBLIC (when parameter passed into a function is invalid)
 *	- RuntimeError - PROTECTED (when error condition can only be caught at runtime)
 *		- OutOfRangeError - PUBLIC (when container encounters an out-of-range error)
 *		- SearchError - PUBLIC (when a search cannot be found)
 *		- TypeCastError - PUBLIC (when runtime cannot type cast an object as requested)
 *
 *=============================================================================================================
 */

#define BUMP_LOCATION bump::String("Function: ") + __PRETTY_FUNCTION__ + " File: " + __FILE__ + " Line: " + bump::String(__LINE__)

namespace bump {

/**
 * A base class exception supporting both logic and runtime errors.
 */
class BUMP_EXPORT Exception
{
public:

	/**
	 * Destructor.
	 */
	virtual ~Exception() throw() {}

	/**
	 * Creates a string representation of all known information about the exception.
	 *
	 * @return a string representation of all known information about the exception.
	 */
	virtual String description() const throw()
	{
		return String::join(_descriptions, "\n");
	}

	/**
	 * Appends the description and location onto a new line of the message.
	 *
	 * This is VERY useful when you are going to re-thrown an exception and wish
	 * to tack on some additional information to the exception's description.
	 *
	 * @param description the description of the exception.
	 * @param location the file path, line number and function name of where the exception was thrown.
	 */
	void extendDescription(const String& description, const String& location)
	{
		String new_description;
		new_description << _className << ": \"" << description << "\" " << location;
		_descriptions.push_back(new_description);
	}

protected:

	/**
	 * Constructor.
	 *
	 * @param className the class name of the sub-class exception.
	 * @param description the description of the exception.
	 * @param location the file path, line number and function name of where the exception was thrown.
	 */
	Exception(const String& className, const String& description, const String& location) throw() :
		_className(className)
	{
		// Add the description
		extendDescription(description, location);
	}

	/** Instance member variables. */
	String _className;
	StringList _descriptions;
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
	virtual ~LogicError() throw() {}

protected:

	/**
	 * Constructor.
	 *
	 * @param className the class name of the sub-class exception.
	 * @param description the description of the exception.
	 * @param location the file path, line number and function name of where the exception was thrown.
	 */
	LogicError(const String& className, const String& description, const String& location) throw() :
		Exception(className, description, location)
	{
		;
	}
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
	virtual ~RuntimeError() throw() {}

protected:

	/**
	 * Constructor.
	 *
	 * @param className the class name of the sub-class exception.
	 * @param description the description of the exception.
	 * @param location the file path, line number and function name of where the exception was thrown.
	 */
	RuntimeError(const String& className, const String& description, const String& location) throw() :
		Exception(className, description, location)
	{
		;
	}
};

/**
 * A public logic error class which is used when a parameter passed into a function is invalid.
 */
class BUMP_EXPORT InvalidArgumentError : public LogicError
{
public:

	/**
	 * Constructor.
	 *
	 * @param description the description of the exception.
	 * @param location the file path, line number and function name of where the exception was thrown.
	 */
	InvalidArgumentError(const String& description, const String& location) throw() :
		LogicError("bump::InvalidArgumentError", description, location)
	{
		;
	}

	/**
	 * Destructor.
	 */
	~InvalidArgumentError() throw() {}
};

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
	 * @param description the description of the exception.
	 * @param location the file path, line number and function name of where the exception was thrown.
	 */
	OutOfRangeError(const String& description, const String& location) throw() :
		RuntimeError("bump::OutOfRangeError", description, location)
	{
		;
	}

	/**
	 * Destructor.
	 */
	~OutOfRangeError() throw() {}
};

/**
 * A public runtime error class which is used when a search algorithm is started and cannot find
 * anything even though it should.
 */
class BUMP_EXPORT SearchError : public RuntimeError
{
public:

	/**
	 * Constructor.
	 *
	 * @param description the description of the exception.
	 * @param location the file path, line number and function name of where the exception was thrown.
	 */
	SearchError(const String& description, const String& location) throw() :
		RuntimeError("bump::SearchError", description, location)
	{
		;
	}

	/**
	 * Destructor.
	 */
	~SearchError() throw() {}
};

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
	 * @param description the description of the exception.
	 * @param location the file path, line number and function name of where the exception was thrown.
	 */
	TypeCastError(const String& description, const String& location) throw() :
		RuntimeError("bump::TypeCastError", description, location)
	{
		;
	}

	/**
	 * Destructor.
	 */
	~TypeCastError() throw() {}
};

}	// End of bump namespace

#endif	// End of BUMP_EXCEPTION_H
