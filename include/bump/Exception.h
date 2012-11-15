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
 *		- TypeCastError - PUBLIC (when runtime cannot type cast an object as requested)
 *
 *=============================================================================================================
 */

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
	 * Overrides what method for std::exception.
	 *
	 * @return a string representation of the class name and message attached to the exception.
	 */
	virtual String what() const throw()
	{
		return String() << _className << "\n\t1) " << _message;
	}

	/**
	 * Appends the description onto a new line of the message.
	 *
	 * @param description the long to append onto this string.
	 */
	void operator << (const String& description)
	{
		++_throwCounter;
		_message << "\n\t" << _throwCounter << ") " << description;
	}

protected:

	/**
	 * Constructor.
	 *
	 * @param className the class name of the sub-class exception.
	 * @param message the message to return when calling the what() method of the exception.
	 */
	Exception(const String& className, const String& message) throw() :
		_className(className),
		_message(message),
		_throwCounter(1)
	{
		;
	}

	/** Instance member variables. */
	String _className;
	String _message;
	unsigned int _throwCounter;
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
	 * @param message the message to return when calling the what() method of the exception.
	 */
	LogicError(const String& className, const String& message) throw() : Exception(className, message) {}
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
	 * @param message the message to return when calling the what() method of the exception.
	 */
	RuntimeError(const String& className, const String& message) : Exception(className, message) {}
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
	 * @param message the message to return when calling the what() method of the exception.
	 */
	InvalidArgumentError(const String& message = "") : LogicError("bump::InvalidArgumentError", message) {}

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
	 * @param message the message to return when calling the what() method of the exception.
	 */
	OutOfRangeError(const String& message = "") : RuntimeError("bump::OutOfRangeError", message) {}

	/**
	 * Destructor.
	 */
	~OutOfRangeError() throw() {}
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
	 * @param message the message to return when calling the what() method of the exception.
	 */
	TypeCastError(const String& message = "") : RuntimeError("bump::TypeCastError", message) {}

	/**
	 * Destructor.
	 */
	~TypeCastError() throw() {}
};

}	// End of bump namespace

#endif	// End of BUMP_EXCEPTION_H
