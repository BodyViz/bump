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
#include <bump/String.h>
#include <bump/StringSearchError.h>

// bumpTest headers
#include "../bumpTest/BaseTest.h"

namespace bumpTest {

/**
 * This is our main string testing class. The SetUp and TearDown methods are
 * executed before the test runs and after it completes. This is where we can
 * add any custom set up for each test without having to add this to "every"
 * test individually.
 */
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
}

TEST_F(StringTest, testUnsignedShortConstructor)
{
	// Check in-range case
	unsigned short my_short = 65232;
	bump::String my_str(my_short);
	EXPECT_STREQ("65232", my_str.c_str());
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
}

TEST_F(StringTest, testUnsignedIntConstructor)
{
	// Check in-range case
	unsigned int my_int = 205000;
	bump::String my_str(my_int);
	EXPECT_STREQ("205000", my_str.c_str());
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
}

TEST_F(StringTest, testUnsignedLongConstructor)
{
	// Check in-range case
	unsigned long my_long = 205000;
	bump::String my_str(my_long);
	EXPECT_STREQ("205000", my_str.c_str());
}

TEST_F(StringTest, testLongConstructor)
{
	// Check positive in-range case
	long my_long = 2147483647;
	bump::String my_str(my_long);
	EXPECT_STREQ("2147483647", my_str.c_str());

	// Check negative in-range case
	my_long = -2147483647;
	my_str = bump::String(my_long);
	EXPECT_STREQ("-2147483647", my_str.c_str());
}

TEST_F(StringTest, testLongLongConstructor)
{
	// Check positive in-range case
	long long my_long_long = 9223372036854775806;
	bump::String my_str(my_long_long);
	EXPECT_STREQ("9223372036854775806", my_str.c_str());

	// Check negative in-range case
	my_long_long = -9223372036854775806;
	my_str = bump::String(my_long_long);
	EXPECT_STREQ("-9223372036854775806", my_str.c_str());
}

TEST_F(StringTest, testUnsignedLongLongConstructor)
{
	// Check positive in-range case
	unsigned long long my_unsigned_long_long = 1844674407370955161;
	bump::String my_str(my_unsigned_long_long);
	EXPECT_STREQ("1844674407370955161", my_str.c_str());

	// Check lower in-range case
	my_unsigned_long_long = 1;
	my_str = bump::String(my_unsigned_long_long);
	EXPECT_STREQ("1", my_str.c_str());
}

TEST_F(StringTest, testFloatConstructor)
{
	//========================================================
	//				  Default decimal places
	//========================================================

	// Positive values
	float my_float = 3;
	bump::String my_str(my_float);
	EXPECT_STREQ("3", my_str.c_str());

	my_float = 2569891;
	my_str = bump::String(my_float);
	EXPECT_STREQ("2569891", my_str.c_str());

	my_float = 232.2345f;
	my_str = bump::String(my_float);
	EXPECT_STREQ("232.2345", my_str.c_str());

	// Negative values
	my_float = -42569;
	my_str = bump::String(my_float);
	EXPECT_STREQ("-42569", my_str.c_str());

	my_float = -39.64589f;
	my_str = bump::String(my_float);
	EXPECT_STREQ("-39.64589", my_str.c_str());

	//========================================================
	//				 Customized decimal places
	//========================================================

	// Make sure we properly handle zero decimal places
	my_float = 121.98734f;
	my_str = bump::String(my_float, 0);
	EXPECT_STREQ("122", my_str.c_str());

	// Negative rounding
	my_float = -4200.599963f;
	my_str = bump::String(my_float, 4);
	EXPECT_STREQ("-4200.6001", my_str.c_str());

	// Positive rounding
	my_float = 9.3215648f;
	my_str = bump::String(my_float, 2);
	EXPECT_STREQ("9.32", my_str.c_str());
}

TEST_F(StringTest, testDoubleConstructor)
{
	//========================================================
	//				  Default decimal places
	//========================================================

	// Positive values
	double my_double = 3;
	bump::String my_str(my_double);
	EXPECT_STREQ("3", my_str.c_str());

	my_double = 2569891;
	my_str = bump::String(my_double);
	EXPECT_STREQ("2569891", my_str.c_str());

	my_double = 232.23456;
	my_str = bump::String(my_double);
	EXPECT_STREQ("232.23456", my_str.c_str());

	// Negative values
	my_double = -42569;
	my_str = bump::String(my_double);
	EXPECT_STREQ("-42569", my_str.c_str());

	my_double = -39.64589;
	my_str = bump::String(my_double);
	EXPECT_STREQ("-39.64589", my_str.c_str());

	//========================================================
	//				 Customized decimal places
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

TEST_F(StringTest, testJoin)
{
	// Default cases
	bump::StringList strings;
	strings.push_back("this");
	strings.push_back("is");
	strings.push_back("an");
	strings.push_back("example");
	strings.push_back("string");
	EXPECT_STREQ("this is an example string", bump::String::join(strings, " ").c_str());
	EXPECT_STREQ("thisisanexamplestring", bump::String::join(strings, "").c_str());
	EXPECT_STREQ("this\nis\nan\nexample\nstring", bump::String::join(strings, "\n").c_str());

	// Test an empty string list
	strings = bump::StringList();
	EXPECT_STREQ("", bump::String::join(strings, "").c_str());
	EXPECT_STREQ("", bump::String::join(strings, " ").c_str());
}

TEST_F(StringTest, testAppendString)
{
	// Normal append
	bump::String str1("string 1");
	bump::String str2(" and string 2");
	str1.append(str2);
	EXPECT_STREQ("string 1 and string 2", str1.c_str());

	// Double append
	str1 = "an";
	str2 = " example";
	bump::String str3(" string");
	str1.append(str2).append(str3);
	EXPECT_STREQ("an example string", str1.c_str());

	// Empty append
	str1 = "string 1";
	str2 = "";
	str1.append(str2);
	EXPECT_STREQ("string 1", str1.c_str());

	// Append to empty string
	str1 = "";
	str2 = "string 2";
	str1.append(str2);
	EXPECT_STREQ("string 2", str1.c_str());

	// Append two empty strings
	str1 = "";
	str2 = "";
	str1.append(str2);
	EXPECT_STREQ("", str1.c_str());
}

TEST_F(StringTest, testAppendCharStar)
{
	// Normal append
	bump::String str1("string 1");
	const char* str2 = " and string 2";
	str1.append(str2);
	EXPECT_STREQ("string 1 and string 2", str1.c_str());

	// Double append
	str1 = "an";
	str1.append(" example").append(" string");
	EXPECT_STREQ("an example string", str1.c_str());

	// Empty append
	str1 = "string 1";
	str2 = "";
	str1.append(str2);
	EXPECT_STREQ("string 1", str1.c_str());

	// Append to empty string
	str1 = "";
	str2 = "string 2";
	str1.append(str2);
	EXPECT_STREQ("string 2", str1.c_str());

	// Append two empty strings
	str1 = "";
	str2 = "";
	str1.append(str2);
	EXPECT_STREQ("", str1.c_str());
}

TEST_F(StringTest, testArg1)
{
	// Default usage
	bump::String str("Processing File: %1");
	EXPECT_STREQ("Processing File: test.txt", str.arg("test.txt").c_str());
	str = "Processing File: %1 %1";
	EXPECT_STREQ("Processing File: test.txt test.txt", str.arg("test.txt").c_str());
	str = "Processing File: %1 %2 %1";
	EXPECT_STREQ("Processing File: test.txt %2 test.txt", str.arg("test.txt").c_str());

	// Stacked usage
	str = "Processing Files: %1, %2, %3";
	EXPECT_STREQ("Processing Files: test1.txt, test2.txt, test3.txt", str.arg("test1.txt").arg("test2.txt").arg("test3.txt").c_str());
	str = "Processing Files: %1, %2, %1";
	EXPECT_STREQ("Processing Files: test1.txt, test2.txt, test1.txt", str.arg("test1.txt").arg("test2.txt").c_str());

	// Missing %i character
	str = "Processing File:";
	EXPECT_THROW(str.arg("test.txt"), bump::StringSearchError);
}

TEST_F(StringTest, testArg2)
{
	// Default usage
	bump::String str("Processing Files: %1 and %2");
	EXPECT_STREQ("Processing Files: test1.txt and test2.txt", str.arg("test1.txt", "test2.txt").c_str());
	str = "Processing File: %1 of %2";
	EXPECT_STREQ("Processing File: 1 of 10", str.arg(1, 10).c_str());

	// Reversed usage
	str = "Processing File: %2 of %1";
	EXPECT_STREQ("Processing File: 10 of 1", str.arg(1, 10).c_str());

	// Stacked usage
	str = "Processing File %1 of %2: %3";
	EXPECT_STREQ("Processing File 1 of 10: test.txt", str.arg(1, 10).arg("test.txt").c_str());

	// Missing %i character
	str = "Processing File:";
	EXPECT_THROW(str.arg(1, 2), bump::StringSearchError);
}

TEST_F(StringTest, testArg3)
{
	// Default usage
	bump::String str("%1, %2 and %3");
	EXPECT_STREQ("1, 0.987 and test", str.arg(1, 0.987, "test").c_str());
	str = "Processing File %1 of %2: %3";
	EXPECT_STREQ("Processing File 1 of 10: test.txt", str.arg(1, 10, "test.txt").c_str());

	// Reversed usage
	str = "Processing File %2 of %1: %3";
	EXPECT_STREQ("Processing File 10 of 1: test.txt", str.arg(1, 10, "test.txt").c_str());

	// Stacked usage
	str = "%1, %2, %3, %4, %5 and %6";
	EXPECT_STREQ("0.1, 0.2, 0.3, 0.4, 0.5 and 0.6", str.arg(0.1, 0.2, 0.3).arg(0.4, 0.5).arg(0.6).c_str());

	// Missing %i character
	str = "Processing File:";
	EXPECT_THROW(str.arg(1, 2, 3), bump::StringSearchError);
}

TEST_F(StringTest, testArg4)
{
	// Default usage
	bump::String str("%1, %2, %3 and %4");
	EXPECT_STREQ("1, 0.987, 29 and test", str.arg(1, 0.987, 29, "test").c_str());

	// Reversed usage
	str = "%2, %4, %1 and %3";
	EXPECT_STREQ("1, 0.987, 29 and test", str.arg(29, 1, "test", 0.987).c_str());

	// Stacked usage
	str = "%1, %2, %3, %4, %5, %6, %7, %8, %9 and %10";
	str = str.arg(0.1, 0.2, 0.3, 0.4).arg(0.5, 0.6, 0.7).arg(0.8, 0.9).arg(bump::String(1.0, 1));
	EXPECT_STREQ("0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 and 1.0", str.c_str());

	// Missing %i character
	str = "Processing File:";
	EXPECT_THROW(str.arg(1, 2, 3, 4), bump::StringSearchError);
}

TEST_F(StringTest, testArg5)
{
	// Default usage
	bump::String str("%1, %2, %3, %4 and %5");
	EXPECT_STREQ("1, 0.987, 29, test and true", str.arg(1, 0.987, 29, "test", true).c_str());

	// Reversed usage
	str = "%2, %5, %4, %1 and %3";
	EXPECT_STREQ("true, 0.987, test, 29 and 1", str.arg(29, true, 1, "test", 0.987).c_str());

	// Stacked usage
	str = "%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14 and %15";
	str = str.arg(0.1, 0.2, 0.3, 0.4, 0.5).arg(0.6, 0.7, 0.8, 0.9).arg(bump::String(1.0, 1), 1.1, 1.2).arg(1.3, 1.4).arg(1.5);
	EXPECT_STREQ("0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4 and 1.5", str.c_str());

	// Missing %i character
	str = "Processing File:";
	EXPECT_THROW(str.arg(1, 2, 3, 4, 5), bump::StringSearchError);
}

TEST_F(StringTest, testArg6)
{
	// Default usage
	bump::String str("%1, %2, %3, %4, %5 and %6");
	EXPECT_STREQ("1, 0.987, 29, test, true and false", str.arg(1, 0.987, 29, "test", true, false).c_str());

	// Reversed usage
	str = "%6, %2, %5, %4, %1, %3";
	EXPECT_STREQ("0.987, 29, test, 1, false, true", str.arg(false, 29, true, 1, "test", 0.987).c_str());

	// Stacked usage
	str = "%1, %2, %3, %4, %5, %6, %7";
	EXPECT_STREQ("0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7", str.arg(0.1, 0.2, 0.3, 0.4, 0.5, 0.6).arg(0.7).c_str());

	// Missing %i character
	str = "Processing File:";
	EXPECT_THROW(str.arg(1, 2, 3, 4, 5, 6), bump::StringSearchError);
}

TEST_F(StringTest, testArg7)
{
	// Default usage
	bump::String str("%1, %2, %3, %4, %5, %6 and %7");
	str = str.arg(1, 0.987, 29, "test", true, false, bump::String(1.000, 3));
	EXPECT_STREQ("1, 0.987, 29, test, true, false and 1.000", str.c_str());

	// Reversed usage
	str = "%6, %2, %5, %4, %1, %3, %7";
	EXPECT_STREQ("0.987, 29, test, 1, false, true, 10", str.arg(false, 29, true, 1, "test", 0.987, 10).c_str());

	// Stacked usage
	str = "%1, %2, %3, %4, %5, %6, %7, %8";
	EXPECT_STREQ("0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8", str.arg(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7).arg(0.8).c_str());

	// Missing %i character
	str = "Processing File:";
	EXPECT_THROW(str.arg(1, 2, 3, 4, 5, 6, 7), bump::StringSearchError);
}

TEST_F(StringTest, testArg8)
{
	// Default usage
	bump::String str("%1, %2, %3, %4, %5, %6, %7 and %8");
	str = str.arg(1, 0.987, 29, "test", true, false, bump::String(1.000, 3), "");
	EXPECT_STREQ("1, 0.987, 29, test, true, false, 1.000 and ", str.c_str());

	// Reversed usage
	str = "%6, %2, %5, %8, %4, %1, %3, %7";
	EXPECT_STREQ("0.987, 29, test, , 1, false, true, 10", str.arg(false, 29, true, 1, "test", 0.987, 10, "").c_str());

	// Stacked usage
	str = "%1, %2, %3, %4, %5, %6, %7, %8, %9";
	EXPECT_STREQ("0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9", str.arg(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8).arg(0.9).c_str());

	// Missing %i character
	str = "Processing File:";
	EXPECT_THROW(str.arg(1, 2, 3, 4, 5, 6, 7, 8), bump::StringSearchError);
}

TEST_F(StringTest, testArg9)
{
	// Default usage
	bump::String str("%1, %2, %3, %4, %5, %6, %7, %8 and %9");
	str = str.arg(1, 0.987, 29, "test", true, false, bump::String(1.000, 3), "", 19.087);
	EXPECT_STREQ("1, 0.987, 29, test, true, false, 1.000,  and 19.087", str.c_str());

	// Reversed usage
	str = "%6, %2, %5, %8, %4, %1, %9, %3, %7";
	EXPECT_STREQ("0.987, 29, test, , 1, false, 19.087, true, 10", str.arg(false, 29, true, 1, "test", 0.987, 10, "", 19.087).c_str());

	// Stacked usage
	str = "%1, %2, %3, %4, %5, %6, %7, %8, %9, %10";
	str = str.arg(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9).arg(bump::String(1.0, 1));
	EXPECT_STREQ("0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0", str.c_str());

	// Missing %i character
	str = "Processing File:";
	EXPECT_THROW(str.arg(1, 2, 3, 4, 5, 6, 7, 8, 9), bump::StringSearchError);
}

TEST_F(StringTest, testAt)
{
	// Test all the characters
	bump::String str = "string";
	char character = str.at(0);
	EXPECT_EQ('s', character);
	character = str.at(1);
	EXPECT_EQ('t', character);
	character = str.at(2);
	EXPECT_EQ('r', character);
	character = str.at(3);
	EXPECT_EQ('i', character);
	character = str.at(4);
	EXPECT_EQ('n', character);
	character = str.at(5);
	EXPECT_EQ('g', character);

	// Test outside the bounds (throws bump::OutOfRangeError exception)
	EXPECT_THROW(str.at(-1), bump::OutOfRangeError);
	EXPECT_THROW(str.at(6), bump::OutOfRangeError);
}

TEST_F(StringTest, testCStr)
{
	// Test full strings
	bump::String str("My string");
	EXPECT_STREQ("My string", str.c_str());

	// Test strings with special characters
	str = bump::String("this\thas\ttabs");
	EXPECT_STREQ("this\thas\ttabs", str.c_str());

	// Test strings with whitespace
	str = bump::String("   where is the whitespace   ");
	EXPECT_STREQ("   where is the whitespace   ", str.c_str());
}

TEST_F(StringTest, testCapitalize)
{
	// Test a regular lowercase string
	bump::String str("example string");
	str.capitalize();
	EXPECT_STREQ("Example string", str.c_str());

	// Test an empty string
	str = bump::String("");
	str.capitalize();
	EXPECT_STREQ("", str.c_str());

	// Test a special character string
	str = bump::String("\t\n\t");
	str.capitalize();
	EXPECT_STREQ("\t\n\t", str.c_str());
}

TEST_F(StringTest, testChop)
{
	// Test regular usage cases
	bump::String str("example string");
	str.chop(1);
	EXPECT_STREQ("example strin", str.c_str());
	str.chop(0);
	EXPECT_STREQ("example strin", str.c_str());
	str.chop(6);
	EXPECT_STREQ("example", str.c_str());
	str.chop(400);
	EXPECT_STREQ("", str.c_str());
}

TEST_F(StringTest, testClear)
{
	// Test a regular string
	bump::String str("example string");
	EXPECT_EQ(14, str.length());
	str.clear();
	EXPECT_STREQ("", str.c_str());
	EXPECT_EQ(0, str.length());

	// Test an empty string
	str = bump::String("");
	EXPECT_EQ(0, str.length());
	str.clear();
	EXPECT_STREQ("", str.c_str());
	EXPECT_EQ(0, str.length());

	// Test a default string
	str = bump::String();
	EXPECT_EQ(0, str.length());
	str.clear();
	EXPECT_STREQ("", str.c_str());
	EXPECT_EQ(0, str.length());
}

TEST_F(StringTest, testCompareString)
{
	// Test regular strings
	bump::String str1("str1");
	bump::String str2("str2");
	EXPECT_FALSE(str1.compare(str2));
	str2 = bump::String("str1");
	EXPECT_TRUE(str1.compare(str2));

	// Test different capitalization
	str1 = bump::String("Str1");
	str2 = bump::String("str1");
	EXPECT_FALSE(str1.compare(str2));
	str2 = bump::String("Str1");
	EXPECT_TRUE(str1.compare(str2));

	// Test some non-case sensitive cases
	str1 = "Str1";
	str2 = "str1";
	EXPECT_FALSE(str1.compare(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.compare(str2, bump::String::NotCaseSensitive));

	// Test empty strings
	str1 = bump::String("");
	str2 = bump::String();
	EXPECT_TRUE(str1.compare(str2));

	// Test special character strings
	str1 = bump::String("\t\n\t");
	str2 = bump::String("\t\n\t");
	EXPECT_TRUE(str1.compare(str2));
}

TEST_F(StringTest, testCompareCString)
{
	// Test regular strings
	bump::String str1("str1");
	const char* str2 = "str2";
	EXPECT_FALSE(str1.compare(str2));
	str2 = "str1";
	EXPECT_TRUE(str1.compare(str2));

	// Test different capitalization
	str1 = bump::String("Str1");
	str2 = "str1";
	EXPECT_FALSE(str1.compare(str2));
	str2 = "Str1";
	EXPECT_TRUE(str1.compare(str2));

	// Test some non-case sensitive cases
	str1 = "Str1";
	str2 = "str1";
	EXPECT_FALSE(str1.compare(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.compare(str2, bump::String::NotCaseSensitive));

	// Test empty strings
	str1 = bump::String("");
	str2 = "";
	EXPECT_TRUE(str1.compare(str2));

	// Test special character strings
	str1 = bump::String("\t\n\t");
	str2 = "\t\n\t";
	EXPECT_TRUE(str1.compare(str2));
}

TEST_F(StringTest, testContainsString)
{
	// Test regular strings using the default case sensitive search
	bump::String str1("this is an example string");
	bump::String str2("Example");
	EXPECT_FALSE(str1.contains(str2));
	str2 = bump::String("example");
	EXPECT_TRUE(str1.contains(str2));
	str2 = bump::String("10 examples");
	EXPECT_FALSE(str1.compare(str2));

	// Test some non-case sensitive searches
	str1 = bump::String("This ExaMple StRiNg...");
	str2 = bump::String("EXAMPLE string...");
	EXPECT_FALSE(str1.contains(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.contains(str2, bump::String::NotCaseSensitive));

	// Test with numbers and special characters
	str1 = bump::String("This\thas\nfunky\t\tstuff");
	str2 = bump::String("\nfunky\t");
	EXPECT_TRUE(str1.contains(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.contains(str2, bump::String::NotCaseSensitive));
}

TEST_F(StringTest, testContainsCString)
{
	// Test regular strings using the default case sensitive search
	bump::String str1("this is an example string");
	const char* str2 = "Example";
	EXPECT_FALSE(str1.contains(str2));
	str2 = "example";
	EXPECT_TRUE(str1.contains(str2));
	str2 = "10 examples";
	EXPECT_FALSE(str1.compare(str2));

	// Test some non-case sensitive searches
	str1 = bump::String("This ExaMple StRiNg...");
	str2 = "EXAMPLE string...";
	EXPECT_FALSE(str1.contains(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.contains(str2, bump::String::NotCaseSensitive));

	// Test with numbers and special characters
	str1 = bump::String("This\thas\nfunky\t\tstuff");
	str2 = "\nfunky\t";
	EXPECT_TRUE(str1.contains(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.contains(str2, bump::String::NotCaseSensitive));
}

TEST_F(StringTest, testCountString)
{
	// Test regular strings
	bump::String str1("how many different a values can I have???");
	bump::String str2("a");
	EXPECT_EQ(5, str1.count(str2));
	str2 = bump::String("???");
	EXPECT_EQ(1, str1.count(str2));
	str2 = bump::String("	");
	EXPECT_EQ(0, str1.count(str2));

	// Test empty strings
	str1 = bump::String("");
	str2 = bump::String();
	EXPECT_EQ(0, str1.count(str2));

	// Test special character strings
	str1 = bump::String("this\tcontains\tmany\ttabs");
	str2 = bump::String("\t");
	EXPECT_EQ(3, str1.count(str2));
}

TEST_F(StringTest, testCountCString)
{
	// Test regular strings
	bump::String str1("how many different a values can I have???");
	const char* str2 = "a";
	EXPECT_EQ(5, str1.count(str2));
	str2 = "???";
	EXPECT_EQ(1, str1.count(str2));
	str2 = "   ";
	EXPECT_EQ(0, str1.count(str2));

	// Test empty strings
	str1 = bump::String("");
	str2 = "";
	EXPECT_EQ(0, str1.count(str2));

	// Test special character strings
	str1 = bump::String("this\tcontains\tmany\ttabs");
	str2 = "\t";
	EXPECT_EQ(3, str1.count(str2));
}

TEST_F(StringTest, testData)
{
	// Test regular strings
	bump::String str("test");
	const char* cstr = "test";
	unsigned int length = str.length();
	EXPECT_EQ(0, memcmp(cstr, str.data(), length));
}

TEST_F(StringTest, testEndsWithString)
{
	// Test regular strings
	bump::String str1("DO I end with THIS???");
	bump::String str2("this???");
	EXPECT_FALSE(str1.endsWith(str2));
	EXPECT_FALSE(str1.endsWith(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.endsWith(str2, bump::String::NotCaseSensitive));

	// Test empty strings
	str1 = bump::String("");
	str2 = bump::String();
	EXPECT_TRUE(str1.endsWith(str2));
	EXPECT_TRUE(str1.endsWith(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.endsWith(str2, bump::String::NotCaseSensitive));
}

TEST_F(StringTest, testEndsWithCString)
{
	// Test regular strings
	bump::String str1("DO I end with THIS???");
	const char* str2 = "this???";
	EXPECT_FALSE(str1.endsWith(str2));
	EXPECT_FALSE(str1.endsWith(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.endsWith(str2, bump::String::NotCaseSensitive));

	// Test empty strings
	str1 = "";
	str2 = "";
	EXPECT_TRUE(str1.endsWith(str2));
	EXPECT_TRUE(str1.endsWith(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.endsWith(str2, bump::String::NotCaseSensitive));
}

TEST_F(StringTest, testFill)
{
	// Default fill
	bump::String str("example string");
	str.fill("X");
	EXPECT_STREQ("XXXXXXXXXXXXXX", str.c_str());

	// Double fill
	str = "example string";
	str.fill("X").fill("Y");
	EXPECT_STREQ("YYYYYYYYYYYYYY", str.c_str());

	// Default fill with empty string
	str = "";
	str.fill("X");
	EXPECT_STREQ("", str.c_str());

	// Fill with set size
	str.fill("Z", 10);
	EXPECT_STREQ("ZZZZZZZZZZ", str.c_str());

	// Test fill with negative size (throws bump::InvalidArgumentError exception)
	str = "example string";
	EXPECT_THROW(str.fill("X", -4), bump::InvalidArgumentError);

	// Test fill with too many characters
	EXPECT_THROW(str.fill("XYZ", 4), bump::InvalidArgumentError);
}

TEST_F(StringTest, testIndexOfString)
{
	// Default search
	bump::String str1("a simple example string");
	bump::String str2("example");
	int index = str1.indexOf(str2);
	EXPECT_EQ(9, index);
	str2 = bump::String("try");
	index = str1.indexOf(str2);
	EXPECT_EQ(-1, index);

	// Position offset search
	str1 = bump::String("a simple example string");
	str2 = bump::String(" ");
	index = str1.indexOf(str2, 4, bump::String::CaseSensitive);
	EXPECT_EQ(8, index);
	str2 = bump::String("try");
	index = str1.indexOf(str2, 4, bump::String::CaseSensitive);
	EXPECT_EQ(-1, index);

	// Try an empty search string
	str2 = bump::String("");
	EXPECT_THROW(str1.indexOf(str2), bump::InvalidArgumentError);

	// Try a position less than 0
	str2 = bump::String("example");
	index = str1.indexOf(str2, -10);
	EXPECT_EQ(-1, index);

	// Try a position greather than the size of str1
	str2 = bump::String("example");
	index = str1.indexOf(str2, 100);
	EXPECT_EQ(-1, index);

	// Try some different non-case sensitive cases
	str1 = bump::String("A Simple Example String");
	str2 = bump::String("simple");
	index = str1.indexOf(str2, 0, bump::String::NotCaseSensitive);
	EXPECT_EQ(2, index);
	str2 = bump::String("try");
	index = str1.indexOf(str2, 0, bump::String::NotCaseSensitive);
	EXPECT_EQ(-1, index);
}

TEST_F(StringTest, testIndexOfCString)
{
	// Default search
	bump::String str1("a simple example string");
	const char* str2("example");
	int index = str1.indexOf(str2);
	EXPECT_EQ(9, index);
	str2 = "try";
	index = str1.indexOf(str2);
	EXPECT_EQ(-1, index);

	// Position offset search
	str1 = bump::String("a simple example string");
	str2 = " ";
	index = str1.indexOf(str2, 4, bump::String::CaseSensitive);
	EXPECT_EQ(8, index);
	str2 = "try";
	index = str1.indexOf(str2, 4, bump::String::CaseSensitive);
	EXPECT_EQ(-1, index);

	// Try an empty search string
	str2 = "";
	EXPECT_THROW(str1.indexOf(str2), bump::InvalidArgumentError);

	// Try a position less than 0
	str2 = "example";
	index = str1.indexOf(str2, -10);
	EXPECT_EQ(-1, index);

	// Try a position greather than the size of str1
	str2 = "example";
	index = str1.indexOf(str2, 100);
	EXPECT_EQ(-1, index);

	// Try some different non-case sensitive cases
	str1 = bump::String("A Simple Example String");
	str2 = "simple";
	index = str1.indexOf(str2, 0, bump::String::NotCaseSensitive);
	EXPECT_EQ(2, index);
	str2 = "try";
	index = str1.indexOf(str2, 0, bump::String::NotCaseSensitive);
	EXPECT_EQ(-1, index);
}

TEST_F(StringTest, testInsertString)
{
	// Mid insert
	bump::String str1("a simple string");
	bump::String str2("example ");
	str1.insert(str2, 9);
	EXPECT_STREQ("a simple example string", str1.c_str());

	// Beginning insert
	str1 = "example string";
	str2 = "an ";
	str1.insert(str2, 0);
	EXPECT_STREQ("an example string", str1.c_str());

	// End insert
	str1 = "an example";
	str2 = " string";
	str1.insert(str2, 10);
	EXPECT_STREQ("an example string", str1.c_str());

	// Double insert
	str1 = "an";
	str2 = " example";
	bump::String str3(" string");
	str1.insert(str2, 2).insert(str3, 10);
	EXPECT_STREQ("an example string", str1.c_str());

	// Try to insert an empty string
	str1 = "an example";
	str2 = "";
	EXPECT_THROW(str1.insert(str2, 10), bump::InvalidArgumentError);

	// Try to insert a string in a negative position
	str2 = " string";
	EXPECT_THROW(str1.insert(str2, -1), bump::OutOfRangeError);

	// Try to insert a string past the string bounds
	EXPECT_THROW(str1.insert(str2, 100), bump::OutOfRangeError);
}

TEST_F(StringTest, testInsertCString)
{
	// Mid insert
	bump::String str1("a simple string");
	const char* str2("example ");
	str1.insert(str2, 9);
	EXPECT_STREQ("a simple example string", str1.c_str());

	// Beginning insert
	str1 = "example string";
	str2 = "an ";
	str1.insert(str2, 0);
	EXPECT_STREQ("an example string", str1.c_str());

	// End insert
	str1 = "an example";
	str2 = " string";
	str1.insert(str2, 10);
	EXPECT_STREQ("an example string", str1.c_str());

	// Double insert
	str1 = "an";
	str1.insert(" example", 2).insert(" string", 10);
	EXPECT_STREQ("an example string", str1.c_str());

	// Try to insert an empty string
	str1 = "an example";
	str2 = "";
	EXPECT_THROW(str1.insert(str2, 10), bump::InvalidArgumentError);

	// Try to insert a string in a negative position
	str2 = " string";
	EXPECT_THROW(str1.insert(str2, -1), bump::OutOfRangeError);

	// Try to insert a string past the string bounds
	EXPECT_THROW(str1.insert(str2, 100), bump::OutOfRangeError);
}

TEST_F(StringTest, testIsEmpty)
{
	// Test regular strings
	bump::String str("example string");
	EXPECT_FALSE(str.isEmpty());
	str = bump::String("");
	EXPECT_TRUE(str.isEmpty());
	str = bump::String();
	EXPECT_TRUE(str.isEmpty());

	// Test special character strings
	str = bump::String("\t\n");
	EXPECT_FALSE(str.isEmpty());
	str = bump::String("0123456789");
	EXPECT_FALSE(str.isEmpty());
}

TEST_F(StringTest, testIsNumber)
{
	// Test some valid numbers
	bump::String str("3");
	EXPECT_TRUE(str.isNumber());
	str = "3.14";
	EXPECT_TRUE(str.isNumber());
	str = "-4000.38483904";
	EXPECT_TRUE(str.isNumber());
	str = "2999999938384893";
	EXPECT_TRUE(str.isNumber());
	str = "14E2";
	EXPECT_TRUE(str.isNumber());

	// Test some invalid numbers
	str = "3.1.3";
	EXPECT_FALSE(str.isNumber());
	str = "Was 21";
	EXPECT_FALSE(str.isNumber());
	str = "21C4D3";
	EXPECT_FALSE(str.isNumber());
}

TEST_F(StringTest, testLastIndexOfString)
{
	// Default reverse search
	bump::String str1("a simple example string");
	bump::String str2("example");
	int index = str1.lastIndexOf(str2);
	EXPECT_EQ(9, index);
	str2 = "a";
	index = str1.lastIndexOf(str2);
	EXPECT_EQ(11, index);
	str2 = "try";
	index = str1.lastIndexOf(str2);
	EXPECT_EQ(-1, index);

	// Position offset reverse search
	str1 = "a simple example string";
	str2 = " ";
	index = str1.lastIndexOf(str2, 12, bump::String::CaseSensitive);
	EXPECT_EQ(8, index);
	str2 = "try";
	index = str1.lastIndexOf(str2, 4, bump::String::CaseSensitive);
	EXPECT_EQ(-1, index);

	// Try an empty search string
	str2 = "";
	EXPECT_THROW(str1.lastIndexOf(str2), bump::InvalidArgumentError);

	// Try a position less than 0
	str2 = "example";
	index = str1.lastIndexOf(str2, -10);
	EXPECT_EQ(-1, index);

	// Try a position greather than the size of str1
	str2 = "example";
	index = str1.lastIndexOf(str2, 100);
	EXPECT_EQ(-1, index);

	// Try some different non-case sensitive cases
	str1 = "A Simple Example String";
	str2 = "simple";
	index = str1.lastIndexOf(str2, -1, bump::String::NotCaseSensitive);
	EXPECT_EQ(2, index);
	str2 = "try";
	index = str1.lastIndexOf(str2, -1, bump::String::NotCaseSensitive);
	EXPECT_EQ(-1, index);
}

TEST_F(StringTest, testLastIndexOfCString)
{
	// Default reverse search
	bump::String str1("a simple example string");
	const char* str2("example");
	int index = str1.lastIndexOf(str2);
	EXPECT_EQ(9, index);
	str2 = "a";
	index = str1.lastIndexOf(str2);
	EXPECT_EQ(11, index);
	str2 = "try";
	index = str1.lastIndexOf(str2);
	EXPECT_EQ(-1, index);

	// Position offset reverse search
	str1 = "a simple example string";
	str2 = " ";
	index = str1.lastIndexOf(str2, 12, bump::String::CaseSensitive);
	EXPECT_EQ(8, index);
	str2 = "try";
	index = str1.lastIndexOf(str2, 4, bump::String::CaseSensitive);
	EXPECT_EQ(-1, index);

	// Try an empty search string
	str2 = "";
	EXPECT_THROW(str1.lastIndexOf(str2), bump::InvalidArgumentError);

	// Try a position less than 0
	str2 = "example";
	index = str1.lastIndexOf(str2, -10);
	EXPECT_EQ(-1, index);

	// Try a position greather than the size of str1
	str2 = "example";
	index = str1.lastIndexOf(str2, 100);
	EXPECT_EQ(-1, index);

	// Try some different non-case sensitive cases
	str1 = "A Simple Example String";
	str2 = "simple";
	index = str1.lastIndexOf(str2, -1, bump::String::NotCaseSensitive);
	EXPECT_EQ(2, index);
	str2 = "try";
	index = str1.lastIndexOf(str2, -1, bump::String::NotCaseSensitive);
	EXPECT_EQ(-1, index);
}

TEST_F(StringTest, testLeft)
{
	// Regular usage tests
	bump::String str("a simple example string");
	EXPECT_STREQ("a simple", str.left(8).c_str());
	EXPECT_STREQ("a", str.left(1).c_str());
	EXPECT_STREQ("a ", str.left(2).c_str());
	EXPECT_STREQ("a simple example string", str.left(str.length()).c_str());

	// Empty string tests
	str = "";
	EXPECT_THROW(str.left(1), bump::OutOfRangeError);

	// Out-of-bounds tests
	EXPECT_THROW(str.left(0), bump::OutOfRangeError);
	EXPECT_THROW(str.left(-2), bump::OutOfRangeError);
	EXPECT_THROW(str.left(str.length() + 1), bump::OutOfRangeError);
}

TEST_F(StringTest, testLength)
{
	// Regular usage tests
	bump::String str("example string");
	EXPECT_EQ(14, str.length());

	// Empty string tests
	str = "";
	EXPECT_EQ(0, str.length());
	str = bump::String();
	EXPECT_EQ(0, str.length());
}

TEST_F(StringTest, testPrependString)
{
	// Normal prepend
	bump::String str1("string 1");
	bump::String str2("string 2 and ");
	str1.prepend(str2);
	EXPECT_STREQ("string 2 and string 1", str1.c_str());

	// Double prepend
	str1 = "string";
	str2 = "example ";
	bump::String str3("an ");
	str1.prepend(str2).prepend(str3);
	EXPECT_STREQ("an example string", str1.c_str());

	// Empty prepend
	str1 = "string 1";
	str2 = "";
	str1.prepend(str2);
	EXPECT_STREQ("string 1", str1.c_str());

	// Prepend to empty string
	str1 = "";
	str2 = "string 2";
	str1.prepend(str2);
	EXPECT_STREQ("string 2", str1.c_str());

	// Prepend two empty strings
	str1 = "";
	str2 = "";
	str1.prepend(str2);
	EXPECT_STREQ("", str1.c_str());
}

TEST_F(StringTest, testPrependCString)
{
	// Normal prepend
	bump::String str1("string 1");
	const char* str2("string 2 and ");
	str1.prepend(str2);
	EXPECT_STREQ("string 2 and string 1", str1.c_str());

	// Double prepend
	str1 = "string";
	str2 = "example ";
	const char* str3("an ");
	str1.prepend(str2).prepend(str3);
	EXPECT_STREQ("an example string", str1.c_str());

	// Empty prepend
	str1 = "string 1";
	str2 = "";
	str1.prepend(str2);
	EXPECT_STREQ("string 1", str1.c_str());

	// Prepend to empty string
	str1 = "";
	str2 = "string 2";
	str1.prepend(str2);
	EXPECT_STREQ("string 2", str1.c_str());

	// Prepend two empty strings
	str1 = "";
	str2 = "";
	str1.prepend(str2);
	EXPECT_STREQ("", str1.c_str());
}

TEST_F(StringTest, testRepeated)
{
	// Regular usage
	bump::String str("xyz");
	EXPECT_STREQ("", str.repeated(0).c_str());
	EXPECT_STREQ("xyz", str.repeated(1).c_str());
	EXPECT_STREQ("xyzxyz", str.repeated(2).c_str());
	EXPECT_STREQ("xyzxyzxyz", str.repeated(3).c_str());
	EXPECT_STREQ("xyzxyzxyzxyz", str.repeated(4).c_str());

	// Special characters
	str = "Ab\t\n";
	EXPECT_STREQ("", str.repeated(0).c_str());
	EXPECT_STREQ("Ab\t\n", str.repeated(1).c_str());
	EXPECT_STREQ("Ab\t\nAb\t\n", str.repeated(2).c_str());
	EXPECT_STREQ("Ab\t\nAb\t\nAb\t\n", str.repeated(3).c_str());
	EXPECT_STREQ("Ab\t\nAb\t\nAb\t\nAb\t\n", str.repeated(4).c_str());
}

TEST_F(StringTest, testRemovePositionWidth)
{
	// Remove from the end
	bump::String str("i love programming in C++");
	str.remove(18, 7);
	EXPECT_STREQ("i love programming", str.c_str());

	// Remove from the beginning
	str.remove(0, 2);
	EXPECT_STREQ("love programming", str.c_str());

	// Remove from the middle
	str.remove(5, 3);
	EXPECT_STREQ("love gramming", str.c_str());

	// Double stack a remove
	str = "i love programming in C++";
	str.remove(18, 7).remove(0, 2);
	EXPECT_STREQ("love programming", str.c_str());

	// Try removing outside the bounds with invalid arguments
	EXPECT_THROW(str.remove(-1, 10), bump::OutOfRangeError);
	EXPECT_THROW(str.remove(-2, -20), bump::OutOfRangeError);
	EXPECT_THROW(str.remove(200, -30), bump::OutOfRangeError);
	EXPECT_THROW(str.remove(2, -30), bump::InvalidArgumentError);

	// Try removing outside the bounds with valid arguments
	str = bump::String("i love programming");
	EXPECT_THROW(str.remove(19, 0), bump::OutOfRangeError);
	str.remove(6, 1000);
	EXPECT_STREQ("i love", str.c_str());
}

TEST_F(StringTest, testRemoveString)
{
	// Default removes
	bump::String str1("i love programming in C++");
	bump::String str2(" in C++");
	str1.remove(str2);
	EXPECT_STREQ("i love programming", str1.c_str());
	str1 = "XaXaXaX";
	str2 = "a";
	str1.remove(str2);
	EXPECT_STREQ("XXXX", str1.c_str());

	// Remove special characters
	str1 = "this\tis\thow\twe\tuse\ttabs\n\n";
	str2 = "\t";
	bump::String str3("\n");
	str1.remove(str2).remove(str3);
	EXPECT_STREQ("thisishowweusetabs", str1.c_str());

	// Try removing something from an empty string
	str1 = "";
	str2 = "test";
	str1.remove(str2);
	EXPECT_STREQ("", str1.c_str());

	// Try removing nothing from a string
	str1 = "example string";
	str2 = "";
	EXPECT_THROW(str1.remove(str2), bump::InvalidArgumentError);

	// Test non-case sensitive cases
	str1 = "I Love Programming In C++";
	str2 = " in c++";
	str1.remove(str2);
	EXPECT_STREQ("I Love Programming In C++", str1.c_str());
	str1.remove(str2, bump::String::NotCaseSensitive);
	EXPECT_STREQ("I Love Programming", str1.c_str());
	str1 = "XaxAXAx";
	str2 = "a";
	str3 = "x";
	str1.remove(str2).remove(str3);
	EXPECT_STREQ("XAXA", str1.c_str());
	str1.remove(str2, bump::String::NotCaseSensitive).remove(str3, bump::String::NotCaseSensitive);
	EXPECT_STREQ("", str1.c_str());
}

TEST_F(StringTest, testRemoveCString)
{
	// Default removes
	bump::String str1("i love programming in C++");
	const char* str2(" in C++");
	str1.remove(str2);
	EXPECT_STREQ("i love programming", str1.c_str());
	str1 = "XaXaXaX";
	str2 = "a";
	str1.remove(str2);
	EXPECT_STREQ("XXXX", str1.c_str());

	// Remove special characters
	str1 = "this\tis\thow\twe\tuse\ttabs\n\n";
	str2 = "\t";
	const char* str3("\n");
	str1.remove(str2).remove(str3);
	EXPECT_STREQ("thisishowweusetabs", str1.c_str());

	// Try removing something from an empty string
	str1 = "";
	str2 = "test";
	str1.remove(str2);
	EXPECT_STREQ("", str1.c_str());

	// Try removing nothing from a string
	str1 = "example string";
	str2 = "";
	EXPECT_THROW(str1.remove(str2), bump::InvalidArgumentError);

	// Test non-case sensitive cases
	str1 = "I Love Programming In C++";
	str2 = " in c++";
	str1.remove(str2);
	EXPECT_STREQ("I Love Programming In C++", str1.c_str());
	str1.remove(str2, bump::String::NotCaseSensitive);
	EXPECT_STREQ("I Love Programming", str1.c_str());
	str1 = "XaxAXAx";
	str2 = "a";
	str3 = "x";
	str1.remove(str2).remove(str3);
	EXPECT_STREQ("XAXA", str1.c_str());
	str1.remove(str2, bump::String::NotCaseSensitive).remove(str3, bump::String::NotCaseSensitive);
	EXPECT_STREQ("", str1.c_str());
}

TEST_F(StringTest, testReplaceString)
{
	// Default beginning replace
	bump::String str1("programming in C++");
	bump::String str2("i love ");
	str1.replace(0, 0, str2);
	EXPECT_STREQ("i love programming in C++", str1.c_str());

	// Default mid replace
	str1 = "i love programming in C++";
	str2 = "coding";
	str1.replace(7, 11, str2);
	EXPECT_STREQ("i love coding in C++", str1.c_str());

	// Default end replace
	str1 = "i love programming in C++";
	str2 = "Python";
	str1.replace(22, 3, str2);
	EXPECT_STREQ("i love programming in Python", str1.c_str());

	// Double stack replace
	str1 = "i love programming in C++";
	str2 = "coding";
	bump::String str3("Python");
	str1.replace(7, 11, str2).replace(17, 3, str3);
	EXPECT_STREQ("i love coding in Python", str1.c_str());

	// Test the out-of-bounds cases
	str1 = "i love programming in C++";
	str2 = "Python";
	EXPECT_THROW(str1.replace(-10, 3, str2), bump::OutOfRangeError);
	EXPECT_THROW(str1.replace(100, 3, str2), bump::OutOfRangeError);
	EXPECT_THROW(str1.replace(2, -10, str2), bump::InvalidArgumentError);
	str1 = "i love programming in C++";
	str1.replace(2, 100, str2);
	EXPECT_STREQ("i Python", str1.c_str());

	// Test the empty string cases
	str1 = "";
	str2 = "test";
	str1.replace(0, 0, str2);
	EXPECT_STREQ("test", str1.c_str());
	str1 = "test";
	str2 = "";
	str1.replace(0, 0, str2);
	EXPECT_STREQ("test", str1.c_str());
}

TEST_F(StringTest, testReplaceCString)
{
	// Default beginning replace
	bump::String str1("programming in C++");
	const char* str2("i love ");
	str1.replace(0, 0, str2);
	EXPECT_STREQ("i love programming in C++", str1.c_str());

	// Default mid replace
	str1 = "i love programming in C++";
	str2 = "coding";
	str1.replace(7, 11, str2);
	EXPECT_STREQ("i love coding in C++", str1.c_str());

	// Default end replace
	str1 = "i love programming in C++";
	str2 = "Python";
	str1.replace(22, 3, str2);
	EXPECT_STREQ("i love programming in Python", str1.c_str());

	// Double stack replace
	str1 = "i love programming in C++";
	str2 = "coding";
	const char* str3("Python");
	str1.replace(7, 11, str2).replace(17, 3, str3);
	EXPECT_STREQ("i love coding in Python", str1.c_str());

	// Test the out-of-bounds cases
	str1 = "i love programming in C++";
	str2 = "Python";
	EXPECT_THROW(str1.replace(-10, 3, str2), bump::OutOfRangeError);
	EXPECT_THROW(str1.replace(100, 3, str2), bump::OutOfRangeError);
	EXPECT_THROW(str1.replace(2, -10, str2), bump::InvalidArgumentError);
	str1 = "i love programming in C++";
	str1.replace(2, 100, str2);
	EXPECT_STREQ("i Python", str1.c_str());

	// Test the empty string cases
	str1 = "";
	str2 = "test";
	str1.replace(0, 0, str2);
	EXPECT_STREQ("test", str1.c_str());
	str1 = "test";
	str2 = "";
	str1.replace(0, 0, str2);
	EXPECT_STREQ("test", str1.c_str());
}

TEST_F(StringTest, testReplaceBeforeAfterString)
{
	// Default replace cases
	bump::String str("i love programming in C++");
	bump::String before("programming");
	bump::String after("coding");
	str.replace(before, after);
	EXPECT_STREQ("i love coding in C++", str.c_str());
	str = "XaXaXaX";
	before = "a";
	after = "r";
	str.replace(before, after);
	EXPECT_STREQ("XrXrXrX", str.c_str());

	// Double stack replace
	str = "I love programming in C++";
	before = "programming";
	after = "coding";
	bump::String before2("C++");
	bump::String after2("Python");
	str.replace(before, after).replace(before2, after2);
	EXPECT_STREQ("I love coding in Python", str.c_str());

	// Test the empty string cases
	str = "";
	before = "test";
	after = "tested";
	str.replace(before, after);
	EXPECT_STREQ("", str.c_str());
	str = "I Love Programming";
	before = "";
	after = "To Program";
	EXPECT_THROW(str.replace(before, after), bump::InvalidArgumentError);
	str = "I Love Programming";
	before = " Programming";
	after = "";
	str.replace(before, after);
	EXPECT_STREQ("I Love", str.c_str());

	// Test the non-case sensitive cases
	str = "I Love To Program";
	before = "to ";
	after = "";
	str.replace(before, after);
	EXPECT_STREQ("I Love To Program", str.c_str());
	str.replace(before, after, bump::String::NotCaseSensitive);
	EXPECT_STREQ("I Love Program", str.c_str());
}

TEST_F(StringTest, testReplaceBeforeAfterCString)
{
	// Default replace cases
	bump::String str("i love programming in C++");
	const char* before("programming");
	const char* after("coding");
	str.replace(before, after);
	EXPECT_STREQ("i love coding in C++", str.c_str());
	str = "XaXaXaX";
	before = "a";
	after = "r";
	str.replace(before, after);
	EXPECT_STREQ("XrXrXrX", str.c_str());

	// Double stack replace
	str = "I love programming in C++";
	before = "programming";
	after = "coding";
	const char* before2("C++");
	const char* after2("Python");
	str.replace(before, after).replace(before2, after2);
	EXPECT_STREQ("I love coding in Python", str.c_str());

	// Test the empty string cases
	str = "";
	before = "test";
	after = "tested";
	str.replace(before, after);
	EXPECT_STREQ("", str.c_str());
	str = "I Love Programming";
	before = "";
	after = "To Program";
	EXPECT_THROW(str.replace(before, after), bump::InvalidArgumentError);
	str = "I Love Programming";
	before = " Programming";
	after = "";
	str.replace(before, after);
	EXPECT_STREQ("I Love", str.c_str());

	// Test the non-case sensitive cases
	str = "I Love To Program";
	before = "to ";
	after = "";
	str.replace(before, after);
	EXPECT_STREQ("I Love To Program", str.c_str());
	str.replace(before, after, bump::String::NotCaseSensitive);
	EXPECT_STREQ("I Love Program", str.c_str());
}

TEST_F(StringTest, testRight)
{
	// Regular usage tests
	bump::String str("a simple example string");
	EXPECT_STREQ("string", str.right(6).c_str());
	EXPECT_STREQ("g", str.right(1).c_str());
	EXPECT_STREQ("ng", str.right(2).c_str());
	EXPECT_STREQ("a simple example string", str.right(str.length()).c_str());

	// Empty string tests
	str = "";
	EXPECT_THROW(str.right(1), bump::OutOfRangeError);

	// Out-of-bounds tests
	EXPECT_THROW(str.right(0), bump::OutOfRangeError);
	EXPECT_THROW(str.right(-2), bump::OutOfRangeError);
	EXPECT_THROW(str.right(str.length() + 1), bump::OutOfRangeError);
}

TEST_F(StringTest, testSection)
{
	// Regular usage tests
	bump::String str("a simple example string");
	EXPECT_STREQ("simple example", str.section(2, 14).c_str());
	EXPECT_STREQ("a ", str.section(0, 2).c_str());
	EXPECT_STREQ("simple example string", str.section(2, 100).c_str());
	EXPECT_STREQ("a simple example string", str.section(0, str.length()).c_str());

	// Empty string tests
	str = "";
	EXPECT_THROW(str.section(1), bump::OutOfRangeError);

	// Out-of-bounds tests
	str = "a simple example string";
	EXPECT_THROW(str.section(-2, 2), bump::OutOfRangeError);
	EXPECT_THROW(str.section(2, 0), bump::InvalidArgumentError);
}

TEST_F(StringTest, testSplit)
{
	// Regular usage tests
	bump::String str("Split By Space");
	bump::String separator(" ");
	bump::StringList result = str.split(separator);
	EXPECT_STREQ("Split", result.at(0).c_str());
	EXPECT_STREQ("By", result.at(1).c_str());
	EXPECT_STREQ("Space", result.at(2).c_str());

	// Special characters
	str = "C:\\libs\\bump";
	separator = "\\";
	result = str.split(separator);
	EXPECT_STREQ("C:", result.at(0).c_str());
	EXPECT_STREQ("libs", result.at(1).c_str());
	EXPECT_STREQ("bump", result.at(2).c_str());
	str = "I\tHave\tTabs";
	separator = "\t";
	result = str.split(separator);
	EXPECT_STREQ("I", result.at(0).c_str());
	EXPECT_STREQ("Have", result.at(1).c_str());
	EXPECT_STREQ("Tabs", result.at(2).c_str());

	// Empty string test
	str = "";
	separator = " ";
	result = str.split(separator);
	EXPECT_STREQ("", result.at(0).c_str());

	// Big separators
	str = "I amXyZThis isXyZAnd Again";
	separator = "XyZ";
	result = str.split(separator);
	EXPECT_STREQ("I am", result.at(0).c_str());
	EXPECT_STREQ("This is", result.at(1).c_str());
	EXPECT_STREQ("And Again", result.at(2).c_str());
}

TEST_F(StringTest, testStartsWithString)
{
	// Test regular strings
	bump::String str1("DO I start with THIS???");
	bump::String str2("do i");
	EXPECT_FALSE(str1.startsWith(str2));
	EXPECT_FALSE(str1.startsWith(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.startsWith(str2, bump::String::NotCaseSensitive));

	// Test empty strings
	str1 = "";
	str2 = bump::String();
	EXPECT_TRUE(str1.startsWith(str2));
	EXPECT_TRUE(str1.startsWith(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.startsWith(str2, bump::String::NotCaseSensitive));
}

TEST_F(StringTest, testStartsWithCString)
{
	// Test regular strings
	bump::String str1("DO I start with THIS???");
	const char* str2("do i");
	EXPECT_FALSE(str1.startsWith(str2));
	EXPECT_FALSE(str1.startsWith(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.startsWith(str2, bump::String::NotCaseSensitive));

	// Test empty strings
	str1 = "";
	str2 = "";
	EXPECT_TRUE(str1.startsWith(str2));
	EXPECT_TRUE(str1.startsWith(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.startsWith(str2, bump::String::NotCaseSensitive));
}

TEST_F(StringTest, testTitle)
{
	// Regular usage tests
	bump::String str("my absolutely awesome book title");
	EXPECT_STREQ("My Absolutely Awesome Book Title", str.title().c_str());
	str = "MY ABSOLUTELY AWESOME BOOK TITLE";
	EXPECT_STREQ("My Absolutely Awesome Book Title", str.title().c_str());

	// Empty string test
	str = "";
	EXPECT_STREQ("", str.title().c_str());
}

TEST_F(StringTest, testToBool)
{
	// Regular usage tests
	bump::String str(true);
	EXPECT_TRUE(str.toBool());
	str = "true";
	EXPECT_TRUE(str.toBool());
	str = "True";
	EXPECT_TRUE(str.toBool());
	str = "TRUE";
	EXPECT_TRUE(str.toBool());
	str = false;
	EXPECT_FALSE(str.toBool());
	str = "false";
	EXPECT_FALSE(str.toBool());
	str = "False";
	EXPECT_FALSE(str.toBool());
	str = "FALSE";
	EXPECT_FALSE(str.toBool());

	// Invalid usage tests
	str = "27";
	EXPECT_THROW(str.toBool(), bump::TypeCastError);
	str = "test";
	EXPECT_THROW(str.toBool(), bump::TypeCastError);
	str = "39.8";
	EXPECT_THROW(str.toBool(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toBool(), bump::TypeCastError);
}

TEST_F(StringTest, testToDouble)
{
	// Regular usage tests
	bump::String str(9.0987, 4);
	EXPECT_DOUBLE_EQ(9.0987, str.toDouble());
	str = bump::String(10.0, 4);
	EXPECT_DOUBLE_EQ(10.0, str.toDouble());
	str = bump::String(0.56897845, 6);
	EXPECT_DOUBLE_EQ(0.568978, str.toDouble());
	str = bump::String(20);
	EXPECT_DOUBLE_EQ(20, str.toDouble());
	str = bump::String(-90.895623, 2);
	EXPECT_DOUBLE_EQ(-90.90, str.toDouble());

	// Invalid usage tests
	str = "test";
	EXPECT_THROW(str.toDouble(), bump::TypeCastError);
	str = true;
	EXPECT_THROW(str.toDouble(), bump::TypeCastError);
	str = false;
	EXPECT_THROW(str.toDouble(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toDouble(), bump::TypeCastError);
}

TEST_F(StringTest, testToFloat)
{
	// Regular usage tests
	bump::String str(9.0987, 4);
	EXPECT_FLOAT_EQ(9.0987f, str.toFloat());
	str = bump::String(10.0, 4);
	EXPECT_FLOAT_EQ(10.0, str.toFloat());
	str = bump::String(0.56897845, 6);
	EXPECT_FLOAT_EQ(0.568978f, str.toFloat());
	str = bump::String(20);
	EXPECT_FLOAT_EQ(20, str.toFloat());
	str = bump::String(-90.895623, 2);
	EXPECT_FLOAT_EQ(-90.90f, str.toFloat());

	// Invalid usage tests
	str = "test";
	EXPECT_THROW(str.toFloat(), bump::TypeCastError);
	str = true;
	EXPECT_THROW(str.toFloat(), bump::TypeCastError);
	str = false;
	EXPECT_THROW(str.toFloat(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toFloat(), bump::TypeCastError);
}

TEST_F(StringTest, testToInt)
{
	// Regular usage tests
	bump::String str(27);
	EXPECT_EQ(27, str.toInt());
	str = -9909;
	EXPECT_EQ(-9909, str.toInt());

	// Invalid usage tests
	str = 400.980;
	EXPECT_THROW(str.toInt(), bump::TypeCastError);
	str = "test";
	EXPECT_THROW(str.toInt(), bump::TypeCastError);
	str = true;
	EXPECT_THROW(str.toInt(), bump::TypeCastError);
	str = false;
	EXPECT_THROW(str.toInt(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toInt(), bump::TypeCastError);
}

TEST_F(StringTest, testToLong)
{
	// Regular usage tests
	bump::String str(2147483647);
	EXPECT_EQ(2147483647, str.toLong());
	str = -2147483647;
	EXPECT_EQ(-2147483647, str.toLong());

	// Invalid usage tests
	str = 400.980;
	EXPECT_THROW(str.toLong(), bump::TypeCastError);
	str = "test";
	EXPECT_THROW(str.toLong(), bump::TypeCastError);
	str = true;
	EXPECT_THROW(str.toLong(), bump::TypeCastError);
	str = false;
	EXPECT_THROW(str.toLong(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toLong(), bump::TypeCastError);
}

TEST_F(StringTest, testToLongLong)
{
	// Regular usage tests
	bump::String str(9223372036854775806);
	EXPECT_EQ(9223372036854775806, str.toLongLong());
	str = -9223372036854775807;
	EXPECT_EQ(-9223372036854775807, str.toLongLong());

	// Invalid usage tests
	str = 400.980;
	EXPECT_THROW(str.toLongLong(), bump::TypeCastError);
	str = "test";
	EXPECT_THROW(str.toLongLong(), bump::TypeCastError);
	str = true;
	EXPECT_THROW(str.toLongLong(), bump::TypeCastError);
	str = false;
	EXPECT_THROW(str.toLongLong(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toLongLong(), bump::TypeCastError);
}

TEST_F(StringTest, testToLowerCase)
{
	// Regular usage tests
	bump::String str("Trying This Out");
	EXPECT_STREQ("trying this out", str.toLowerCase().c_str());
	str = "XAxaruXR\t\n";
	EXPECT_STREQ("xaxaruxr\t\n", str.toLowerCase().c_str());
	str = 98.985;
	EXPECT_STREQ("98.985", str.toLowerCase().c_str());
	str = "";
	EXPECT_STREQ("", str.toLowerCase().c_str());
}

TEST_F(StringTest, testToShort)
{
	// Regular usage tests
	bump::String str(27);
	EXPECT_EQ(27, str.toShort());
	str = -4587;
	EXPECT_EQ(-4587, str.toShort());

	// Invalid usage tests
	str = 400.980;
	EXPECT_THROW(str.toShort(), bump::TypeCastError);
	str = "test";
	EXPECT_THROW(str.toShort(), bump::TypeCastError);
	str = true;
	EXPECT_THROW(str.toShort(), bump::TypeCastError);
	str = false;
	EXPECT_THROW(str.toShort(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toShort(), bump::TypeCastError);
}

TEST_F(StringTest, testToStdString)
{
	// Regular usage tests
	bump::String str("Trying This Out");
	EXPECT_STREQ("Trying This Out", str.toStdString().c_str());
	str = "XAxaruXR\t\n";
	EXPECT_STREQ("XAxaruXR\t\n", str.toStdString().c_str());
	str = 98.985;
	EXPECT_STREQ("98.985", str.toStdString().c_str());
	str = "";
	EXPECT_STREQ("", str.toStdString().c_str());
}

TEST_F(StringTest, testToUInt)
{
	// Regular usage tests
	bump::String str(4294967294);
	EXPECT_EQ(4294967294, str.toUInt());
	str = 1;
	EXPECT_EQ(1, str.toUInt());

	// Invalid usage tests
	str = 400.980;
	EXPECT_THROW(str.toUInt(), bump::TypeCastError);
	str = "test";
	EXPECT_THROW(str.toUInt(), bump::TypeCastError);
	str = true;
	EXPECT_THROW(str.toUInt(), bump::TypeCastError);
	str = false;
	EXPECT_THROW(str.toUInt(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toUInt(), bump::TypeCastError);
}

TEST_F(StringTest, testToULong)
{
	// Regular usage tests
	bump::String str(4294967294);
	EXPECT_EQ(4294967294, str.toULong());
	str = 1;
	EXPECT_EQ(1, str.toULong());

	// Invalid usage tests
	str = 400.980;
	EXPECT_THROW(str.toULong(), bump::TypeCastError);
	str = "test";
	EXPECT_THROW(str.toULong(), bump::TypeCastError);
	str = true;
	EXPECT_THROW(str.toULong(), bump::TypeCastError);
	str = false;
	EXPECT_THROW(str.toULong(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toULong(), bump::TypeCastError);
}

TEST_F(StringTest, testToULongLong)
{
	// Regular usage tests
	bump::String str(1844674407370955161);
	EXPECT_EQ(1844674407370955161, str.toULongLong());
	str = 1;
	EXPECT_EQ(1, str.toULongLong());

	// Invalid usage tests
	str = 400.980;
	EXPECT_THROW(str.toULongLong(), bump::TypeCastError);
	str = "test";
	EXPECT_THROW(str.toULongLong(), bump::TypeCastError);
	str = true;
	EXPECT_THROW(str.toULongLong(), bump::TypeCastError);
	str = false;
	EXPECT_THROW(str.toULongLong(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toULongLong(), bump::TypeCastError);
}

TEST_F(StringTest, testToUpperCase)
{
	// Regular usage tests
	bump::String str("Trying This Out");
	EXPECT_STREQ("TRYING THIS OUT", str.toUpperCase().c_str());
	str = "XAxaruXR\t\n";
	EXPECT_STREQ("XAXARUXR\t\n", str.toUpperCase().c_str());
	str = 98.985;
	EXPECT_STREQ("98.985", str.toUpperCase().c_str());
	str = "";
	EXPECT_STREQ("", str.toUpperCase().c_str());
}

TEST_F(StringTest, testToUShort)
{
	// Regular usage tests
	bump::String str(65534);
	EXPECT_EQ(65534, str.toUShort());
	str = 1;
	EXPECT_EQ(1, str.toUShort());

	// Invalid usage tests
	str = 400.980;
	EXPECT_THROW(str.toUShort(), bump::TypeCastError);
	str = "test";
	EXPECT_THROW(str.toUShort(), bump::TypeCastError);
	str = true;
	EXPECT_THROW(str.toUShort(), bump::TypeCastError);
	str = false;
	EXPECT_THROW(str.toUShort(), bump::TypeCastError);
	str = "";
	EXPECT_THROW(str.toUShort(), bump::TypeCastError);
}

TEST_F(StringTest, testTrimmed)
{
	// Regular cases
	bump::String str("     1x x x x1     ");
	EXPECT_STREQ("1x x x x1", str.trimmed().c_str());
	str = " \t\n\v\f\r1x x x x1\t\n\v\f\r ";
	EXPECT_STREQ("1x x x x1", str.trimmed().c_str());

	// Empty cases
	str = "";
	EXPECT_STREQ("", str.trimmed().c_str());
}

TEST_F(StringTest, testOperatorLTLTString)
{
	// Normal append
	bump::String str1("string 1");
	bump::String str2(" and string 2");
	str1 << str2;
	EXPECT_STREQ("string 1 and string 2", str1.c_str());

	// Double append
	str1 = "an";
	str2 = " example";
	bump::String str3(" string");
	str1 << str2 << str3;
	EXPECT_STREQ("an example string", str1.c_str());

	// Empty append
	str1 = "string 1";
	str2 = "";
	str1 << str2;
	EXPECT_STREQ("string 1", str1.c_str());

	// Append to empty string
	str1 = "";
	str2 = "string 2";
	str1 << str2;
	EXPECT_STREQ("string 2", str1.c_str());

	// Append two empty strings
	str1 = "";
	str2 = "";
	str1 << str2;
	EXPECT_STREQ("", str1.c_str());
}

TEST_F(StringTest, testOperatorLTLTCString)
{
	// Normal append
	bump::String str1("string 1");
	const char* str2(" and string 2");
	str1 << str2;
	EXPECT_STREQ("string 1 and string 2", str1.c_str());

	// Double append
	str1 = "an";
	str2 = " example";
	const char* str3(" string");
	str1 << str2 << str3;
	EXPECT_STREQ("an example string", str1.c_str());

	// Empty append
	str1 = "string 1";
	str2 = "";
	str1 << str2;
	EXPECT_STREQ("string 1", str1.c_str());

	// Append to empty string
	str1 = "";
	str2 = "string 2";
	str1 << str2;
	EXPECT_STREQ("string 2", str1.c_str());

	// Append two empty strings
	str1 = "";
	str2 = "";
	str1 << str2;
	EXPECT_STREQ("", str1.c_str());
}

TEST_F(StringTest, testOperatorLTLTUnsignedChar)
{
	// Normal append
	bump::String str("example string ");
	unsigned char num1 = 0;
	str << num1;
	EXPECT_STREQ("example string 0", str.c_str());
	str = "example string ";
	num1 = 255;
	str << num1;
	EXPECT_STREQ("example string 255", str.c_str());

	// Double append
	str = "a ";
	num1 = 10;
	unsigned char num2 = 20;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a 10 and 20", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40;
	str << num1;
	EXPECT_STREQ("40", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTChar)
{
	// Normal append
	bump::String str("example string ");
	char num1 = -128;
	str << num1;
	EXPECT_STREQ("example string -128", str.c_str());
	str = "example string ";
	num1 = 127;
	str << num1;
	EXPECT_STREQ("example string 127", str.c_str());

	// Double append
	str = "a ";
	num1 = -10;
	char num2 = 20;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a -10 and 20", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40;
	str << num1;
	EXPECT_STREQ("40", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTUnsignedShort)
{
	// Normal append
	bump::String str("example string ");
	unsigned short num1 = 0;
	str << num1;
	EXPECT_STREQ("example string 0", str.c_str());
	str = "example string ";
	num1 = 65535;
	str << num1;
	EXPECT_STREQ("example string 65535", str.c_str());

	// Double append
	str = "a ";
	num1 = 10;
	unsigned short num2 = 20;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a 10 and 20", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40;
	str << num1;
	EXPECT_STREQ("40", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTShort)
{
	// Normal append
	bump::String str("example string ");
	short num1 = -32768;
	str << num1;
	EXPECT_STREQ("example string -32768", str.c_str());
	str = "example string ";
	num1 = 32767;
	str << num1;
	EXPECT_STREQ("example string 32767", str.c_str());

	// Double append
	str = "a ";
	num1 = -10;
	short num2 = 20;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a -10 and 20", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40;
	str << num1;
	EXPECT_STREQ("40", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTUnsignedInt)
{
	// Normal append
	bump::String str("example string ");
	unsigned int num1 = 0;
	str << num1;
	EXPECT_STREQ("example string 0", str.c_str());
	str = "example string ";
	num1 = 2147483647;
	str << num1;
	EXPECT_STREQ("example string 2147483647", str.c_str());

	// Double append
	str = "a ";
	num1 = 10;
	unsigned int num2 = 20;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a 10 and 20", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40;
	str << num1;
	EXPECT_STREQ("40", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTInt)
{
	// Normal append
	bump::String str("example string ");
	int num1 = -2147483647;
	str << num1;
	EXPECT_STREQ("example string -2147483647", str.c_str());
	str = "example string ";
	num1 = 2147483647;
	str << num1;
	EXPECT_STREQ("example string 2147483647", str.c_str());

	// Double append
	str = "a ";
	num1 = -10;
	int num2 = 20;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a -10 and 20", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40;
	str << num1;
	EXPECT_STREQ("40", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTUnsignedLong)
{
	// Normal append
	bump::String str("example string ");
	unsigned long num1 = 0;
	str << num1;
	EXPECT_STREQ("example string 0", str.c_str());
	str = "example string ";
	num1 = 2147483647;
	str << num1;
	EXPECT_STREQ("example string 2147483647", str.c_str());

	// Double append
	str = "a ";
	num1 = 10;
	unsigned long num2 = 20;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a 10 and 20", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40;
	str << num1;
	EXPECT_STREQ("40", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTLong)
{
	// Normal append
	bump::String str("example string ");
	long num1 = -2147483647;
	str << num1;
	EXPECT_STREQ("example string -2147483647", str.c_str());
	str = "example string ";
	num1 = 2147483647;
	str << num1;
	EXPECT_STREQ("example string 2147483647", str.c_str());

	// Double append
	str = "a ";
	num1 = -10;
	long num2 = 20;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a -10 and 20", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40;
	str << num1;
	EXPECT_STREQ("40", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTUnsignedLongLong)
{
	// Normal append
	bump::String str("example string ");
	unsigned long long num1 = 0;
	str << num1;
	EXPECT_STREQ("example string 0", str.c_str());
	str = "example string ";
	num1 = 1844674407370955161;
	str << num1;
	EXPECT_STREQ("example string 1844674407370955161", str.c_str());

	// Double append
	str = "a ";
	num1 = 10;
	unsigned long long num2 = 20;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a 10 and 20", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40;
	str << num1;
	EXPECT_STREQ("40", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTLongLong)
{
	// Normal append
	bump::String str("example string ");
	long long num1 = -922337203685477580;
	str << num1;
	EXPECT_STREQ("example string -922337203685477580", str.c_str());
	str = "example string ";
	num1 = 922337203685477580;
	str << num1;
	EXPECT_STREQ("example string 922337203685477580", str.c_str());

	// Double append
	str = "a ";
	num1 = -10;
	long long num2 = 20;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a -10 and 20", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40;
	str << num1;
	EXPECT_STREQ("40", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTFloat)
{
	// Normal append
	bump::String str("example string ");
	float num1 = -92.3015f;
	str << num1;
	EXPECT_STREQ("example string -92.3015", str.c_str());
	str = "example string ";
	num1 = 4068.983f;
	str << num1;
	EXPECT_STREQ("example string 4068.983", str.c_str());

	// Double append
	str = "a ";
	num1 = -10.01001f;
	float num2 = 20.2385f;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a -10.01001 and 20.2385", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40.1f;
	str << num1;
	EXPECT_STREQ("40.1", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTDouble)
{
	// Normal append
	bump::String str("example string ");
	double num1 = -92.30145;
	str << num1;
	EXPECT_STREQ("example string -92.30145", str.c_str());
	str = "example string ";
	num1 = 40068.98304;
	str << num1;
	EXPECT_STREQ("example string 40068.98304", str.c_str());

	// Double append
	str = "a ";
	num1 = -10.01;
	double num2 = 20.238473;
	str << num1 << " and " << num2;
	EXPECT_STREQ("a -10.01 and 20.238473", str.c_str());

	// Append to empty string
	str = "";
	num1 = 40.1;
	str << num1;
	EXPECT_STREQ("40.1", str.c_str());
}

TEST_F(StringTest, testOperatorLTLTBool)
{
	// Normal append
	bump::String str("example string ");
	bool bool1 = true;
	str << bool1;
	EXPECT_STREQ("example string true", str.c_str());
	str = "example string ";
	bool1 = false;
	str << bool1;
	EXPECT_STREQ("example string false", str.c_str());

	// Double append
	str = "a ";
	bool1 = false;
	bool bool2 = false;
	str << bool1 << " and " << bool2;
	EXPECT_STREQ("a false and false", str.c_str());

	// Append to empty string
	str = "";
	bool1 = true;
	str << bool1;
	EXPECT_STREQ("true", str.c_str());
}

}	// End of bumpTest namespace
