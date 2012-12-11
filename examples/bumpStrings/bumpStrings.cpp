//
//  bumpStrings.cpp
//  Bump
//
//  Created by Christian Noon on 11/16/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// C++ headers
#include <iomanip>

// Bump headers
#include <bump/String.h>

// Forward declarations
void creationAndCasting();
void formatting();
void comparison();
void manipulation();
void extraction();
void capitalization();
void findReplace();
void joinSplit();

/**
 * This example demonstrates how to use the bump::String class.
 *
 * It is broken up into the following sections to make it easier to find out about a
 * particular functionality.
 *
 *		Section 1 - Creation and Casting
 *		Section 2 - Formatting (arg, << operator)
 *		Section 3 - Comparison (compare, startsWith, endsWith)
 *		Section 4 - Manipulation (prepend, append, remove, chop, trimmed)
 *		Section 5 - Extraction (section, left, right)
 *		Section 6 - Capitalization (toLowerCase, toUpperCase, capitalize, title)
 *		Section 7 - Find/Replace (indexOf, lastIndexOf, replace)
 *		Section 8 - Join/Split
 */
int main(int argc, char **argv)
{
	// Run each example
	creationAndCasting();
	formatting();
	comparison();
	manipulation();
	extraction();
	capitalization();
	findReplace();
	joinSplit();

    return 0;
}

void creationAndCasting()
{
	std::cout << "\n============================ CREATION AND CASTING ============================" << std::endl;

	// A bump::String can be created just like an std::string
	std::cout << "\nConstructed like std::strings:" << std::endl;
	bump::String str1("string 1");
	bump::String str2 = "string 2";
	std::cout << "- " << str1 << " and " << str2 << std::endl;

	// A bump::String can also be created with numbers
	std::cout << "\nCreated with numbers:" << std::endl;
	char value_char = -20;
	unsigned char value_uchar = 254;
	short value_short = -3265;
	unsigned short value_ushort = 31258;
	int value_int = -90258;
	unsigned int value_uint = 1282058;
	long value_long = -200258;
	unsigned long value_ulong = 960200;
	long long value_longlong = -1000000000;
	unsigned long long value_ulonglong = 2000000000;
	bump::String str_char(value_char);
	bump::String str_uchar(value_uchar);
	bump::String str_short(value_short);
	bump::String str_ushort(value_ushort);
	bump::String str_int(value_int);
	bump::String str_uint(value_uint);
	bump::String str_long(value_long);
	bump::String str_ulong(value_ulong);
	bump::String str_longlong(value_longlong);
	bump::String str_ulonglong(value_ulonglong);
	std::cout << "- Char:\n\t- Value:  " << (int)value_char << "\n\t- String: " << str_char << std::endl;
	std::cout << "- Unsigned Char:\n\t- Value:  " << (int)value_uchar << "\n\t- String: " << str_uchar << std::endl;
	std::cout << "- Short:\n\t- Value:  " << value_short << "\n\t- String: " << str_short << std::endl;
	std::cout << "- Unsigned Short:\n\t- Value:  " << value_ushort << "\n\t- String: " << str_ushort << std::endl;
	std::cout << "- Int:\n\t- Value:  " << value_int << "\n\t- String: " << str_int << std::endl;
	std::cout << "- Unsigned Int:\n\t- Value:  " << value_uint << "\n\t- String: " << str_uint << std::endl;
	std::cout << "- Long:\n\t- Value:  " << value_long << "\n\t- String: " << str_long << std::endl;
	std::cout << "- Unsigned Long:\n\t- Value:  " << value_ulong << "\n\t- String: " << str_ulong << std::endl;
	std::cout << "- Long Long:\n\t- Value:  " << value_longlong << "\n\t- String: " << str_longlong << std::endl;
	std::cout << "- Unsigned Long Long:\n\t- Value:  " << value_ulonglong << "\n\t- String: " << str_ulonglong << std::endl;

	// These strings can even be created with floats and doubles. The precision in
	// the string will be the same as passed into the function.
	std::cout << "\nCreated with floats and doubles:" << std::endl;
	float value_float = 3.0000;
	double value_double = 97.008930487;
	bump::String str_float(value_float);
	bump::String str_double(value_double);
	std::cout << "- Float:\n\t- Value:  " << value_float << "\n\t- String: " << str_float << std::endl;
	std::cout << "- Double:\n\t- Value:  " << std::setprecision(11) << value_double << "\n\t- String: " << str_double << std::endl;

	// You can even specify the precision for the floats and doubles. The bump::String class will
	// handle all the rounding properly as you can see below.
	std::cout << "\nSpecify float and double precision:" << std::endl;
	value_float = 3.1456;
	value_double = 97.008930487;
	bump::String str_float_precise(value_float, 2);
	bump::String str_double_precise(value_double, 4);
	std::cout << "- Float:\n\t- Value:  " << value_float << "\n\t- String: " << str_float_precise << " Precision: " << 2 << std::endl;
	std::cout << "- Double:\n\t- Value:  " << std::setprecision(11) << value_double << "\n\t- String: " << str_double_precise << " Precision: 4" << std::endl;

	// How about booleans?
	std::cout << "\nCreated from booleans:" << std::endl;
	bool value_false = false;
	bool value_true = true;
	bump::String str_false(value_false);
	bump::String str_true(value_true);
	std::cout << "- Bool:\n\t- Value:  " << value_false << "\n\t- String: " << str_false << std::endl;
	std::cout << "- Bool:\n\t- Value:  " << value_true << "\n\t- String: " << str_true << std::endl;

	// Now let's cast all these strings back to values (except char and uchar)
	std::cout << "\nConverted back to values:" << std::endl;
	short converted_short = str_short.toShort();
	unsigned short converted_ushort = str_ushort.toUShort();
	int converted_int = str_int.toInt();
	unsigned int converted_uint = str_uint.toUInt();
	long converted_long = str_long.toLong();
	unsigned long converted_ulong = str_ulong.toULong();
	long long converted_longlong = str_longlong.toLongLong();
	unsigned long long converted_ulonglong = str_ulonglong.toULongLong();
	float converted_float = str_float.toFloat();
	double converted_double = str_double.toDouble();
	std::cout << "- Short:\n\t- String: " << str_short << "\n\t- Value:  " << converted_short << std::endl;
	std::cout << "- Unsigned Short:\n\t- String: " << str_ushort << "\n\t- Value:  " << converted_ushort << std::endl;
	std::cout << "- Int:\n\t- String: " << str_int << "\n\t- Value:  " << converted_int << std::endl;
	std::cout << "- Unsigned Int:\n\t- String: " << str_uint << "\n\t- Value:  " << converted_uint << std::endl;
	std::cout << "- Long:\n\t- String: " << str_long << "\n\t- Value:  " << converted_long << std::endl;
	std::cout << "- Unsigned Long:\n\t- String: " << str_ulong << "\n\t- Value:  " << converted_ulong << std::endl;
	std::cout << "- Long Long:\n\t- String: " << str_longlong << "\n\t- Value:  " << converted_longlong << std::endl;
	std::cout << "- Unsigned Long Long:\n\t- String: " << str_ulonglong << "\n\t- Value:  " << converted_ulonglong << std::endl;
	std::cout << "- Float:\n\t- String: " << str_float << "\n\t- Value:  " << converted_float << std::endl;
	std::cout << "- Double:\n\t- String: " << str_double << "\n\t- Value:  " << converted_double << std::endl;
}

void formatting()
{
	std::cout << "\n============================ FORMATTING ============================" << std::endl;

	// You can use the << operator to concatenate strings and c-strings together
	std::cout << "\nConcatenating strings together with << operator:" << std::endl;
	bump::String str("bump");
	str << bump::String(" strings ") << "are " << "really cool!!!";
	std::cout << "- Concatenated String: " << str << std::endl;

	// You can even use the << operator to concatenate numbers and booleans into the string
	std::cout << "\nConcatenating strings, numbers and booleans together with << operator:" << std::endl;
	str = "Processing";
	str << " File " << 2 << " of " << 10 << " at " << 1.24 << " MB/s";
	std::cout << "- Concatenated String: " << str << std::endl;

	// You can also use the arg methods to format strings. The way this works is that
	// you specify a marker between 1 and 99 (i.e. %1-%99) and the arg method will replace
	// the lowest marker (i.e. %5) with the given argument.
	std::cout << "\nConcatenating strings together with arg method:" << std::endl;
	bump::String orig_str = "bump strings %1 %2 %3";
	str = orig_str.arg("are");
	str = str.arg("really");
	str = str.arg("cool!!!");
	std::cout << "- Original String:     " << orig_str << std::endl;
	std::cout << "- Concatenated String: " << str << std::endl;

	// You can also stack the arg methods to make it easier
	std::cout << "\nStacking multiple arg methods:" << std::endl;
	orig_str = "bump strings %1 %2 %3";
	str = orig_str.arg("are").arg("really").arg("cool!!!");
	std::cout << "- Original String:     " << orig_str << std::endl;
	std::cout << "- Replaced String:     " << str << std::endl;

	// There are also methods that support up to nine arguments for replacement
	std::cout << "\nMultiple parameter arg methods:" << std::endl;
	orig_str = "bump strings %1 %2 %3";
	str = orig_str.arg("are", "really", "cool!!!");
	std::cout << "- Original String:     " << orig_str << std::endl;
	std::cout << "- Replaced String:     " << str << std::endl;

	// Wouldn't it be really cool if the arg method also supported numbers and booleans?
	std::cout << "\nStrings, numbers and booleans as arg method parameters:" << std::endl;
	orig_str = "Processing Files %1 of %2 at %3 %4";
	str = orig_str.arg(2, 10, 1.24, "MBs");
	std::cout << "- Original String:     " << orig_str << std::endl;
	std::cout << "- Replaced String:     " << str << std::endl;

	// You can even repeat markers if you would like...they all get replaced
	std::cout << "\nRepeating markers in arg methods:" << std::endl;
	orig_str = "%1 %2 %1 %2 %3 %4 %5 %6";
	str = orig_str.arg(20.9987, true, "\"awesome\"", -174354, bump::String("\"why not\""), std::string("\"works\""));
	std::cout << "- Original String:     " << orig_str << std::endl;
	std::cout << "- Replaced String:     " << str << std::endl;
}

void comparison()
{
	std::cout << "\n============================ COMPARISON ============================" << std::endl;

	// Comparing if two strings are equal using the == operator
	std::cout << "\nComparing if two strings are equal with the == operator:" << std::endl;
	bump::String str1("string 1");
	bump::String str2("string 1");
	bump::String are_equal = str1 == str2;
	std::cout << "- \"" << str1 << "\" == \"" << str2 << "\" : " << are_equal << std::endl;
	str1 = "string 1";
	str2 = "string 2";
	are_equal = str1 == str2;
	std::cout << "- \"" << str1 << "\" == \"" << str2 << "\" : " << are_equal << std::endl;
	str1 = "String 1";
	str2 = "string 1";
	are_equal = str1 == str2;
	std::cout << "- \"" << str1 << "\" == \"" << str2 << "\" : " << are_equal << std::endl;

	// The == operator is nice when the comparison is case sensitive, but what if we don't
	// actually care about case? This is where the bump::String::compare method comes in.
	std::cout << "\nComparing if two strings are equal with the compare method:" << std::endl;
	str1 = "string 1";
	str2 = "string 1";
	are_equal = str1.compare(str2);
	std::cout << "- \"" << str1 << "\" == \"" << str2 << "\" : " << are_equal << std::endl;
	str1 = "string 1";
	str2 = "string 2";
	are_equal = str1.compare(str2, bump::String::CaseSensitive);
	std::cout << "- \"" << str1 << "\" == \"" << str2 << "\" : " << are_equal << std::endl;
	str1 = "STRING 1";
	str2 = "string 2";
	are_equal = str1.compare(str2, bump::String::CaseSensitive);
	std::cout << "- \"" << str1 << "\" == \"" << str2 << "\" : " << are_equal << " : Case Sensitive" << std::endl;
	are_equal = str1.compare(str2, bump::String::NotCaseSensitive);
	std::cout << "- \"" << str1 << "\" == \"" << str2 << "\" : " << are_equal << " : Not Case Sensitive" << std::endl;

	// Another useful comparison is to know whether a string starts with a different string
	std::cout << "\nComparing if a string starts with another string:" << std::endl;
	str1 = "What does this string start with?";
	str2 = "what";
	bump::String starts_with = str1.startsWith(str2, bump::String::CaseSensitive);
	std::cout << "- Does \"" << str1 << "\" start with \"" << str2 << "\" : " << starts_with << " : Case Sensitive" << std::endl;
	starts_with = str1.startsWith(str2, bump::String::NotCaseSensitive);
	std::cout << "- Does \"" << str1 << "\" start with \"" << str2 << "\" : " << starts_with << " : Not Case Sensitive" << std::endl;

	// Another useful comparison is to know whether a string ends with a different string
	std::cout << "\nComparing if a string ends with another string:" << std::endl;
	str1 = "Do I end with this?";
	str2 = "THIS?";
	bump::String ends_with = str1.endsWith(str2, bump::String::CaseSensitive);
	std::cout << "- Does \"" << str1 << "\" end with \"" << str2 << "\" : " << ends_with << " : Case Sensitive" << std::endl;
	ends_with = str1.endsWith(str2, bump::String::NotCaseSensitive);
	std::cout << "- Does \"" << str1 << "\" end with \"" << str2 << "\" : " << ends_with << " : Not Case Sensitive" << std::endl;
}

void manipulation()
{
	std::cout << "\n============================ MANIPULATION ============================" << std::endl;

	// How to add a string to the beginning of another string (prepend)
	std::cout << "\nPrepending a string onto another string:" << std::endl;
	bump::String str1 = "Strings are cool";
	bump::String str2 = "bump::";
	std::cout << "- \"" << str1 << "\" prepended with \"" << str2 << "\" equals \"";
	str1.prepend(str2);
	std::cout << str1 << "\"" << std::endl;

	// How to add a string onto the end of another string (append).
	// NOTE: You can also use the << operator shown in the Formatting section.
	std::cout << "\nAppending a string onto another string:" << std::endl;
	str1 = "string 1";
	str2 = " and also string 2";
	std::cout << "- \"" << str1 << "\" appended with \"" << str2 << "\" equals \"";
	str1.append(str2);
	std::cout << str1 << "\"" << std::endl;

	// How to remove a portion of the string
	std::cout << "\nRemoving a string from another string:" << std::endl;
	str1 = "This is a simple string";
	str2 = "simple ";
	std::cout << "- Removing \"" << str2 << "\" from \"" << str1 << "\" equals \"";
	str1.remove(str2);
	std::cout << str1 << "\"" << std::endl;
	str1 = "This is a simple string";
	std::cout << "- Removing the first 8 characters of \"" << str1 << "\" equals \"";
	str1.remove(0, 8);
	std::cout << str1 << "\"" << std::endl;

	// How to chop off characters from the end of a string
	std::cout << "\nChopping off characters from the end of a string:" << std::endl;
	str1 = "Be sure to go to the movies";
	std::cout << "- Chopping off the last 14 character of \"" << str1 << "\" equals \"";
	str1.chop(14);
	std::cout << str1 << "\"" << std::endl;

	// How to trim off whitespace from the beginning and end of a string
	std::cout << "\nTrimming off whitespace from the beginning and end of a string:" << std::endl;
	str1 = "   I have some spaces   ";
	std::cout << "- Trimming \"" << str1 << "\" equals \"";
	str2 = str1.trimmed();
	std::cout << str2 << "\"" << std::endl;
	str1 = "\t\n\t \t I have some spaces and special characters  \t\n";
	std::cout << "- Trimming \"" << "\\t\\n\\t \\t I have some spaces and special characters  \\t\\n" << "\" equals \"";
	str2 = str1.trimmed();
	std::cout << str2 << "\"" << std::endl;
}

void extraction()
{
	std::cout << "\n============================ EXTRACTION ============================" << std::endl;

	// How to extract a section of a string
	std::cout << "\nExtracting a section of a string:" << std::endl;
	bump::String str1 = "Be sure to go to the movies";
	std::cout << "- Extracting all characters starting at position 11 from \"" << str1 << "\" equals \"";
	bump::String str2 = str1.section(11);
	std::cout << str2 << "\"" << std::endl;
	str1 = "Processing File 1 of 20: test.txt";
	std::cout << "- Extracting 7 characters starting at position 16 from \"" << str1 << "\" equals \"";
	str2 = str1.section(16, 7);
	std::cout << str2 << "\"" << std::endl;

	// How to extract a left portion of a string
	std::cout << "\nExtracting a left portion of a string:" << std::endl;
	str1 = "<node>testing</node>";
	std::cout << "- Extracting 6 characters from the left side of \"" << str1 << "\" equals \"";
	str2 = str1.left(6);
	std::cout << str2 << "\"" << std::endl;

	// How to extract a right portion of a string
	std::cout << "\nExtracting a right portion of a string:" << std::endl;
	str1 = "<node>testing</node>";
	std::cout << "- Extracting 7 characters from the right side of \"" << str1 << "\" equals \"";
	str2 = str1.right(7);
	std::cout << str2 << "\"" << std::endl;
}

void capitalization()
{
	std::cout << "\n============================ CAPITALIZATION ============================" << std::endl;

	// How to convert the string to lower case characters
	std::cout << "\nConverting a string to lower case characters:" << std::endl;
	bump::String str1 = "ALL CAPS!";
	std::cout << "- Converting \"" << str1 << "\" to lower case equals \"";
	str1.toLowerCase();
	std::cout << str1 << "\"" << std::endl;

	// How to convert the string to upper case characters
	std::cout << "\nConverting a string to upper case characters:" << std::endl;
	str1 = "nothing here is capitalized";
	std::cout << "- Converting \"" << str1 << "\" to upper case equals \"";
	str1.toLowerCase();
	std::cout << str1 << "\"" << std::endl;

	// How to capitalize the first letter of a string
	std::cout << "\nCapitalizing the first letter of a string:" << std::endl;
	str1 = "a documentary on planets";
	std::cout << "- Capitalizing \"" << str1 << "\" equals \"";
	str1.capitalize();
	std::cout << str1 << "\"" << std::endl;

	// How to capitalize all the words in a string (the first character and any following a space)
	std::cout << "\nCapitalizing all words like a title of a book:" << std::endl;
	str1 = "running around like crazy";
	std::cout << "- Capitalizing all words from \"" << str1 << "\" equals \"";
	bump::String str2 = str1.title();
	std::cout << str2 << "\"" << std::endl;
}

void findReplace()
{
	std::cout << "\n============================ FIND/REPLACE ============================" << std::endl;

	// How to see if a string contains another string
	std::cout << "\nDetermining if a string contains another string:" << std::endl;
	bump::String str1 = "I like using spaces in sentences";
	bump::String str2 = " ";
	bump::String contains = str1.contains(str2);
	std::cout << "- Does \"" << str1 << "\" contain \"" << str2 << "\" : " << contains << std::endl;
	str1 = "I ran a really long race";
	str2 = "bad";
	contains = str1.contains(str2);
	std::cout << "- Does \"" << str1 << "\" contain \"" << str2 << "\" : " << contains << std::endl;

	// How to find the index of a string inside another string
	std::cout << "\nFinding the index of a string inside another string:" << std::endl;
	str1 = "i drove down the runway";
	str2 = "down";
	int index = str1.indexOf(str2);
	std::cout << "- Where is \"" << str2 << "\" in \"" << str1 << "\" : " << index << std::endl;
	str1 = "Our new kitchen floor is almost finished.";
	str2 = "done";
	index = str1.indexOf(str2);
	std::cout << "- Where is \"" << str2 << "\" in \"" << str1 << "\" : " << index << std::endl;

	// How to find the last index of a string inside another string
	std::cout << "\nFinding the last index of a string inside another string:" << std::endl;
	str1 = "i drove down the runway";
	str2 = "e";
	index = str1.lastIndexOf(str2);
	std::cout << "- Where is the last \"" << str2 << "\" in \"" << str1 << "\" : " << index << std::endl;
	str1 = "a giant dog ate a tiny cat.";
	str2 = "a ";
	index = str1.lastIndexOf(str2);
	std::cout << "- Where is the last \"" << str2 << "\" in \"" << str1 << "\" : " << index << std::endl;

	// How to replace a specified section of a string
	std::cout << "\nReplacing a specified section of another string:" << std::endl;
	str1 = "i drove down the runway";
	str2 = "with my eyes closed";
	std::cout << "- Replacing 15 characters at position 8 in \"" << str1 << "\" with \"" << str2 << "\" equals \"";
	str1.replace(8, 15, str2);
	std::cout << str1 << "\"" << std::endl;

	// How to replace a string with another string
	std::cout << "\nReplacing a string with another string:" << std::endl;
	str1 = "i drove down the runway";
	str2 = "runway";
	bump::String str3 = "driveway";
	std::cout << "- Replacing \"" << str2 << "\" with \"" << str3 << "\" in \"" << str1 << "\" equals \"";
	str1.replace(str2, str3);
	std::cout << str1 << "\"" << std::endl;
}

void joinSplit()
{
	std::cout << "\n============================ JOIN/SPLIT ============================" << std::endl;

	// How to split a string into a list of strings
	std::cout << "\nSplitting a string into a list of strings:" << std::endl;
	bump::String str1 = "these are a bunch of words";
	bump::String str2 = " ";
	bump::StringList split_strings = str1.split(str2);
	std::cout << "- Splitting \"" << str1 << "\" with \"" << str2 << "\" equals:";
	for (unsigned int i = 0; i < split_strings.size(); ++i)
	{
		std::cout << " [\"" << split_strings.at(i) << "\"]";
	}
	std::cout << std::endl;

	// How to join a list of strings into a single string
	std::cout << "\nJoining a list of strings into a single string:" << std::endl;
	str1 = bump::String::join(split_strings, " ");
	std::cout << "- Joining List: ";
	for (unsigned int i = 0; i < split_strings.size(); ++i)
	{
		std::cout << " [\"" << split_strings.at(i) << "\"]";
	}
	std::cout << " with \" \" into a single string equals \"" << str1 << "\"" << std::endl;
}
