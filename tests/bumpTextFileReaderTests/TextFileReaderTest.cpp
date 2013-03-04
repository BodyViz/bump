//
//	StringTest.cpp
//	Bump
//
//	Created by Christian Noon on 11/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// C++ headers
#include <limits>

// Bump headers
#include <bump/InvalidArgumentError.h>
#include <bump/OutOfRangeError.h>
#include <bump/String.h>
#include <bump/StringSearchError.h>
#include <bump/TypeCastError.h>

// bumpTest headers
#include "../bumpTest/BaseTest.h"

namespace bumpTest {

/**
 * This is our main string testing class. The SetUp and TearDown methods are
 * executed before the test runs and after it completes. This is where we can
 * add any custom set up for each test without having to add this to "every"
 * test individually.
 */
class TextFileReaderTest : public BaseTest
{
protected:

	/** Run immediately before a test starts. Starts the timer. */
	void SetUp()
	{
		// Call the parent setup method
		BaseTest::SetUp();

		// Any custom setup we may need
	}

	/** Invoked immediately after a test finishes. Stops the timer. */
	void TearDown()
	{
		// Call the parent tear down method
		BaseTest::TearDown();

		// Any custom teardown you may need
	}
};

TEST_F(TextFileReaderTest, testEmptyConstructor)
{
	bump::String empty_string_1;
	bump::String empty_string_2("");
	EXPECT_STREQ(empty_string_1.c_str(), empty_string_2.c_str());
}


}	// End of bumpTest namespace
