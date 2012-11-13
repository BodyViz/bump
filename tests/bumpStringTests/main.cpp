//
//	main.cpp
//	Bump
//
//	Created by Christian Noon on 11/12/12.
//	Copyright (c) 2011 Christian Noon. All rights reserved.
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
 * - EXPECT_FALSE (condition)							 = condition is true
 * - EXPECT_TRUE  (condition)							 = condition is false
 *
 * - EXPECT_EQ	  (expected, actual)					 = expected == actual
 * - EXPECT_NE	  (val1, val2)							 = val1 != val2
 * - EXPECT_LT	  (val1, val2)							 = val1 < val2
 * - EXPECT_LE	  (val1, val2)							 = val1 <= val2
 * - EXPECT_GT	  (val1, val2)							 = val1 > val2
 * - EXPECT_GE	  (val1, val2)							 = val1 >= val2
 *
 * - EXPECT_STREQ (expected.c_str(), actual.c_str())	 = expected == actual
 * - EXPECT_STRNE (expected.c_str(), actual.c_str())	 = expected != actual
 * - EXPECT_STRCASEEQ (expected.c_str(), actual.c_str()) = expected == actual (ignoring case)
 * - EXPECT_STRCASENE (expected.c_str(), actual.c_str()) = expected != actual (ignoring case)
 *
 * - EXPECT_FLOAT_EQ (expected, actual)					 = expected almost equal to actual
 * - EXPECT_DOUBLE_EQ (expected, actual)				 = expected almost equal to actual
 * - EXPECT_NEAR (val1, val2, abs_error)				 = difference between val1 and val2 doesn't exceed abs_error
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
	//				  Default decimal places
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
	//				 Customized decimal places
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
	//				  Default decimal places
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

TEST_F(StringTest, testAppendString)
{
	// Normal append
	bump::String str1("string 1");
	bump::String str2(" and string 2");
	str1.append(str2);
	EXPECT_STREQ("string 1 and string 2", str1.c_str());

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

	// Test outside the bounds (should throw a std::exception)
	EXPECT_THROW(str.at(-1), std::exception);
	EXPECT_THROW(str.at(6), std::exception);
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

TEST_F(StringTest, testEmpty)
{
	// Test regular strings
	bump::String str("example string");
	EXPECT_FALSE(str.empty());
	str = bump::String("");
	EXPECT_TRUE(str.empty());
	str = bump::String();
	EXPECT_TRUE(str.empty());

	// Test special character strings
	str = bump::String("\t\n");
	EXPECT_FALSE(str.empty());
	str = bump::String("0123456789");
	EXPECT_FALSE(str.empty());
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
	str1 = bump::String("");
	str2 = "";
	EXPECT_TRUE(str1.endsWith(str2));
	EXPECT_TRUE(str1.endsWith(str2, bump::String::CaseSensitive));
	EXPECT_TRUE(str1.endsWith(str2, bump::String::NotCaseSensitive));
}

TEST_F(StringTest, testErasePositionWidth)
{
	// Remove from the end
	bump::String str("i love programming in C++");
	str.erase(18, 7);
	EXPECT_STREQ("i love programming", str.c_str());

	// Remove from the beginning
	str.erase(0, 2);
	EXPECT_STREQ("love programming", str.c_str());

	// Remove from the middle
	str.erase(5, 3);
	EXPECT_STREQ("love gramming", str.c_str());

	// Try removing outside the bounds with invalid arguments
	EXPECT_THROW(str.erase(-1, 10), std::range_error);
	EXPECT_THROW(str.erase(-2, -20), std::range_error);
	EXPECT_THROW(str.erase(2, -30), std::range_error);

	// Try removing outside the bounds with valid arguments
	str = bump::String("i love programming");
	EXPECT_THROW(str.erase(100, 4), std::exception);
	str.erase(6, 1000);
	EXPECT_STREQ("i love", str.c_str());
}

TEST_F(StringTest, testEraseIterator)
{
	// Remove from the beginning
	bump::String str("i love programming in C++");
	bump::String::iterator iter = str.begin();
	str.erase(iter);
	EXPECT_STREQ(" love programming in C++", str.c_str());

	// Remove from the end
	iter = str.end() - 2;
	str.erase(iter);
	str.erase(iter);
	EXPECT_STREQ(" love programming in C", str.c_str());

	// Remove from the middle
	iter = str.end() - 4;
	str.erase(iter);
	str.erase(iter);
	str.erase(iter);
	EXPECT_STREQ(" love programming C", str.c_str());
}

TEST_F(StringTest, testEraseIteratorFirstAndLast)
{
	// Remove from the end
	bump::String str("i love programming in C++");
	bump::String::iterator start_iter = str.begin() + 18;
	bump::String::iterator end_iter = str.begin() + 25;
	str.erase(start_iter, end_iter);
	EXPECT_STREQ("i love programming", str.c_str());

	// Remove from the beginning
	start_iter = str.begin();
	end_iter = str.begin() + 2;
	str.erase(start_iter, end_iter);
	EXPECT_STREQ("love programming", str.c_str());

	// Remove from the middle
	start_iter = str.begin() + 5;
	end_iter = str.begin() + 8;
	str.erase(start_iter, end_iter);
	EXPECT_STREQ("love gramming", str.c_str());

	// Handle reversed iterators
	str = bump::String("i love programming in C++");
	start_iter = str.begin() + 4;
	end_iter = str.begin() + 2;
	EXPECT_THROW(str.erase(start_iter, end_iter), std::range_error);

	// Handle doubled up iterators
	start_iter = str.begin() + 2;
	end_iter = str.begin() + 2;
	str.erase(start_iter, end_iter);
	EXPECT_STREQ("i love programming in C++", str.c_str());
	start_iter = str.end();
	end_iter = str.end();
	str.erase(start_iter, end_iter);
	EXPECT_STREQ("i love programming in C++", str.c_str());
}

TEST_F(StringTest, testFill)
{
	// Default fill
	bump::String str("example string");
	str.fill("X");
	EXPECT_STREQ("XXXXXXXXXXXXXX", str.c_str());

	// Default fill with empty string
	str = "";
	str.fill("X");
	EXPECT_STREQ("", str.c_str());

	// Fill with set size
	str.fill("Z", 10);
	EXPECT_STREQ("ZZZZZZZZZZ", str.c_str());

	// Test fill with negative size (throws std::invalid_argument)
	str = "example string";
	EXPECT_THROW(str.fill("X", -4), std::invalid_argument);

	// Test fill with too many characters
	EXPECT_THROW(str.fill("XYZ", 4), std::invalid_argument);
}

TEST_F(StringTest, testIndexOfString)
{
	// Default find
	bump::String str1("a simple example string");
	bump::String str2("example");
	int index = str1.indexOf(str2);
	EXPECT_EQ(9, index);
	str2 = bump::String("try");
	index = str1.indexOf(str2);
	EXPECT_EQ(-1, index);

	// Position offset find
	str1 = bump::String("a simple example string");
	str2 = bump::String(" ");
	index = str1.indexOf(str2, 4, bump::String::CaseSensitive);
	EXPECT_EQ(8, index);
	str2 = bump::String("try");
	index = str1.indexOf(str2, 4, bump::String::CaseSensitive);
	EXPECT_EQ(-1, index);

	// Try an empty search string
	str2 = bump::String("");
	EXPECT_THROW(str1.indexOf(str2), std::invalid_argument);

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
	// Default find
	bump::String str1("a simple example string");
	const char* str2("example");
	int index = str1.indexOf(str2);
	EXPECT_EQ(9, index);
	str2 = "try";
	index = str1.indexOf(str2);
	EXPECT_EQ(-1, index);

	// Position offset find
	str1 = bump::String("a simple example string");
	str2 = " ";
	index = str1.indexOf(str2, 4, bump::String::CaseSensitive);
	EXPECT_EQ(8, index);
	str2 = "try";
	index = str1.indexOf(str2, 4, bump::String::CaseSensitive);
	EXPECT_EQ(-1, index);

	// Try an empty search string
	str2 = "";
	EXPECT_THROW(str1.indexOf(str2), std::invalid_argument);

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

}	// End of bumpTest namespace
