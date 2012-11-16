//
//	String.h
//	Bump
//
//	Created by Christian Noon on 11/7/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_STRING_H
#define BUMP_STRING_H

// C++ headers
#include <iostream>
#include <vector>

// Bump headers
#include <bump/Export.h>

namespace bump {

// Forward Declarations
class String;

// Typedefs
typedef std::vector<String> StringList;

/**
 * A string class which adds lots of useful string methods ontop of the std::string class. These
 * methods range from custom print methods for many different types of objects as well as string
 * methods common in both Python and Objective-C. This class was developed to eliminate the pain
 * of string parsing by implementing a much more straight forward syntax to make development much
 * easier and less time consuming.
 */
class BUMP_EXPORT String : public std::string
{
public:

	/**
	 * Case Sensitivity enumeration.
	 *
	 * This enumeration is used in many methods to specify whether or not
	 * you would like to use a case sensitive search.
	 */
	enum CaseSensitivity
	{
		CaseSensitive = 0,
		NotCaseSensitive = 1
	};

	/**
	 * Default constructor.
	 */
	String();

	/**
	 * Constructor that takes a const char*.
	 *
	 * @param cString the c string to convert to a string.
	 */
	String(const char* cString);

	/**
	 * Constructor that takes a std::string.
	 *
	 * @param stdString the std::string to convert to a string.
	 */
	String(const std::string& stdString);

	/**
	 * Constructor that takes an unsigned char.
	 *
	 * @param number the number to convert to a string.
	 */
	String(unsigned char number);

	/**
	 * Constructor that takes a char.
	 *
	 * @param number the number to convert to a string.
	 */
	String(char number);

	/**
	 * Constructor that takes an unsigned short.
	 *
	 * @param number the number to convert to a string.
	 */
	String(unsigned short number);

	/**
	 * Constructor that takes a short.
	 *
	 * @param number the number to convert to a string.
	 */
	String(short number);

	/**
	 * Constructor that takes an unsigned int.
	 *
	 * @param number the number to convert to a string.
	 */
	String(unsigned int number);

	/**
	 * Constructor that takes an int.
	 *
	 * @param number the number to convert to a string.
	 */
	String(int number);

	/**
	 * Constructor that takes an unsigned long.
	 *
	 * @param number the number to convert to a string.
	 */
	String(unsigned long number);

	/**
	 * Constructor that takes a long.
	 *
	 * @param number the number to convert to a string.
	 */
	String(long number);

	/**
	 * Constructor that takes an unsigned long long.
	 *
	 * @param number the number to convert to a string.
	 */
	String(unsigned long long number);

	/**
	 * Constructor that takes a long long.
	 *
	 * @param number the number to convert to a string.
	 */
	String(long long number);

	/**
	 * Constructor that takes a float.
	 *
	 * Throw an InvalidArgumentError when precision is less than -1.
	 *
	 * @param number the number to convert to a string.
	 * @param precision the number of decimal places, default is -1 which uses full decimal representation.
	 */
	String(float number, int precision = -1);

	/**
	 * Constructor that takes a double.
	 *
	 * Throw an InvalidArgumentError when precision is less than -1.
	 *
	 * @param number the number to convert to a string.
	 * @param precision the number of decimal places, default is -1 which uses full decimal representation.
	 */
	String(double number, int precision = -1);

	/**
	 * Constructor that takes a bool.
	 *
	 * @param boolValue a boolean to convert to a string.
	 */
	String(bool boolValue);

	/**
	 * Destructor.
	 */
	~String();

	/**
	 * Joins all the strings into a single string each separated by the separator string.
	 *
	 * @param strings a list of strings to join.
	 * @param separator a string used to separate each of the joined strings.
	 * @return a single string consisting of the list of string joined together by the separator string.
	 */
	static String join(const StringList& strings, const String& separator);

	/**
	 * Appends the given string onto the end of this string.
	 *
	 * @param appendString the string to add.
	 * @return a reference to the modified string.
	 */
	String& append(const String& appendString);

	/**
	 * Appends the given string onto the end of this string.
	 *
	 * @param appendString the c string to add.
	 * @return a reference to the modified string.
	 */
	String& append(const char* appendString);

	/**
	 * Creates a copy of this string with the lowest numbered marker replaced by a1.
	 *
	 * Throws a SearchError when no valid valid markers are found (i.e. %1-%99).
	 *
	 * Here is a small example demonstrating...
	 *
	 * bump::String example("Copying files %1 of %2: %3");
	 * bump::String replaced = example.arg(1).arg(10).arg(test.txt);
	 * // replaced = "Copying files 1 of 10: test.txt"
	 *
	 * @param a1 a string to replace the lowest numbered marker
	 * @return a copy of the string with the lowest numbered marker replaced.
	 */
	String arg(const String& a1) const;

	/**
	 * Creates a copy of this string with the two lowest numbered markers replaced by a1 and a2.
	 *
	 * Throws a SearchError when no valid valid markers are found (i.e. %1-%99).
	 *
	 * The same as str.arg(a1).arg(a2).
	 *
	 * Here is a small example demonstrating...
	 *
	 * bump::String example("Copying files %1 of %2");
	 * bump::String replaced = example.arg(1, 10);
	 * // replaced = "Copying files 1 of 10"
	 *
	 * @param a1 a string to replace the lowest numbered marker
	 * @param a2 a string to replace the second lowest numbered marker
	 * @return a copy of the string with the two lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2) const;

	/**
	 * Creates a copy of this string with the three lowest numbered markers replaced by a1, a2 and a3.
	 *
	 * Throws a SearchError when no valid valid markers are found (i.e. %1-%99).
	 *
	 * The same as str.arg(a1).arg(a2).arg(a3).
	 *
	 * @param a1 a string to replace the lowest numbered marker
	 * @param a2 a string to replace the second lowest numbered marker
	 * @param a3 a string to replace the third lowest numbered marker
	 * @return a copy of the string with the three lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3) const;

	/**
	 * Creates a copy of this string with the four lowest numbered markers replaced.
	 *
	 * Throws a SearchError when no valid valid markers are found (i.e. %1-%99).
	 *
	 * The same as str.arg(a1).arg(a2).arg(a3).arg(a4).
	 *
	 * @param a1 a string to replace the lowest numbered marker
	 * @param a2 a string to replace the second lowest numbered marker
	 * @param a3 a string to replace the third lowest numbered marker
	 * @param a4 a string to replace the fourth lowest numbered marker
	 * @return a copy of the string with the four lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4) const;

	/**
	 * Creates a copy of this string with the five lowest numbered markers replaced.
	 *
	 * Throws a SearchError when no valid valid markers are found (i.e. %1-%99).
	 *
	 * The same as str.arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).
	 *
	 * @param a1 a string to replace the lowest numbered marker
	 * @param a2 a string to replace the second lowest numbered marker
	 * @param a3 a string to replace the third lowest numbered marker
	 * @param a4 a string to replace the fourth lowest numbered marker
	 * @param a5 a string to replace the fifth lowest numbered marker
	 * @return a copy of the string with the five lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5) const;

	/**
	 * Creates a copy of this string with the six lowest numbered markers replaced.
	 *
	 * Throws a SearchError when no valid valid markers are found (i.e. %1-%99).
	 *
	 * The same as str.arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).
	 *
	 * @param a1 a string to replace the lowest numbered marker
	 * @param a2 a string to replace the second lowest numbered marker
	 * @param a3 a string to replace the third lowest numbered marker
	 * @param a4 a string to replace the fourth lowest numbered marker
	 * @param a5 a string to replace the fifth lowest numbered marker
	 * @param a6 a string to replace the sixth lowest numbered marker
	 * @return a copy of the string with the six lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
			   const String& a6) const;

	/**
	 * Creates a copy of this string with the seven lowest numbered markers replaced.
	 *
	 * Throws a SearchError when no valid valid markers are found (i.e. %1-%99).
	 *
	 * The same as str.arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7).
	 *
	 * @param a1 a string to replace the lowest numbered marker
	 * @param a2 a string to replace the second lowest numbered marker
	 * @param a3 a string to replace the third lowest numbered marker
	 * @param a4 a string to replace the fourth lowest numbered marker
	 * @param a5 a string to replace the fifth lowest numbered marker
	 * @param a6 a string to replace the sixth lowest numbered marker
	 * @param a7 a string to replace the seventh lowest numbered marker
	 * @return a copy of the string with the seven lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
			   const String& a6, const String& a7) const;

	/**
	 * Creates a copy of this string with the eight lowest numbered markers replaced.
	 *
	 * Throws a SearchError when no valid valid markers are found (i.e. %1-%99).
	 *
	 * The same as str.arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7).arg(a8).
	 *
	 * @param a1 a string to replace the lowest numbered marker
	 * @param a2 a string to replace the second lowest numbered marker
	 * @param a3 a string to replace the third lowest numbered marker
	 * @param a4 a string to replace the fourth lowest numbered marker
	 * @param a5 a string to replace the fifth lowest numbered marker
	 * @param a6 a string to replace the sixth lowest numbered marker
	 * @param a7 a string to replace the seventh lowest numbered marker
	 * @param a8 a string to replace the eighth lowest numbered marker
	 * @return a copy of the string with the eight lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
			   const String& a6, const String& a7, const String& a8) const;

	/**
	 * Creates a copy of this string with the nine lowest numbered markers replaced.
	 *
	 * Throws a SearchError when no valid valid markers are found (i.e. %1-%99).
	 *
	 * The same as str.arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7).arg(a8).arg(a9).
	 *
	 * @param a1 a string to replace the lowest numbered marker
	 * @param a2 a string to replace the second lowest numbered marker
	 * @param a3 a string to replace the third lowest numbered marker
	 * @param a4 a string to replace the fourth lowest numbered marker
	 * @param a5 a string to replace the fifth lowest numbered marker
	 * @param a6 a string to replace the sixth lowest numbered marker
	 * @param a7 a string to replace the seventh lowest numbered marker
	 * @param a8 a string to replace the eighth lowest numbered marker
	 * @param a9 a string to replace the ninth lowest numbered marker
	 * @return a copy of the string with the nine lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
			   const String& a6, const String& a7, const String& a8, const String& a9) const;

	/**
	 * Locates and returns the character at the position in this string.
	 *
	 * Throws an OutOfRangeError when position is outside this string's bounds.
	 *
	 * @param position the position of the character to return of this string.
	 * @return the character at the given position.
	 */
	const char at(int position) const;

	/**
	 * Converts the string to a c string.
	 *
	 * @return the c string representation of the string.
	 */
	const char* c_str() const;

	/**
	 * Capitalizes the first letter of this string.
	 *
	 * @return a reference to the modified string.
	 */
	String& capitalize();

	/**
	 * Chops the specified number of characters off from the end of this string.
	 *
	 * If n is greater than the string's length, the result is an empty string.
	 *
	 * @param n the number of characters to chop off the end of this string.
	 * @return the modified version of this string.
	 */
	String& chop(unsigned int n);

	/**
	 * Clears the contents of the string making it empty.
	 */
	void clear();

	/**
	 * Compares the content of the this string with the given string.
	 *
	 * @param otherString the string to compare content against with this string.
	 * @return whether the content within both objects is the same.
	 */
	bool compare(const String& otherString) const;

	/**
	 * Compares the content of the this string with the given string.
	 *
	 * @param otherString the const char* to compare content against with this string.
	 * @return whether the content within both objects is the same.
	 */
	bool compare(const char* otherString) const;

	/**
	 * Finds out whether this string contains an occurrence of the given string.
	 *
	 * @param containString the String to see if is contained within this string.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return true if the string contains an occurrence of containString, otherwise returns false.
	 */
	bool contains(const String& containString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Finds out whether this string contains an occurrence of the given string.
	 *
	 * @param containString the const char* to see if is contained within this string.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return true if the string contains an occurrence of containString, otherwise returns false.
	 */
	bool contains(const char* containString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Counts the number of (potentially overlapping) occurrences of the given string in this string.
	 *
	 * @param containString the tring to see if is contained within this string.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return the number of occurrences of the given string in this string.
	 */
	int count(const String& containString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Counts the number of (potentially overlapping) occurrences of the given string in this string.
	 *
	 * @param containString the const char* to see if is contained within this string.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return the number of occurrences of the given string in this string.
	 */
	int count(const char* containString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Returns a pointer to an array of characters without appending a terminating null character.
	 *
	 * @return a pointer to an array of characters without appending a terminating null character.
	 */
	const char* data() const;

	/**
	 * Checks whether this string ends with the given string.
	 *
	 * @param endString the string to check if this string ends with.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return true if this string ends with endString, otherwise returns false.
	 */
	bool endsWith(const String& endString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Checks whether this string ends with the given string.
	 *
	 * @param endString the const char* to check if this string ends with.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return true if this string ends with endString, otherwise returns false.
	 */
	bool endsWith(const char* endString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Sets every character in the string to character. If size is different from -1 (default),
	 * the string is resized to size beforehand.
	 *
	 * Throws an InvalidArgumentError when passed a character string with length not equal to one.
	 * Throws an InvalidArgumentError when passed a size less than -1.
	 *
	 * @param character the character to fill this string with.
	 * @param size the size to resize this string to be filling.
	 * @return a reference to the modified string.
	 */
	String& fill(const String& character, int size = -1);

	/**
	 * Finds the position of the first occurrence of indexString in this string by searching
	 * forward from the startPosition.
	 *
	 * Throws an InvalidArgumentError when passed an empty index string.
	 *
	 * @param indexString the String to find the first occurence of in this string.
	 * @param startPosition the index of the string to start searching at.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return the position of the first occurrence of indexString, defaults to -1 if not found.
	 */
	int indexOf(const String& indexString, int startPosition = 0, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Finds the position of the first occurrence of indexString in this string by searching
	 * forward from the startPosition.
	 *
	 * Throws an InvalidArgumentError when passed an empty index string.
	 *
	 * @param indexString the const char* to find the first occurence of in this string.
	 * @param startPosition the index of the string to start searching at.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return the position of the first occurrence of indexString, defaults to -1 if not found.
	 */
	int indexOf(const char* indexString, int startPosition = 0, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Inserts the insertString at the given position.
	 *
	 * Throws an InvalidArgumentError when passed an empty insert string.
	 * Throws an OutOfRangeError when position is outside this string's bounds.
	 *
	 * @param position the index position of the string to start inserting at.
	 * @param insertString the String to insert at the given index position in this string.
	 * @return a reference to the modified string.
	 */
	String& insert(const String& insertString, int position);

	/**
	 * Inserts the insertString at the given position.
	 *
	 * @param position the index position of the string to start inserting at.
	 * @param insertString the const char* to insert at the given index position in this string.
	 * @return a reference to the modified string.
	 */
	String& insert(const char* insertString, int position);

	/**
	 * Determines whether the string has any characters.
	 *
	 * @return true if the string has no characters, otherwise returns false.
	 */
	bool isEmpty() const;

	/**
	 * Determines whether the string is any kind of number (int, float, double, scientific).
	 *
	 * @return whether the string is a valid number (int, float, double, scientific).
	 */
	bool isNumber() const;

	/**
	 * Finds the position of the last occurrence of indexString in this string by searching
	 * backwards from the startPosition. If startPosition is -1 (default), the search starts
	 * at the last character.
	 *
	 * Throws an InvalidArgumentError when passed an empty index string.
	 *
	 * @param indexString the string to find the last occurence of in this string.
	 * @param startPosition the index of the string to start searching at.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return the position of the last occurrence of indexString, defaults to -1 if not found.
	 */
	int lastIndexOf(String indexString, int startPosition = -1, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Finds the position of the last occurrence of indexString in this string by searching
	 * backwards from the startPosition. If startPosition is -1 (default), the search starts
	 * at the last character.
	 *
	 * Throws an InvalidArgumentError when passed an empty index string.
	 *
	 * @param indexString the const char* to find the last occurence of in this string.
	 * @param startPosition the index of the string to start searching at.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return the position of the last occurrence of indexString, defaults to -1 if not found.
	 */
	int lastIndexOf(const char* indexString, int startPosition = -1, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Finds the substring that contains the number of leftmost characters of this string.
	 *
	 * Throws an OutOfRangeError when n is outside this string's bounds.
	 *
	 * @param n the number of characters to return.
	 * @return the substring of the leftmost number of characters of this string.
	 */
	String left(int n) const;

	/**
	 * Computes the total number of characters in this string.
	 *
	 * @return the total number of characters in this string.
	 */
	unsigned int length() const;

	/**
	 * Adds the given string to the beginning of this string.
	 *
	 * @param prependString the string to add to the beginning of this string.
	 * @return the modified version of this string.
	 */
	String& prepend(const String& prependString);

	/**
	 * Adds the given string to the beginning of this string.
	 *
	 * @param prependString the const char* to add to the beginning of this string.
	 * @return the modified version of this string.
	 */
	String& prepend(const char* prependString);

	/**
	 * Removes the given width of characters starting at the given position.
	 *
	 * Throws an OutOfRangeError when position is outside this string's bounds.
	 * Throws an InvalidArgumentError when n is negative.
	 *
	 * @param position the index position to start removing characters at from this string.
	 * @param n the number of characters to remove from this string.
	 * @return the modified version of this string.
	 */
	String& remove(int position, int n);

	/**
	 * Removes every occurrence of the given in this string.
	 *
	 * Throws an InvalidArgumentError when the remove string is empty.
	 *
	 * @param removeString the string to remove from this string.
	 * @param caseSensitivity - the case sensitivity to be used, defaults to String::CaseSensitive.
	 * @return the modified version of this string.
	 */
	String& remove(const String& removeString, CaseSensitivity caseSensitivity = CaseSensitive);

	/**
	 * Removes every occurrence of the given in this string.
	 *
	 * Throws an InvalidArgumentError when the remove string is empty.
	 *
	 * @param removeString the const char* to remove from this string.
	 * @param caseSensitivity - the case sensitivity to be used, defaults to String::CaseSensitive.
	 * @return the modified version of this string.
	 */
	String& remove(const char* removeString, CaseSensitivity caseSensitivity = CaseSensitive);

	/**
	 * Generates a new string repeated the specified number of times.
	 *
	 * Passing a value of zero will return an empty string.
	 *
	 * @param times the number of times the new string will be repeated.
	 * @return a new string repeated the specified number of times.
	 */
	String repeated(unsigned int times) const;

	/**
	 * Replaces n characters starting at position with the replace string.
	 *
	 * Throws an OutOfRangeError when position is outside this string's bounds.
	 * Throws an InvalidArgumentError when n is negative.
	 *
	 * @param position the index of this string to start replacing at.
	 * @param n the number of characters to replace in this string.
	 * @param replaceString the string to replace the n characters in this string.
	 * @return the modified version of this string.
	 */
	String& replace(int position, int n, const String& replaceString);

	/**
	 * Replaces n characters starting at position with the replace string.
	 *
	 * Throws an OutOfRangeError when position is outside this string's bounds.
	 * Throws an InvalidArgumentError when n is negative.
	 *
	 * @param position the index of this string to start replacing at.
	 * @param n the number of characters to replace in this string.
	 * @param replaceString the const char* to replace the n characters in this string.
	 * @return the modified version of this string.
	 */
	String& replace(int position, int n, const char* replaceString);

	/**
	 * Replaces every occurrence of the before string with the after string.
	 *
	 * Throws an InvalidArgumentError when passed an empty before string.
	 *
	 * @param before the string to be replaced.
	 * @param after the string to replace the before string.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return the modified version of this string.
	 */
	String& replace(const String& before, const String& after, CaseSensitivity caseSensitivity = CaseSensitive);

	/**
	 * Replaces every occurrence of the before string with the after string.
	 *
	 * Throws an InvalidArgumentError when passed an empty before string.
	 *
	 * @param before the const char* to be replaced.
	 * @param after the const char* to replace the before string.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return the modified version of this string.
	 */
	String& replace(const char* before, const char* after, CaseSensitivity caseSensitivity = CaseSensitive);

	/**
	 * Finds the substring that contains the number of rightmost characters of this string.
	 *
	 * Throws an OutOfRangeError when n is outside this string's bounds.
	 *
	 * @param n the number of characters to return.
	 * @return the substring of the rightmost number of characters of this string.
	 */
	String right(int n) const;

	/**
	 * Creates a substring of the given length beginning at the start position.
	 *
	 * Throws an OutOfRangeError when position is outside this string's bounds.
	 * Throws an InvalidArgumentError when length is less than one.
	 *
	 * @param startPosition the starting position in this string to begin the section.
	 * @param length the length of the section to extract from the string.
	 * @return a section of the string beginning at the start position with the given length.
	 */
	String section(int startPosition, int length = -1) const;

	/**
	 * Splits the string into a list of string that were separated by the given separator string.
	 *
	 * @param separator a string used to split the string into a list of strings.
	 * @return a list of strings separated by the separator character
	 */
	StringList split(const String& separator) const;

	/**
	 * Checks whether this string starts with the given string.
	 *
	 * @param startString the string to check if this string starts with.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return true if this string starts with startString, otherwise returns false.
	 */
	bool startsWith(const String& startString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Checks whether this string starts with the given string.
	 *
	 * @param startString the const char* to check if this string starts with.
	 * @param caseSensitivity the case sensitivity to be used, defaults to CaseSensitive.
	 * @return true if this string starts with startString, otherwise returns false.
	 */
	bool startsWith(const char* startString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Creates a new string beginning at the start position with the given length.
	 *
	 * Throws an OutOfRangeError when the start position is outside this string's bounds.
	 * Throws an InvalidArgumentError when length is greater than zero.
	 *
	 * @param startPosition the index position to start the section at in this string.
	 * @param length the length of the section to extract from the string.
	 * @return the string beginning at the start position with the given length.
	 */
	String subString(int startPosition, int length) const;

	/**
	 * Capitalizes all the first letters of each word in the string.
	 *
	 * @return a new string with all the first letters of each word capitalized.
	 */
	String title() const;

	/**
	 * Converts this string to a boolean.
	 *
	 * Throws a TypeCastError when this string cannot be converted to a boolean.
	 *
	 * @return the bool value of the string.
	 */
	bool toBool() const;

	/**
	 * Converts this string to a double.
	 *
	 * Throws a TypeCastError when this string cannot be converted to a double.
	 *
	 * @return the double value of the string.
	 */
	double toDouble() const;

	/**
	 * Converts this string to a float.
	 *
	 * Throws a TypeCastError when this string cannot be converted to a float.
	 *
	 * @return the float value of the string.
	 */
	float toFloat() const;

	/**
	 * Converts this string to an int.
	 *
	 * Throws a TypeCastError when this string cannot be converted to an int.
	 *
	 * @return the int value of the string.
	 */
	int toInt() const;

	/**
	 * Converts this string to a long.
	 *
	 * Throws a TypeCastError when this string cannot be converted to a long.
	 *
	 * @return the long value of the string.
	 */
	long toLong() const;

	/**
	 * Converts this string to a long long.
	 *
	 * Throws a TypeCastError when this string cannot be converted to a long long.
	 *
	 * @return the long long value of the string.
	 */
	long long toLongLong() const;

	/**
	 * Converts this string to all lowercase text.
	 *
	 * @return the modified version of this string.
	 */
	String& toLowerCase();

	/**
	 * Converts this string to a short.
	 *
	 * Throws a TypeCastError when this string cannot be converted to a short.
	 *
	 * @return the short value of the string.
	 */
	short toShort() const;

	/**
	 * Converts the string to a std::string.
	 *
	 * @return the std::string representation of the string.
	 */
	std::string toStdString() const;

	/**
	 * Converts this string to an unsigned int.
	 *
	 * Throws a TypeCastError when this string cannot be converted to an unsigned int.
	 *
	 * @return the unsigned int value of the string.
	 */
	unsigned int toUInt() const;

	/**
	 * Converts this string to an unsigned long.
	 *
	 * Throws a TypeCastError when this string cannot be converted to an unsigned long.
	 *
	 * @return the unsigned long value of the string.
	 */
	unsigned long toULong() const;

	/**
	 * Converts this string to an unsigned long long.
	 *
	 * Throws a TypeCastError when this string cannot be converted to an unsigned long long.
	 *
	 * @return the unsigned long long value of the string.
	 */
	unsigned long long toULongLong() const;

	/**
	 * Converts this string to all uppercase text.
	 *
	 * @return the modified version of this string.
	 */
	String& toUpperCase();

	/**
	 * Converts this string to an unsigned short.
	 *
	 * Throws a TypeCastError when this string cannot be converted to an unsigned short.
	 *
	 * @return the unsigned short value of the string.
	 */
	unsigned short toUShort() const;

	/**
	 * Generates a string that has all whitespace removed from the start and end.
	 *
	 * Whitespace characters are ' ', '\t', '\n', '\v', '\f' and '\r'.
	 *
	 * @return a new string that has all whitespace removed from the start and end.
	 */
	String trimmed() const;

	/**
	 * Appends the string onto the end of this string.
	 *
	 * @param appendString the string to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (const String& appendString);

	/**
	 * Appends the string onto the end of this string.
	 *
	 * @param appendString the const char* to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (const char* appendString);

	/**
	 * Appends the unsigned char to the end of this string.
	 *
	 * @param appendChar the unsigned char to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (unsigned char appendChar);

	/**
	 * Appends the char to the end of this string.
	 *
	 * @param appendChar the char to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (char appendChar);

	/**
	 * Appends the unsigned short to the end of this string.
	 *
	 * @param appendShort the unsigned short to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (unsigned short appendShort);

	/**
	 * Appends the short to the end of this string.
	 *
	 * @param appendShort the short to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (short appendShort);

	/**
	 * Appends the unsigned int to the end of this string.
	 *
	 * @param appendInt the unsigned int to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (unsigned int appendInt);

	/**
	 * Appends the int to the end of this string.
	 *
	 * @param appendInt the int to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (int appendInt);

	/**
	 * Appends the unsigned long to the end of this string.
	 *
	 * @param appendLong the unsigned long to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (unsigned long appendLong);

	/**
	 * Appends the long to the end of this string.
	 *
	 * @param appendLong the long to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (long appendLong);

	/**
	 * Appends the unsigned long long to the end of this string.
	 *
	 * @param appendLongLong the unsigned long long to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (unsigned long long appendLongLong);

	/**
	 * Appends the long long to the end of this string.
	 *
	 * @param appendLongLong the long long to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (long long appendLongLong);

	/**
	 * Appends the float to the end of this string.
	 *
	 * @param appendFloat the float to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (float appendFloat);

	/**
	 * Appends the double to the end of this string.
	 *
	 * @param appendDouble the float to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (double appendDouble);

	/**
	 * Appends the bool to the end of this string.
	 *
	 * @param appendBool the bool to append onto this string.
	 * @return the modified version of this string.
	 */
	String& operator << (bool appendBool);
};

}	// End of bump namespace

#endif	// End of BUMP_STRING_H
