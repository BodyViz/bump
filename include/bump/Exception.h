//
//	Exception.h
//	Bump
//
//	Created by Christian Noon on 11/14/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#pragma once

#include <bump/Export.h>
#include <bump/String.h>

#include <boost/current_function.hpp>
#include <exception>

// MSVC C4251: bump::Exception holds bump::String members, which derive from
// std::string and so have no dll-interface.
//
// C4275: std::exception is the base and has none either. Confirmed on MSVC
// 14.44 -- without this every translation unit including the header fails
// under warnings-as-errors. It is unavoidable for an exported type that wants
// to be caught by a consumer's ordinary handler, and benign here because the
// base comes from the CRT, which both sides share.
//
// Both scoped to this header so neither suppression reaches consumer code.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4251)  // needs dll-interface to be used by clients
#pragma warning(disable : 4275)  // non dll-interface base for exported class
#endif

/**
 * The BUMP_LOCATION is used in exceptions to place the function name, filename
 * and line number directly into the description for the exception. This makes
 * everything much easier to debug when exceptions are actually thrown.
 */
#define BUMP_LOCATION                                     \
    bump::String("Function: ") + BOOST_CURRENT_FUNCTION + \
        " File: " + __FILE__ + " Line: " + bump::String(__LINE__)

namespace bump {

/**
 * A base class exception supporting both logic and runtime errors.
 *
 * The following is a list of the common Bump Exception Hierarchy:
 * - Exception - PROTECTED (base class exception supporting both logic and
 * runtime errors)
 *     - LogicError - PROTECTED (when error condition could be detected prior to
 * running the application)
 *         - InvalidArgumentError - PUBLIC (when parameter passed into a
 * function is invalid)
 *     - RuntimeError - PROTECTED (when error condition can only be caught at
 * runtime)
 *         - NotImplementedError - PUBLIC (when a function, method or scope has
 * not yet been implemented)
 *         - OutOfRangeError - PUBLIC (when container encounters an out-of-range
 * error)
 *         - StringSearchError - PUBLIC (when a string search algorithm is
 * started and cannot find anything when it should)
 *         - TypeCastError - PUBLIC (when runtime cannot type cast an object as
 * requested)
 */
class BUMP_EXPORT Exception : public std::exception {
public:
    /**
     * Destructor.
     */
    ~Exception() override = default;

    /**
     * Creates a string representation of all known information about the
     * exception.
     *
     * @return A string representation of all known information about the
     * exception.
     */
    virtual String description() const;

    /**
     * The same text as description(), as a null terminated string.
     *
     * This is what makes a bump exception catchable, and reportable, by a
     * consumer that knows nothing about bump beyond std::exception.
     *
     * @return The description, valid until the exception is modified or
     * destroyed.
     */
    const char* what() const noexcept override;

    /**
     * Appends the description and location onto a new line of the message.
     *
     * This is VERY useful when you are going to re-thrown an exception and wish
     * to tack on some additional information to the exception's description.
     *
     * @param description The description of the exception.
     * @param location The file path, line number and function name of where the
     * exception was thrown.
     */
    void extendDescription(const String& description, const String& location);

protected:
    /**
     * @internal
     * Constructor.
     *
     * @param className The class name of the sub-class exception.
     * @param description The description of the exception.
     * @param location The file path, line number and function name of where the
     * exception was thrown.
     */
    Exception(const String& className, const String& description,
              const String& location);

    // Instance member variables
    String _className;   /**< @internal The class name of the exception. */
    String _description; /**< @internal The accumulated description, one line
                            per throw or re-throw. Held whole rather than
                            joined on demand so what() has something with a
                            lifetime to hand back. */
};

/**
 * A abstract, protected exception class containing error subclasses whose error
 * condition could be detected prior to running the application.
 */
class BUMP_EXPORT LogicError : public Exception {
public:
    /**
     * Destructor.
     */
    ~LogicError() override = default;

protected:
    /**
     * @internal
     * Constructor.
     *
     * @param className The class name of the sub-class exception.
     * @param description The description of the exception.
     * @param location The file path, line number and function name of where the
     * exception was thrown.
     */
    LogicError(const String& className, const String& description,
               const String& location);
};

/**
 * An abstract, protected exception class containing error subclasses whose
 * error condition can only be detected at runtime.
 */
class BUMP_EXPORT RuntimeError : public Exception {
public:
    /**
     * Destructor.
     */
    ~RuntimeError() override = default;

protected:
    /**
     * @internal
     * Constructor.
     *
     * @param className The class name of the sub-class exception.
     * @param description The description of the exception.
     * @param location The file path, line number and function name of where the
     * exception was thrown.
     */
    RuntimeError(const String& className, const String& description,
                 const String& location);
};

}  // namespace bump

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
