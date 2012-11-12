//
//  main.cpp
//  Bump
//
//  Created by Christian Noon on 11/12/12.
//  Copyright (c) 2011 Christian Noon. All rights reserved.
//

#include <gtest/gtest.h>
#include "../bumpTest/BaseTest.h"
#include "../bumpTest/EnvironmentFixture.h"

#include <bump/String.h>

/**
 * This test TODO...
 */
int main(int argc, char **argv)
{
	std::cout << "Begin running all tests...\n\n";

	// Setup the environment
	testing::AddGlobalTestEnvironment(new bumpTest::EnvironmentFixture);

	// Initialize everything and run all the tests
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace bumpTest {

/** TODO. */
class StringTest : public BaseTest
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

/**
 * All Possible Checks:
 * - EXPECT_FALSE (condition)                            = condition is true
 * - EXPECT_TRUE  (condition)                            = condition is false
 *
 * - EXPECT_EQ    (expected, actual)                     = expected == actual
 * - EXPECT_NE    (val1, val2)                           = val1 != val2
 * - EXPECT_LT    (val1, val2)                           = val1 < val2
 * - EXPECT_LE    (val1, val2)                           = val1 <= val2
 * - EXPECT_GT    (val1, val2)                           = val1 > val2
 * - EXPECT_GE    (val1, val2)                           = val1 >= val2
 *
 * - EXPECT_STREQ (expected.c_str(), actual.c_str())     = expected == actual
 * - EXPECT_STRNE (expected.c_str(), actual.c_str())     = expected != actual
 * - EXPECT_STRCASEEQ (expected.c_str(), actual.c_str()) = expected == actual (ignoring case)
 * - EXPECT_STRCASENE (expected.c_str(), actual.c_str()) = expected != actual (ignoring case)
 *
 * - EXPECT_FLOAT_EQ (expected, actual)                  = expected almost equal to actual
 * - EXPECT_DOUBLE_EQ (expected, actual)                 = expected almost equal to actual
 * - EXPECT_NEAR (val1, val2, abs_error)                 = difference between val1 and val2 doesn't exceed abs_error
 */

TEST_F(StringTest, testEmptyConstructor)
{
    bump::String empty_string_1;
	bump::String empty_string_2("");
	EXPECT_STREQ(empty_string_1.c_str(), empty_string_2.c_str());
}

TEST_F(StringTest, testCharStarConstructor)
{
	const char* char_star = "char star";
	bump::String char_str(char_star);
	EXPECT_STREQ(char_star, char_str.c_str());
}

TEST_F(StringTest, testStdStringConstructor)
{
	std::string std_string = "std::string";
	bump::String std_str(std_string);
	EXPECT_STREQ(std_string.c_str(), std_str.c_str());
}

TEST_F(StringTest, testUnsignedCharConstructor)
{
	// Check in-range case
	unsigned char my_char = 27;
	bump::String my_str(my_char);
	EXPECT_STREQ("27", my_str.c_str());

	// Check out-of-range negative case
	my_char = -100;
	my_str = bump::String(my_char);
	EXPECT_STRNE("-100", my_str.c_str());

	// Check out-of-range positive case
	my_char = 260;
	my_str = bump::String(my_char);
	EXPECT_STRNE("260", my_str.c_str());
}

TEST_F(StringTest, testCharConstructor)
{
	// Check positive in-range case
	char my_char = 27;
	bump::String my_str(my_char);
	EXPECT_STREQ("27", my_str.c_str());

	// Check negative in-range case
	my_char = -50;
	my_str = bump::String(my_char);
	EXPECT_STREQ("-50", my_str.c_str());

	// Check out-of-range negative case
	my_char = -220;
	my_str = bump::String(my_char);
	EXPECT_STRNE("-220", my_str.c_str());

	// Check out-of-range positive case
	my_char = 220;
	my_str = bump::String(my_char);
	EXPECT_STRNE("220", my_str.c_str());
}

TEST_F(StringTest, testUnsignedShortConstructor)
{
	// Check in-range case
	unsigned short my_short = 65232;
	bump::String my_str(my_short);
	EXPECT_STREQ("65232", my_str.c_str());

	// Check out-of-range negative case
	my_short = -220;
	my_str = bump::String(my_short);
	EXPECT_STRNE("-220", my_str.c_str());

	// Check out-of-range positive case
	my_short = 69000;
	my_str = bump::String(my_short);
	EXPECT_STRNE("220", my_str.c_str());
}

TEST_F(StringTest, testShortConstructor)
{
	// Check positive in-range case
	short my_short = 32121;
	bump::String my_str(my_short);
	EXPECT_STREQ("32121", my_str.c_str());

	// Check negative in-range case
	my_short = -29324;
	my_str = bump::String(my_short);
	EXPECT_STREQ("-29324", my_str.c_str());

	// Check out-of-range negative case
	my_short = -39465;
	my_str = bump::String(my_short);
	EXPECT_STRNE("-39465", my_str.c_str());

	// Check out-of-range positive case
	my_short = 44258;
	my_str = bump::String(my_short);
	EXPECT_STRNE("44258", my_str.c_str());
}

TEST_F(StringTest, testUnsignedIntConstructor)
{
	// Check in-range case
	unsigned int my_int = 205000;
	bump::String my_str(my_int);
	EXPECT_STREQ("205000", my_str.c_str());

	// Check out-of-range negative case
	my_int = -220;
	my_str = bump::String(my_int);
	EXPECT_STRNE("-220", my_str.c_str());

	// Check out-of-range positive case
	my_int = 5000000000;
	my_str = bump::String(my_int);
	EXPECT_STRNE("5000000000", my_str.c_str());
}

TEST_F(StringTest, testIntConstructor)
{
	// Check positive in-range case
	int my_int = 214748364;
	bump::String my_str(my_int);
	EXPECT_STREQ("214748364", my_str.c_str());

	// Check negative in-range case
	my_int = -214748364;
	my_str = bump::String(my_int);
	EXPECT_STREQ("-214748364", my_str.c_str());

	// Check out-of-range negative case
	my_int = -3000000000;
	my_str = bump::String(my_int);
	EXPECT_STRNE("-3000000000", my_str.c_str());

	// Check out-of-range positive case
	my_int = 3000000000;
	my_str = bump::String(my_int);
	EXPECT_STRNE("3000000000", my_str.c_str());
}
	
TEST_F(StringTest, testUnsignedLongConstructor)
{
	// Check in-range case
	unsigned long my_long = 205000;
	bump::String my_str(my_long);
	EXPECT_STREQ("205000", my_str.c_str());

	// Check out-of-range negative case
	my_long = -220;
	my_str = bump::String(my_long);
	EXPECT_STRNE("-220", my_str.c_str());
}

TEST_F(StringTest, testLongConstructor)
{
	// Check positive in-range case
	long my_long = 214748364000;
	bump::String my_str(my_long);
	EXPECT_STREQ("214748364000", my_str.c_str());
	
	// Check negative in-range case
	my_long = -214748364000;
	my_str = bump::String(my_long);
	EXPECT_STREQ("-214748364000", my_str.c_str());
}

TEST_F(StringTest, testFloatConstructor)
{
	//========================================================
	//                Default decimal places
	//========================================================

	// Positive values
	float my_float = 3;
	bump::String my_str(my_float);
	EXPECT_STREQ("3.000", my_str.c_str());

	my_float = 2569891;
	my_str = bump::String(my_float);
	EXPECT_STREQ("2569891.000", my_str.c_str());

	my_float = 232.23456;
	my_str = bump::String(my_float);
	EXPECT_STREQ("232.235", my_str.c_str());

	// Negative values
	my_float = -42569;
	my_str = bump::String(my_float);
	EXPECT_STREQ("-42569.000", my_str.c_str());

	my_float = -39.64589;
	my_str = bump::String(my_float);
	EXPECT_STREQ("-39.646", my_str.c_str());

	//========================================================
	//               Customized decimal places
	//========================================================

	// Make sure we properly handle zero decimal places
	my_float = 121.98734;
	my_str = bump::String(my_float, 0);
	EXPECT_STREQ("122", my_str.c_str());

	// Negative rounding
	my_float = -4200.599963;
	my_str = bump::String(my_float, 4);
	EXPECT_STREQ("-4200.6001", my_str.c_str());

	// Positive rounding
	my_float = 9.3215648;
	my_str = bump::String(my_float, 2);
	EXPECT_STREQ("9.32", my_str.c_str());
}

TEST_F(StringTest, testDoubleConstructor)
{
	//========================================================
	//                Default decimal places
	//========================================================
	
	// Positive values
	double my_double = 3;
	bump::String my_str(my_double);
	EXPECT_STREQ("3.000", my_str.c_str());
	
	my_double = 2569891;
	my_str = bump::String(my_double);
	EXPECT_STREQ("2569891.000", my_str.c_str());
	
	my_double = 232.23456;
	my_str = bump::String(my_double);
	EXPECT_STREQ("232.235", my_str.c_str());
	
	// Negative values
	my_double = -42569;
	my_str = bump::String(my_double);
	EXPECT_STREQ("-42569.000", my_str.c_str());
	
	my_double = -39.64589;
	my_str = bump::String(my_double);
	EXPECT_STREQ("-39.646", my_str.c_str());
	
	//========================================================
	//               Customized decimal places
	//========================================================
	
	// Make sure we properly handle zero decimal places
	my_double = 121.98734;
	my_str = bump::String(my_double, 0);
	EXPECT_STREQ("122", my_str.c_str());
	
	// Negative rounding
	my_double = -4200.599963;
	my_str = bump::String(my_double, 4);
	EXPECT_STREQ("-4200.6000", my_str.c_str());
	
	// Positive rounding
	my_double = 9.3215648;
	my_str = bump::String(my_double, 2);
	EXPECT_STREQ("9.32", my_str.c_str());
}

TEST_F(StringTest, testBoolConstructor)
{
	// True tests
	bump::String my_str(true);
	EXPECT_STREQ("true", my_str.c_str());
	my_str = bump::String((bool)1);
	EXPECT_STREQ("true", my_str.c_str());

	// False test
	my_str = bump::String(false);
	EXPECT_STREQ("false", my_str.c_str());
	my_str = bump::String((bool)0);
	EXPECT_STREQ("false", my_str.c_str());
}

}   // End of bumpTest namespace
