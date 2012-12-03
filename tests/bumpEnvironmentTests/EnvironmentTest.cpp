//
//	EnvironmentTest.cpp
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Environment.h>
#include <bump/String.h>

// bumpTest headers
#include "../bumpTest/BaseTest.h"

namespace bumpTest {

/**
 * This is our main environment testing class. The SetUp and TearDown methods are
 * executed before the test runs and after it completes. This is where we can
 * add any custom set up for each test without having to add this to "every"
 * test individually.
 */
class EnvironmentTest : public BaseTest
{
protected:

	/** Run immediately before a test starts. Starts the timer. */
	void SetUp()
	{
		// Call the parent setup method
		BaseTest::SetUp();

		// Set a default environment variable
		_environmentVariable = bump::String("BumpTest");
		_expectedValue = bump::String("this is my value");
		bump::Environment::setEnvironmentVariable(_environmentVariable, _expectedValue);
	}

	/** Invoked immediately after a test finishes. Stops the timer. */
	void TearDown()
	{
		// Call the parent tear down method
		BaseTest::TearDown();

		// Unset the default environment variable
		bump::Environment::unsetEnvironmentVariable(_environmentVariable);
	}

	/** Instance member variables. */
	bump::String _environmentVariable;
	bump::String _expectedValue;
};

TEST_F(EnvironmentTest, testEnvironmentVariable)
{
	// Test the default environment variable
	bump::String actual_value = bump::Environment::environmentVariable(_environmentVariable);
	EXPECT_STREQ(_expectedValue.c_str(), actual_value.c_str());

	// Test a ridiculous environment variable that does not exist
	actual_value = bump::Environment::environmentVariable("XYZ5674$$ABC");
	EXPECT_STREQ("", actual_value.c_str());
}

TEST_F(EnvironmentTest, testSetEnvironmentVariable)
{
	// Test the default environment variable
	bump::String actual_value = bump::Environment::environmentVariable(_environmentVariable);
	EXPECT_STREQ(_expectedValue.c_str(), actual_value.c_str());

	// Try to overwrite the default environment variable without forcing the overwrite flag
	bump::Environment::setEnvironmentVariable(_environmentVariable, "Attempt 2", false);
	actual_value = bump::Environment::environmentVariable(_environmentVariable);
	EXPECT_STREQ(_expectedValue.c_str(), actual_value.c_str());

	// Try to overwrite the default environment variable again with forcing the overwrite flag
	bump::Environment::setEnvironmentVariable(_environmentVariable, "Attempt 3", true);
	actual_value = bump::Environment::environmentVariable(_environmentVariable);
	EXPECT_STREQ("Attempt 3", actual_value.c_str());
}

TEST_F(EnvironmentTest, testUnsetEnvironmentVariable)
{
	// Test the default environment variable
	bump::String actual_value = bump::Environment::environmentVariable(_environmentVariable);
	EXPECT_STREQ(_expectedValue.c_str(), actual_value.c_str());

	// Unset the default environment variable
	bump::Environment::unsetEnvironmentVariable(_environmentVariable);
	actual_value = bump::Environment::environmentVariable(_environmentVariable);
	EXPECT_STREQ("", actual_value.c_str());

	// Try to unset a ridiculous environment variable that does not exist
	bump::String odd("XYZ5674$$ABC");
	bump::Environment::unsetEnvironmentVariable(odd);
	actual_value = bump::Environment::environmentVariable(odd);
	EXPECT_STREQ("", actual_value.c_str());
}

}	// End of bumpTest namespace
