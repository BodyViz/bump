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
#include <set>
#include <string>
#include <vector>

// Bump headers
#include <bump/Export.h>

namespace bump {

// Forward Declarations
class String;

// Typedefs
typedef std::vector<String> StringList;		/**< A shortcut typedef for an std::vector of bump::String objects. */
typedef std::set<String> StringSet;			/**< A shortcut typedef for an std::set of bump::String objects. */

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
	 * @param cString The c string to convert to a string.
	 */
	String(const char* cString);

	/**
	 * Constructor that takes a std::string.
	 *
	 * @param stdString The std::string to convert to a string.
	 */
	String(const std::string& stdString);

	/**
	 * Constructor that takes an unsigned char.
	 *
	 * @param number The number to convert to a string.
	 */
	String(unsigned char number);

	/**
	 * Constructor that takes a char.
	 *
	 * @param number The number to convert to a string.
	 */
	String(char number);

	/**
	 * Constructor that takes an unsigned short.
	 *
	 * @param number The number to convert to a string.
	 */
	String(unsigned short number);

	/**
	 * Constructor that takes a short.
	 *
	 * @param number The number to convert to a string.
	 */
	String(short number);

	/**
	 * Constructor that takes an unsigned int.
	 *
	 * @param number The number to convert to a string.
	 */
	String(unsigned int number);

	/**
	 * Constructor that takes an int.
	 *
	 * @param number The number to convert to a string.
	 */
	String(int number);

	/**
	 * Constructor that takes an unsigned long.
	 *
	 * @param number The number to convert to a string.
	 */
	String(unsigned long number);

	/**
	 * Constructor that takes a long.
	 *
	 * @param number The number to convert to a string.
	 */
	String(long number);

	/**
	 * Constructor that takes an unsigned long long.
	 *
	 * @param number The number to convert to a string.
	 */
	String(unsigned long long number);

	/**
	 * Constructor that takes a long long.
	 *
	 * @param number The number to convert to a string.
	 */
	String(long long number);

	/**
	 * Constructor that takes a float.
	 *
	 * @throw bump::InvalidArgumentError When precision is less than -1.
	 *
	 * @param number The number to convert to a string.
	 * @param precision The number of decimal places, default is -1 which uses full decimal representation.
	 */
	String(float number, int precision = -1);

	/**
	 * Constructor that takes a double.
	 *
	 * @throw bump::InvalidArgumentError When precision is less than -1.
	 *
	 * @param number The number to convert to a string.
	 * @param precision The number of decimal places, default is -1 which uses full decimal representation.
	 */
	String(double number, int precision = -1);

	/**
	 * Constructor that takes a bool.
	 *
	 * @param boolValue A boolean to convert to a string.
	 */
	String(bool boolValue);

	/**
	 * Destructor.
	 */
	~String();

	/**
	 * Joins all the strings into a single string each separated by the separator string.
	 *
	 * @param strings A list of strings to join.
	 * @param separator A string used to separate each of the joined strings.
	 * @return A single string consisting of the list of string joined together by the separator string.
	 */
	static String join(const StringList& strings, const String& separator);

	/**
	 * Appends the given string onto the end of this string.
	 *
	 * @param appendString The string to add.
	 * @return A reference to the modified string.
	 */
	String& append(const String& appendString);

	/**
	 * Appends the given string onto the end of this string.
	 *
	 * @param appendString The c string to add.
	 * @return A reference to the modified string.
	 */
	String& append(const char* appendString);

	/**
	 * Creates a copy of this string with the lowest numbered marker replaced by a1.
	 *
	 * Here is a small example demonstrating how to use this method:
	 *
	 * @code
	 *   bump::String example("Copying files %1 of %2: %3");
	 *   bump::String replaced = example.arg(1).arg(10).arg(test.txt);
	 *   // replaced = "Copying files 1 of 10: test.txt"
	 * @endcode
	 *
	 * @throw bump::StringSearchError When no valid valid markers are found (i.e. %1-%99).
	 *
	 * @param a1 A string to replace the lowest numbered marker.
	 * @return A copy of the string with the lowest numbered marker replaced.
	 */
	String arg(const String& a1) const;

	/**
	 * Creates a copy of this string with the two lowest numbered markers replaced by a1 and a2.
	 *
	 * This is the same as the following:
	 *
	 * @code
	 *   str.arg(a1).arg(a2);
	 * @endcode
	 *
	 * Here is a small example demonstrating how to use this method:
	 *
	 * @code
	 *   bump::String example("Copying files %1 of %2");
	 *   bump::String replaced = example.arg(1, 10);
	 *   // replaced = "Copying files 1 of 10"
	 * @endcode
	 *
	 * @throw bump::StringSearchError When no valid valid markers are found (i.e. %1-%99).
	 *
	 * @param a1 A string to replace the lowest numbered marker.
	 * @param a2 A string to replace the second lowest numbered marker.
	 * @return A copy of the string with the two lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2) const;

	/**
	 * Creates a copy of this string with the three lowest numbered markers replaced by a1, a2 and a3.
	 *
	 * This is the same as the following:
	 *
	 * @code
	 *   str.arg(a1).arg(a2).arg(a3);
	 * @endcode
	 *
	 * @throw bump::StringSearchError When no valid valid markers are found (i.e. %1-%99).
	 *
	 * @param a1 a string to replace the lowest numbered marker.
	 * @param a2 a string to replace the second lowest numbered marker.
	 * @param a3 a string to replace the third lowest numbered marker.
	 * @return a copy of the string with the three lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3) const;

	/**
	 * Creates a copy of this string with the four lowest numbered markers replaced.
	 *
	 * This is the same as the following:
	 *
	 * @code
	 *   str.arg(a1).arg(a2).arg(a3).arg(a4);
	 * @endcode
	 *
	 * @throw bump::StringSearchError When no valid valid markers are found (i.e. %1-%99).
	 *
	 * @param a1 a string to replace the lowest numbered marker.
	 * @param a2 a string to replace the second lowest numbered marker.
	 * @param a3 a string to replace the third lowest numbered marker.
	 * @param a4 a string to replace the fourth lowest numbered marker.
	 * @return a copy of the string with the four lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4) const;

	/**
	 * Creates a copy of this string with the five lowest numbered markers replaced.
	 *
	 * This is the same as the following:
	 *
	 * @code
	 *   str.arg(a1).arg(a2).arg(a3).arg(a4).arg(a5);
	 * @endcode
	 *
	 * @throw bump::StringSearchError When no valid valid markers are found (i.e. %1-%99).
	 *
	 * @param a1 a string to replace the lowest numbered marker.
	 * @param a2 a string to replace the second lowest numbered marker.
	 * @param a3 a string to replace the third lowest numbered marker.
	 * @param a4 a string to replace the fourth lowest numbered marker.
	 * @param a5 a string to replace the fifth lowest numbered marker.
	 * @return a copy of the string with the five lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5) const;

	/**
	 * Creates a copy of this string with the six lowest numbered markers replaced.
	 *
	 * This is the same as the following:
	 *
	 * @code
	 *   str.arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6);
	 * @endcode
	 *
	 * @throw bump::StringSearchError When no valid valid markers are found (i.e. %1-%99).
	 *
	 * @param a1 a string to replace the lowest numbered marker.
	 * @param a2 a string to replace the second lowest numbered marker.
	 * @param a3 a string to replace the third lowest numbered marker.
	 * @param a4 a string to replace the fourth lowest numbered marker.
	 * @param a5 a string to replace the fifth lowest numbered marker.
	 * @param a6 a string to replace the sixth lowest numbered marker.
	 * @return a copy of the string with the six lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
			   const String& a6) const;

	/**
	 * Creates a copy of this string with the seven lowest numbered markers replaced.
	 *
	 * This is the same as the following:
	 *
	 * @code
	 *   str.arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7);
	 * @endcode
	 *
	 * @throw bump::StringSearchError When no valid valid markers are found (i.e. %1-%99).
	 *
	 * @param a1 a string to replace the lowest numbered marker.
	 * @param a2 a string to replace the second lowest numbered marker.
	 * @param a3 a string to replace the third lowest numbered marker.
	 * @param a4 a string to replace the fourth lowest numbered marker.
	 * @param a5 a string to replace the fifth lowest numbered marker.
	 * @param a6 a string to replace the sixth lowest numbered marker.
	 * @param a7 a string to replace the seventh lowest numbered marker.
	 * @return a copy of the string with the seven lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
			   const String& a6, const String& a7) const;

	/**
	 * Creates a copy of this string with the eight lowest numbered markers replaced.
	 *
	 * This is the same as the following:
	 *
	 * @code
	 *   str.arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7).arg(a8);
	 * @endcode
	 *
	 * @throw bump::StringSearchError When no valid valid markers are found (i.e. %1-%99).
	 *
	 * @param a1 a string to replace the lowest numbered marker.
	 * @param a2 a string to replace the second lowest numbered marker.
	 * @param a3 a string to replace the third lowest numbered marker.
	 * @param a4 a string to replace the fourth lowest numbered marker.
	 * @param a5 a string to replace the fifth lowest numbered marker.
	 * @param a6 a string to replace the sixth lowest numbered marker.
	 * @param a7 a string to replace the seventh lowest numbered marker.
	 * @param a8 a string to replace the eighth lowest numbered marker.
	 * @return a copy of the string with the eight lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
			   const String& a6, const String& a7, const String& a8) const;

	/**
	 * Creates a copy of this string with the nine lowest numbered markers replaced.
	 *
	 * This is the same as the following:
	 *
	 * @code
	 *   str.arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7).arg(a8).arg(a9);
	 * @endcode
	 *
	 * @throw bump::StringSearchError When no valid valid markers are found (i.e. %1-%99).
	 *
	 * @param a1 a string to replace the lowest numbered marker.
	 * @param a2 a string to replace the second lowest numbered marker.
	 * @param a3 a string to replace the third lowest numbered marker.
	 * @param a4 a string to replace the fourth lowest numbered marker.
	 * @param a5 a string to replace the fifth lowest numbered marker.
	 * @param a6 a string to replace the sixth lowest numbered marker.
	 * @param a7 a string to replace the seventh lowest numbered marker.
	 * @param a8 a string to replace the eighth lowest numbered marker.
	 * @param a9 a string to replace the ninth lowest numbered marker.
	 * @return a copy of the string with the nine lowest numbered markers replaced.
	 */
	String arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
			   const String& a6, const String& a7, const String& a8, const String& a9) const;

	/**
	 * Locates and returns the character at the position in this string.
	 *
	 * @throw bump::OutOfRangeError When position is outside this string's bounds.
	 *
	 * @param position The position of the character to return of this string.
	 * @return The character at the given position.
	 */
	const char& at(int position) const;

	/**
	 * Converts the string to a c string.
	 *
	 * @return The c string representation of the string.
	 */
	const char* c_str() const;

	/**
	 * Capitalizes the first letter of this string.
	 *
	 * @return A reference to the modified string.
	 */
	String& capitalize();

	/**
	 * Chops the specified number of characters off from the end of this string.
	 *
	 * If n is greater than the string's length, the result is an empty string.
	 *
	 * @param n The number of characters to chop off the end of this string.
	 * @return The modified version of this string.
	 */
	String& chop(unsigned int n);

	/**
	 * Clears the contents of the string making it empty.
	 */
	void clear();

	/**
	 * Compares the content of the this string with the given string.
	 *
	 * @param otherString The string to compare content against with this string.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return Whether the content within both objects is the same.
	 */
	bool compare(const String& otherString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Compares the content of the this string with the given string.
	 *
	 * @param otherString The const char* to compare content against with this string.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return Whether the content within both objects is the same.
	 */
	bool compare(const char* otherString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Finds out whether this string contains an occurrence of the given string.
	 *
	 * @param containString The String to see if is contained within this string.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return True if the string contains an occurrence of containString, otherwise returns false.
	 */
	bool contains(const String& containString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Finds out whether this string contains an occurrence of the given string.
	 *
	 * @param containString The const char* to see if is contained within this string.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return True if the string contains an occurrence of containString, otherwise returns false.
	 */
	bool contains(const char* containString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Counts the number of (potentially overlapping) occurrences of the given string in this string.
	 *
	 * @param containString The tring to see if is contained within this string.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return The number of occurrences of the given string in this string.
	 */
	int count(const String& containString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Counts the number of (potentially overlapping) occurrences of the given string in this string.
	 *
	 * @param containString The const char* to see if is contained within this string.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return The number of occurrences of the given string in this string.
	 */
	int count(const char* containString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Returns a pointer to an array of characters without appending a terminating null character.
	 *
	 * @return A pointer to an array of characters without appending a terminating null character.
	 */
	const char* data() const;

	/**
	 * Checks whether this string ends with the given string.
	 *
	 * @param endString The string to check if this string ends with.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return True if this string ends with endString, otherwise returns false.
	 */
	bool endsWith(const String& endString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Checks whether this string ends with the given string.
	 *
	 * @param endString The const char* to check if this string ends with.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return True if this string ends with endString, otherwise returns false.
	 */
	bool endsWith(const char* endString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Sets every character in the string to character. If size is different from -1 (default),
	 * the string is resized to size beforehand.
	 *
	 * @throw bump::InvalidArgumentError When passed a character string with length not equal to one.
	 * @throw bump::InvalidArgumentError When passed a size less than -1.
	 *
	 * @param character The character to fill this string with.
	 * @param size The size to resize this string to be filling.
	 * @return A reference to the modified string.
	 */
	String& fill(const String& character, int size = -1);

	/**
	 * Finds the position of the first occurrence of indexString in this string by searching
	 * forward from the startPosition.
	 *
	 * @throw bump::InvalidArgumentError When passed an empty index string.
	 *
	 * @param indexString The String to find the first occurence of in this string.
	 * @param startPosition The index of the string to start searching at.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return The position of the first occurrence of indexString, defaults to -1 if not found.
	 */
	int indexOf(const String& indexString, int startPosition = 0, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Finds the position of the first occurrence of indexString in this string by searching
	 * forward from the startPosition.
	 *
	 * @throw bump::InvalidArgumentError When passed an empty index string.
	 *
	 * @param indexString The const char* to find the first occurence of in this string.
	 * @param startPosition The index of the string to start searching at.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return The position of the first occurrence of indexString, defaults to -1 if not found.
	 */
	int indexOf(const char* indexString, int startPosition = 0, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Inserts the insertString at the given position.
	 *
	 * @throw bump::InvalidArgumentError When passed an empty insert string.
	 * @throw bump::OutOfRangeError When position is outside this string's bounds.
	 *
	 * @param position The index position of the string to start inserting at.
	 * @param insertString The String to insert at the given index position in this string.
	 * @return A reference to the modified string.
	 */
	String& insert(const String& insertString, int position);

	/**
	 * Inserts the insertString at the given position.
	 *
	 * @param position The index position of the string to start inserting at.
	 * @param insertString The const char* to insert at the given index position in this string.
	 * @return A reference to the modified string.
	 */
	String& insert(const char* insertString, int position);

	/**
	 * Determines whether the string has any characters.
	 *
	 * @return True if the string has no characters, otherwise returns false.
	 */
	bool isEmpty() const;

	/**
	 * Determines whether the string is any kind of number (int, float, double, scientific).
	 *
	 * @return Whether the string is a valid number (int, float, double, scientific).
	 */
	bool isNumber() const;

	/**
	 * Finds the position of the last occurrence of indexString in this string by searching
	 * backwards from the startPosition. If startPosition is -1 (default), the search starts
	 * at the last character.
	 *
	 * @throw bump::InvalidArgumentError When passed an empty index string.
	 *
	 * @param indexString The string to find the last occurence of in this string.
	 * @param startPosition The index of the string to start searching at.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return The position of the last occurrence of indexString, defaults to -1 if not found.
	 */
	int lastIndexOf(String indexString, int startPosition = -1, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Finds the position of the last occurrence of indexString in this string by searching
	 * backwards from the startPosition. If startPosition is -1 (default), the search starts
	 * at the last character.
	 *
	 * @throw bump::InvalidArgumentError When passed an empty index string.
	 *
	 * @param indexString The const char* to find the last occurence of in this string.
	 * @param startPosition The index of the string to start searching at.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return The position of the last occurrence of indexString, defaults to -1 if not found.
	 */
	int lastIndexOf(const char* indexString, int startPosition = -1, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Finds the substring that contains the number of leftmost characters of this string.
	 *
	 * @throw bump::OutOfRangeError When n is outside this string's bounds.
	 *
	 * @param n The number of characters to return.
	 * @return The substring of the leftmost number of characters of this string.
	 */
	String left(int n) const;

	/**
	 * Computes the total number of characters in this string.
	 *
	 * @return The total number of characters in this string.
	 */
	int length() const;

	/**
	 * Adds the given string to the beginning of this string.
	 *
	 * @param prependString The string to add to the beginning of this string.
	 * @return The modified version of this string.
	 */
	String& prepend(const String& prependString);

	/**
	 * Adds the given string to the beginning of this string.
	 *
	 * @param prependString The const char* to add to the beginning of this string.
	 * @return The modified version of this string.
	 */
	String& prepend(const char* prependString);

	/**
	 * Removes the given width of characters starting at the given position.
	 *
	 * @throw bump::OutOfRangeError When position is outside this string's bounds.
	 * @throw bump::InvalidArgumentError When n is negative.
	 *
	 * @param position The index position to start removing characters at from this string.
	 * @param n The number of characters to remove from this string.
	 * @return The modified version of this string.
	 */
	String& remove(int position, int n);

	/**
	 * Removes every occurrence of the given in this string.
	 *
	 * @throw bump::InvalidArgumentError When the remove string is empty.
	 *
	 * @param removeString The string to remove from this string.
	 * @param caseSensitivity The case sensitivity to be used, defaults to String::CaseSensitive.
	 * @return The modified version of this string.
	 */
	String& remove(const String& removeString, CaseSensitivity caseSensitivity = CaseSensitive);

	/**
	 * Removes every occurrence of the given in this string.
	 *
	 * @throw bump::InvalidArgumentError When the remove string is empty.
	 *
	 * @param removeString The const char* to remove from this string.
	 * @param caseSensitivity The case sensitivity to be used, defaults to String::CaseSensitive.
	 * @return The modified version of this string.
	 */
	String& remove(const char* removeString, CaseSensitivity caseSensitivity = CaseSensitive);

	/**
	 * Generates a new string repeated the specified number of times.
	 *
	 * Passing a value of zero will return an empty string.
	 *
	 * @param times The number of times the new string will be repeated.
	 * @return A new string repeated the specified number of times.
	 */
	String repeated(unsigned int times) const;

	/**
	 * Replaces n characters starting at position with the replace string.
	 *
	 * @throw bump::OutOfRangeError When position is outside this string's bounds.
	 * @throw bump::InvalidArgumentError When n is negative.
	 *
	 * @param position The index of this string to start replacing at.
	 * @param n The number of characters to replace in this string.
	 * @param replaceString The string to replace the n characters in this string.
	 * @return The modified version of this string.
	 */
	String& replace(int position, int n, const String& replaceString);

	/**
	 * Replaces n characters starting at position with the replace string.
	 *
	 * @throw bump::OutOfRangeError When position is outside this string's bounds.
	 * @throw bump::InvalidArgumentError When n is negative.
	 *
	 * @param position The index of this string to start replacing at.
	 * @param n The number of characters to replace in this string.
	 * @param replaceString The const char* to replace the n characters in this string.
	 * @return The modified version of this string.
	 */
	String& replace(int position, int n, const char* replaceString);

	/**
	 * Replaces every occurrence of the before string with the after string.
	 *
	 * @throw bump::InvalidArgumentError When passed an empty before string.
	 *
	 * @param before The string to be replaced.
	 * @param after The string to replace the before string.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return The modified version of this string.
	 */
	String& replace(const String& before, const String& after, CaseSensitivity caseSensitivity = CaseSensitive);

	/**
	 * Replaces every occurrence of the before string with the after string.
	 *
	 * @throw bump::InvalidArgumentError When passed an empty before string.
	 *
	 * @param before The const char* to be replaced.
	 * @param after The const char* to replace the before string.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return The modified version of this string.
	 */
	String& replace(const char* before, const char* after, CaseSensitivity caseSensitivity = CaseSensitive);

	/**
	 * Finds the substring that contains the number of rightmost characters of this string.
	 *
	 * @throw bump::OutOfRangeError When n is outside this string's bounds.
	 *
	 * @param n The number of characters to return.
	 * @return The substring of the rightmost number of characters of this string.
	 */
	String right(int n) const;

	/**
	 * Creates a substring of the given length beginning at the start position.
	 *
	 * @throw bump::OutOfRangeError When position is outside this string's bounds.
	 * @throw bump::InvalidArgumentError When length is less than one.
	 *
	 * @param startPosition The starting position in this string to begin the section.
	 * @param length The length of the section to extract from the string.
	 * @return A section of the string beginning at the start position with the given length.
	 */
	String section(int startPosition, int length = -1) const;

	/**
	 * Splits the string into a list of string that were separated by the given separator string.
	 *
	 * @param separator A string used to split the string into a list of strings.
	 * @return A list of strings separated by the separator character.
	 */
	StringList split(const String& separator) const;

	/**
	 * Checks whether this string starts with the given string.
	 *
	 * @param startString The string to check if this string starts with.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return True if this string starts with startString, otherwise returns false.
	 */
	bool startsWith(const String& startString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Checks whether this string starts with the given string.
	 *
	 * @param startString The const char* to check if this string starts with.
	 * @param caseSensitivity The case sensitivity to be used, defaults to CaseSensitive.
	 * @return True if this string starts with startString, otherwise returns false.
	 */
	bool startsWith(const char* startString, CaseSensitivity caseSensitivity = CaseSensitive) const;

	/**
	 * Capitalizes all the first letters of each word in the string.
	 *
	 * @return A new string with all the first letters of each word capitalized.
	 */
	String title() const;

	/**
	 * Converts this string to a boolean.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to a boolean.
	 *
	 * @return The bool value of the string.
	 */
	bool toBool() const;

	/**
	 * Converts this string to a double.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to a double.
	 *
	 * @return The double value of the string.
	 */
	double toDouble() const;

	/**
	 * Converts this string to a float.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to a float.
	 *
	 * @return The float value of the string.
	 */
	float toFloat() const;

	/**
	 * Converts this string to an int.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to an int.
	 *
	 * @return The int value of the string.
	 */
	int toInt() const;

	/**
	 * Converts this string to a long.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to a long.
	 *
	 * @return The long value of the string.
	 */
	long toLong() const;

	/**
	 * Converts this string to a long long.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to a long long.
	 *
	 * @return The long long value of the string.
	 */
	long long toLongLong() const;

	/**
	 * Converts this string to all lowercase text.
	 *
	 * @return The modified version of this string.
	 */
	String& toLowerCase();

	/**
	 * Converts this string to a short.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to a short.
	 *
	 * @return The short value of the string.
	 */
	short toShort() const;

	/**
	 * Converts the string to a std::string.
	 *
	 * @return The std::string representation of the string.
	 */
	std::string toStdString() const;

	/**
	 * Converts this string to an unsigned int.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to an unsigned int.
	 *
	 * @return The unsigned int value of the string.
	 */
	unsigned int toUInt() const;

	/**
	 * Converts this string to an unsigned long.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to an unsigned long.
	 *
	 * @return The unsigned long value of the string.
	 */
	unsigned long toULong() const;

	/**
	 * Converts this string to an unsigned long long.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to an unsigned long long.
	 *
	 * @return The unsigned long long value of the string.
	 */
	unsigned long long toULongLong() const;

	/**
	 * Converts this string to all uppercase text.
	 *
	 * @return The modified version of this string.
	 */
	String& toUpperCase();

	/**
	 * Converts this string to an unsigned short.
	 *
	 * @throw bump::TypeCastError When this string cannot be converted to an unsigned short.
	 *
	 * @return The unsigned short value of the string.
	 */
	unsigned short toUShort() const;

	/**
	 * Generates a string that has all whitespace removed from the start and end.
	 *
	 * Whitespace characters are " ", "\t", "\n", "\v", "\f" and "\r".
	 *
	 * @return A new string that has all whitespace removed from the start and end.
	 */
	String trimmed() const;

	/**
	 * Appends the string onto the end of this string.
	 *
	 * @param appendString The string to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (const String& appendString);

	/**
	 * Appends the string onto the end of this string.
	 *
	 * @param appendString The const char* to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (const char* appendString);

	/**
	 * Appends the unsigned char to the end of this string.
	 *
	 * @param appendChar The unsigned char to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (unsigned char appendChar);

	/**
	 * Appends the char to the end of this string.
	 *
	 * @param appendChar The char to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (char appendChar);

	/**
	 * Appends the unsigned short to the end of this string.
	 *
	 * @param appendShort The unsigned short to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (unsigned short appendShort);

	/**
	 * Appends the short to the end of this string.
	 *
	 * @param appendShort The short to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (short appendShort);

	/**
	 * Appends the unsigned int to the end of this string.
	 *
	 * @param appendInt The unsigned int to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (unsigned int appendInt);

	/**
	 * Appends the int to the end of this string.
	 *
	 * @param appendInt The int to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (int appendInt);

	/**
	 * Appends the unsigned long to the end of this string.
	 *
	 * @param appendLong The unsigned long to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (unsigned long appendLong);

	/**
	 * Appends the long to the end of this string.
	 *
	 * @param appendLong The long to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (long appendLong);

	/**
	 * Appends the unsigned long long to the end of this string.
	 *
	 * @param appendLongLong The unsigned long long to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (unsigned long long appendLongLong);

	/**
	 * Appends the long long to the end of this string.
	 *
	 * @param appendLongLong The long long to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (long long appendLongLong);

	/**
	 * Appends the float to the end of this string.
	 *
	 * @param appendFloat The float to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (float appendFloat);

	/**
	 * Appends the double to the end of this string.
	 *
	 * @param appendDouble The float to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (double appendDouble);

	/**
	 * Appends the bool to the end of this string.
	 *
	 * @param appendBool The bool to append onto this string.
	 * @return The modified version of this string.
	 */
	String& operator << (bool appendBool);
};

}	// End of bump namespace

#endif	// End of BUMP_STRING_H
