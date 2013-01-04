//
//  bumpExceptions.cpp
//  Bump
//
//  Created by Christian Noon on 11/15/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/InvalidArgumentError.h>
#include <bump/OutOfRangeError.h>
#include <bump/TypeCastError.h>

void valueMustBePositive(int value)
{
	if (value < 0)
	{
		std::cout << "valueMustBePositive FAILED with a value of " << value << std::endl;
		throw bump::InvalidArgumentError("The value cannot be negative", BUMP_LOCATION);
	}

	std::cout << "valueMustBePositive executed SUCCESSFULLY with a value of " << value << std::endl;
}

void removeItemFromVector(std::vector<double>& values, int itemIndex)
{
	// Make sure item index falls inside the values bounds
	if (itemIndex < 0 || itemIndex > (int)values.size() - 1)
	{
		std::cout << "removeItemFromVector FAILED with an itemIndex of " << itemIndex << std::endl;
		throw bump::OutOfRangeError("The item index was outside the bounds of values", BUMP_LOCATION);
	}

	int previous_size = values.size();
	values.erase(values.begin() + itemIndex);
	std::cout << "removeItemFromVector executed SUCCESSFULLY: old size: " << previous_size << " new size: " << values.size() << std::endl;
}

// Example classes
class Base { virtual void dummy() {} };
class Derived : public Base {};

void tryToTypeCast()
{
	// Create some Base and Derived objects
	Base* base1 = new Derived;
	Base* base2 = new Base;
	Derived* base3;

	// Try to cast base1 to a Derived
	base3 = dynamic_cast<Derived*>(base1);
	if (base3)
	{
		std::cout << "Successfully cast base1 to a Derived" << std::endl;
	}
	else
	{
		throw bump::TypeCastError("Failed to typecast base1 to a Derived", BUMP_LOCATION);
	}

	// Try to cast base2 to a Derived
	base3 = dynamic_cast<Derived*>(base2);
	if (base3)
	{
		std::cout << "Successfully cast base2 to a Derived" << std::endl;
	}
	else
	{
		throw bump::TypeCastError("Failed to typecast base2 to a Derived", BUMP_LOCATION);
	}
}

void firstThrow()
{
	throw bump::InvalidArgumentError("First throw", BUMP_LOCATION);
}

void doubleThrow()
{
	try
	{
		firstThrow();
	}
	catch (bump::Exception& e)
	{
		// You can use the extendDescription method to append an additional description to the exception
		e.extendDescription("Second throw", BUMP_LOCATION);
		throw;
	}
}

/**
 * This example demonstrates how to use the bump::Exception classes.
 *
 * To view the bump::Exception hierarchy, please refer to the documentation provided in
 * the <bump/Exception.h> header.
 *
 * Throughout the Bump library, there are certain cases guarded by exceptions when used
 * incorrectly. These safeguard crashes and give you, the user, the ability to determine
 * what to do at runtime. This example breaks down how you can handle these exceptions if
 * you choose to. It also shows you how to use multiple throws to continue sending the same
 * exception up the stack with additional information.
 *
 * NOTE: If you don't understand the basics of try/catch blocks in C++,
 * then you will need to read up on them before trying to understand
 * bump::Exceptions.
 */
int main(int argc, char **argv)
{
	// Demonstrates how to handle a bump::InvalidArgumentError.
	try
	{
		std::cout << "=================== bump::InvalidArgumentError Example ===================" << std::endl;

		// Runs just fine
		valueMustBePositive(10);

		// Throws an exception
		valueMustBePositive(-4);
	}
	catch (const bump::InvalidArgumentError& e)
	{
		std::cout << e.description() << std::endl;
	}

	// Demonstrates how to handle a bump::OutOfRangeError by catching it as a bump::Exception
	try
	{
		std::cout << "\n=================== bump::OutOfRangeError Example ===================" << std::endl;

		// Runs just fine
		std::vector<double> values;
		values.push_back(20.2);
		values.push_back(100.289);
		removeItemFromVector(values, 1);

		// Throws an exception
		removeItemFromVector(values, 10);
	}
	catch (const bump::InvalidArgumentError& e)
	{
		// This will only catch a bump::InvalidArgumentError exception. Since this is not the type of
		// exception throw in the removeItemFromVector function, this will never actually get called
		// unless we modify the function to also throw this type of exception.
		std::cout << e.description() << std::endl;
	}
	catch (const bump::Exception& e)
	{
		// We can also catch exceptions by using base classes higher up in the bump::Exception
		// inheritance hierarchy. This block will in fact catch any exception thrown by Bump
		// since bump::Exception is the base class for all actual exceptions.
		std::cout << e.description() << std::endl;
	}

	// Demonstrates how to handle a bump::TypeCastError.
	try
	{
		std::cout << "\n=================== bump::TypeCastError Example ===================" << std::endl;

		// Throws an exception
		tryToTypeCast();
	}
	catch (const bump::TypeCastError& e)
	{
		std::cout << e.description() << std::endl;
	}

	// Demonstrates how to use multiple throws to append additional info to the exception.
	try
	{
		std::cout << "\n=================== Multiple Throws Example ===================" << std::endl;

		// Throws an exception twice
		doubleThrow();
	}
	catch (const bump::Exception& e)
	{
		std::cout << e.description() << std::endl;
	}

    return 0;
}
