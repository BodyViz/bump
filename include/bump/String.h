//
//  String.h
//  Bump
//
//  Created by Christian Noon on 11/7/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_STRING_H
#define BUMP_STRING_H

// C++ headers
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

// Boost headers
#include <boost/lexical_cast.hpp>

namespace bump {

/**
 * A string class which adds lots of useful string methods ontop of the std::string class. These
 * methods range from custom print methods for many different types of objects as well as string
 * methods common in both Python and Objective-C. This class was developed to eliminate the pain
 * of string parsing by implementing a much more straight forward syntax to make development much
 * easier and less time consuming.
 */
class String : public std::string
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
     */
    String(const char* c_string);

    /**
     * Constructor that takes a std::string.
     */
    String(const std::string& std_string);

    /**
     * Constructor that takes an unsigned char.
     */
    String(unsigned char number);

    /**
     * Constructor that takes a char.
     */
    String(char number);

    /**
     * Constructor that takes an unsigned short.
     */
    String(unsigned short number);

    /**
     * Constructor that takes a short.
     */
    String(short number);

    /**
     * Constructor that takes an unsigned int.
     */
    String(unsigned int number);

    /**
     * Constructor that takes an int.
     */
    String(int number);

    /**
     * Constructor that takes an unsigned long.
     */
    String(unsigned long number);

    /**
     * Constructor that takes a long.
     */
    String(long number);

    /**
     * Constructor that takes a float.
     */
    String(float number, unsigned int precision = 3);

    /**
     * Constructor that takes a double.
     */
    String(double number, unsigned int precision = 3);

    /**
     * Constructor that takes a bool.
     */
    String(bool boolValue);

    /**
     * Returns a string joined between path and fname with a forward or back slash
     * depending on the operating system.
     *
     * @param path - the file path.
     * @param fname - the file name.
     */
    static String join(String path, String fname);

    /**
     * Returns a string joined by a forward or backslash between all the elements
     * of the string vector.
     *
     * @param strings - the strings to join together.
     */
    static String joinVector(std::vector<String> strings);

    /**
     * Appends the string append_string onto the end of this string.
     *
     * @param append_string - the String to add.
     */
    void append(const String& append_string);

    /**
     * Appends the const char* append_char onto the end of this string.
     *
     * @param append_string - the String to add.
     */
    void append(const char* append_char);

    /**
     * Returns the character at the given index position in this string.
     *
     * @param position - the position of the character to return of this string.
     */
    char& at(int position);

    /**
     * Returns a c string.
     */
    const char* c_str();

    /**
     * Returns a c string.
     */
    const char* c_str() const;

    /**
     * Capitalizes the first letter of this string.
     */
    void capitalize();

    /**
     * Clears the contents of the string and makes it empty.
     */
    void clear();

    /**
     * Compares the content of this string with the String str.
     *
     * Returns whether or not the content within both objects is the same.
     *
     * @param str - the string to compare content against with this string.
     */
    bool compare(const String& str) const;

    /**
     * Compares the content of this string with the const char* char_star.
     *
     * Returns whether or not the content within both objects is the same.
     *
     * @param char_star - the const char* to compare content against with this string.
     */
    bool compare(const char* char_star) const;

    /**
     * Returns true if this string contains an occurrence of the string str,
     * otherwise returns false.
     *
     * @param contain_string - the String to see if is contained within this string.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    bool contains(String contain_string, String::CaseSensitivity cs = String::CaseSensitive);

    /**
     * Returns true if this string contains an occurrence of the const char* contain_char,
     * otherwise returns false.
     *
     * @param contain_char - the const char* to see if is contained within this string.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    bool contains(const char* contain_char, String::CaseSensitivity cs = String::CaseSensitive);

    /**
     * Returns the number of (potentially overlapping) occurrences of the String
     * contain_string in this string.
     *
     * @param contain_string - the String to see if is contained within this string.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    int count(String contain_string, String::CaseSensitivity cs = String::CaseSensitive);

    /**
     * Returns the number of (potentially overlapping) occurrences of the const char*
     * contain_char in this string.
     *
     * @param contain_char - the const char* to see if is contained within this string.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    int count(const char* contain_char, String::CaseSensitivity cs = String::CaseSensitive);

    /**
     * Returns true if the string has no characters; otherwise returns false.
     *
     * Same as isEmpty() method.
     */
    bool empty() const;

    /**
     * Returns true if this string ends with end_string; otherwise returns false.
     *
     * @param end_string - the string to check if this string ends with.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    bool endsWith(String end_string, String::CaseSensitivity cs = String::CaseSensitive);

    /**
     * Returns true if this string ends with end_string; otherwise returns false.
     *
     * @param end_string - the string to check if this string ends with.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    bool endsWith(String end_string, String::CaseSensitivity cs = String::CaseSensitive) const;

    /**
     * Returns true if this string ends with end_char; otherwise returns false.
     *
     * @param end_char - the const char* to check if this string ends with.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    bool endsWith(const char* end_char, String::CaseSensitivity cs = String::CaseSensitive);

    /**
     * Returns true if this string ends with end_char; otherwise returns false.
     *
     * @param end_char - the const char* to check if this string ends with.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    bool endsWith(const char* end_char, String::CaseSensitivity cs = String::CaseSensitive) const;

    /**
     * Erases a part of the string content, shortening the length of this string.
     *
     * @param position - the index of this string to start erasing at.
     * @param width - the number of characters to erase from this string.
     */
    void erase(int position, int width);

    /**
     * Erases a part of the string content, shortening the length of this string.
     *
     * @param position - an iterator at the character index to remove from this string.
     */
    void erase(iterator position);

    /**
     * Erases a part of the string content, shortening the length of the string.
     *
     * @param first - an iterator at the character index to start removing from this string.
     * @param last - an iterator at the character index to stop removing from this string.
     */
    void erase(iterator first, iterator last);

    /**
     * Sets every character in the string to character ch. If size is different from -1 (default),
     * the string is resized to size beforehand.
     *
     * @param ch - the character to fill this string with.
     * @param size - the size to resize this string to be filling.
     */
    void fill(const char* ch, int size=-1);

    /**
     * Searches the string for the content specified in string str and returns the
     * position of the first occurrence in the string.
     *
     * @param str - the String to find the first occurence of in this string.
     * @param position - the index of the string to start searching at.
     */
    int find(const String& str, int position = 0);

    /**
     * Searches the string for the content specified in the const char* and returns the
     * position of the first occurrence in the string.
     *
     * @param char_star - the const char* to find the first occurence of in this string.
     * @param position - the index of the string to start searching at.
     */
    int find(const char* char_star, int position = 0);

    /**
     * Returns the index position of the first occurrence of the String index_string
     * in this string, searching forward from index position from. Returns -1 if
     * index_string is not found.
     *
     * @param index_string - the String to find the first occurence of in this string.
     * @param from - the index of the string to start searching at.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    int indexOf(String index_string, int from = 0, String::CaseSensitivity cs = String::CaseSensitive);

    /**
     * Returns the index position of the first occurrence of the const char* index_char
     * in this string, searching forward from index position from. Returns -1 if
     * index_char is not found.
     *
     * @param index_char - the const char* to find the first occurence of in this string.
     * @param from - the index of the string to start searching at.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    int indexOf(const char* index_char, int from = 0, String::CaseSensitivity cs = String::CaseSensitive);

    /**
     * Inserts the String insert_string at the given index position.
     *
     * @param position - the index position of the string to start inserting at.
     * @param insert_string - the String to insert at the given index position in this string.
     */
    void insert(int position, String insert_string);

    /**
     * Inserts the const char* insert_char at the given index position.
     *
     * @param position - the index position of the string to start inserting at.
     * @param insert_char - the const char* to insert at the given index position in this string.
     */
    void insert(int position, const char* insert_char);

    /**
     * Returns true if the string has no characters; otherwise returns false.
     *
     * Same as empty() method.
     */
    bool isEmpty();

    /**
     * Returns whether the string is a number.
     */
    bool isNumber();

    /**
     * Returns the index position of the last occurrence of the String index_string
     * in this string, searching backward from index position from. If from is -1 (default),
     * the search starts at the last character.
     *
     * @param index_string - the String to find the first occurence of in this string.
     * @param from - the index position of the string to start searching at.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    int lastIndexOf(String index_string, int from = -1, String::CaseSensitivity cs=String::CaseSensitive);

    /**
     * Returns the index position of the last occurrence of the const char* index_char
     * in this string, searching backward from index position from. If from is -1 (default),
     * the search starts at the last character.
     *
     * @param index_char - the const char* to find the first occurence of in this string.
     * @param from - the index position of the string to start searching at.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    int lastIndexOf(const char* index_char, int from = -1, String::CaseSensitivity cs=String::CaseSensitive);

    /**
     * Returns a substring that contains the num leftmost characters of the string.
     *
     * @param num - the number of characters to return.
     */
    String left(int num);

    /**
     * Returns the number of characters in this string. Equivalent to size().
     */
    int length();

	/**
	 * Pads the string with zeroes at the beginning until it reaches length.
	 */
	void padWithZeroes(unsigned int length);

    /**
     * Prepends the String prepend_string to the beginning of this string.
     *
     * @param prepend_string - the String to prepend to the beginning of this string.
     */
    void prepend(const String& prepend_string);

    /**
     * Prepends the const char* prepend_string to the beginning of this string.
     *
     * @param prepend_char - the const char* to prepend to the beginning of this string.
     */
    void prepend(const char* prepend_char);

    /**
     * Prints this string.
     */
    void print();

    /**
     * Removes n characters from the string, starting at the given position index..
     *
     * @param position - the index position to start removing characters at from this string.
     * @param width - the number of characters to remove from this string.
     */
    void remove(int position, int width);

    /**
     * Removes every occurrence of the given String remove_string in this string.
     *
     * @param remove_string - the String to remove from this string.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    void remove(String remove_string, String::CaseSensitivity cs=String::CaseSensitive);

    /**
     * Removes every occurrence of the given const char* remove_char in this string.
     *
     * @param remove_char - the const char* to remove from this string.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    void remove(const char* remove_char, String::CaseSensitivity cs=String::CaseSensitive);

    /**
     * Replaces width characters beginning at the index position in this string with
     * the String replace_string.
     *
     * @param position - the index of this string to start replacing at.
     * @param width - the number of characters to replace in this string.
     * @param replace_string - the String to replace the width characters in this string.
     */
    void replace(int position, int width, const String& replace_string);

    /**
     * Replaces width characters beginning at the index position in this string with
     * the const char* replace_char.
     *
     * @param position - the index of this string to start replacing at.
     * @param width - the number of characters to replace in this string.
     * @param replace_char - the const char* to replace the width characters in this string.
     */
    void replace(int position, int width, const char* replace_char);

    /**
     * Replaces every occurrence of the String before_string with the String after_string.
     *
     * @param before_string - the String to be replaced in this string.
     * @param after_string - the String to replace the before_string in this string.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    void replace(String before_string, String after_string, String::CaseSensitivity cs=String::CaseSensitive);

    /**
     * Replaces every occurrence of the const char* before_char with the const char* after_char.
     *
     * @param before_char - the const char* to be replaced in this string.
     * @param after_char - the const char* to replace the before_string in this string.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    void replace(const char* before_char, const char* after_char, String::CaseSensitivity cs=String::CaseSensitive);

    /**
     * Resizes this string content to n characters.
     *
     * If n is smaller than the current length of the string, the content is reduced to its first
     * n characters, the rest being dropped.
     *
     * @param n - the number of characters to resize this string to.
     */
    void resize(int n);

    /**
     * Resizes this string content to n characters.
     *
     * If n is smaller than the current length of the string, the content is reduced to its first
     * n characters, the rest being dropped.
     *
     * If n is greater than the current length of the string, the content is expanded by appending
     * as many instances of the const char* c as needed to reach a size of n characters.
     *
     * @param n - the number of characters to resize this string to.
     */
    void resize(int n, const char* c);

    /**
     * Searches this string for the content specified in String str and returns the
     * position of the last occurrence in the string.
     *
     * @param str - the String to find in this string.
     */
    int rfind(const String& str);

    /**
     * Searches this string for the content specified in const char* char_star and returns the
     * position of the last occurrence in the string.
     *
     * @param char_star - the const char* to find in this string.
     */
    int rfind(const char* char_star);

    /**
     * Returns a substring that contains the num rightmost characters of the string.
     *
     * @param num - the number of characters to return.
     */
    String right(int num);

    /**
     * Returns a section of the string between start and end positions.
     *
     * @param start - the index position to start the section at in this string.
     * @param length - the length of the section to extract from the string.
     */
    String section(int start, int length = -1);

    /**
     * Returns the number of characters in this string.
     */
    int size();

    /**
     * Returns a vector of strings that were separated by the given character.
     *
     * @param sep - the const char* used to separate all the Strings in this string.
     */
    std::vector<String> split(const char* sep);

    /**
     * Returns true if this string starts with start_string; otherwise returns false.
     *
     * @param start_string - the String used to see if this string starts with
     * the same characters.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    bool startsWith(String start_string, String::CaseSensitivity cs=String::CaseSensitive);

    /**
     * Returns true if this string starts with start_string; otherwise returns false.
     *
     * @param start_string - the String used to see if this string starts with
     * the same characters.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    bool startsWith(String start_string, String::CaseSensitivity cs=String::CaseSensitive) const;

    /**
     * Returns true if this string starts with start_char; otherwise returns false.
     *
     * @param start_char - the const char* used to see if this string starts
     * with the same characters.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    bool startsWith(const char* start_char, String::CaseSensitivity cs=String::CaseSensitive);

    /**
     * Returns true if this string starts with start_char; otherwise returns false.
     *
     * @param start_char - the const char* used to see if this string starts
     * with the same characters.
     * @param cs - the case sensitivity to be used, defaults to String::CaseSensitive.
     */
    bool startsWith(const char* start_char, String::CaseSensitivity cs=String::CaseSensitive) const;

    /**
     * Return the part of the string between the indices from and to.
     *
     * @param start - the index position to start the section at in this string.
     * @param length - the length of the section to extract from the string.
     */
    String substr(int start, int length);

    /**
     * Return the part of the string between the indices from and to.
     *
     * @param start - the index position to start the section at in this string.
     * @param length - the length of the section to extract from the string.
     */
    String subString(int start, int length);

    /**
     * Converts this string to a boolean.
     */
    bool toBool();

    /**
     * Converts this string to a double.
     */
    double toDouble();

    /**
     * Converts this string to a float.
     */
    float toFloat();

    /**
     * Converts this string to an int.
     */
    int toInt();

    /**
     * Converts this string to all lowercase text.
     */
    void toLowerCase();

    /**
     * Returns a std::string object with the data contained in this String.
     */
    std::string toStdString();

    /**
     * Converts this string to all uppercase text.
     */
    void toUpperCase();

    /**
     * Appends the String append_string onto the end of this string.
     *
     * @param append_string - the String to add.
     */
    String& operator << (const String& append_string);

	/**
	 * Appends the const char* to the end of the string.
	 *
	 * @param append_char_array - the const char* to add to the original String
	 */
	String& operator << (const char* append_char_array);

	/**
	 * Appends the unsigned char to the end of the string.
	 *
	 * @param rhs - the char short to add to the original String
	 */
	String& operator << (unsigned char append_char);

	/**
	 * Appends the char to the end of the string.
	 *
	 * @param append_char - the char to add to the original String
	 */
	String& operator << (char append_char);

	/**
	 * Appends the unsigned short to the end of the string.
	 *
	 * @param append_short - the unsigned short to add to the original String
	 */
	String& operator << (unsigned short append_short);

	/**
	 * Appends the short to the end of the string.
	 *
	 * @param append_short - the short to add to the original String
	 */
	String& operator << (short append_short);

	/**
	 * Appends the unsigned int to the end of the string.
	 *
	 * @param append_int - the unsigned int to add to the original String
	 */
	String& operator << (unsigned int append_int);

	/**
	 * Appends the int to the end of the string.
	 *
	 * @param append_int - the int to add to the original String
	 */
	String& operator << (int append_int);

	/**
	 * Appends the unsigned long to the end of the string.
	 *
	 * @param append_long - the unsigned long to add to the original String
	 */
	String& operator << (unsigned long append_long);

	/**
	 * Appends the long to the end of the string.
	 *
	 * @param append_long - the long to add to the original String
	 */
	String& operator << (long append_long);

	/**
	 * Appends the float to the end of the string.
	 *
	 * @param append_float - the float to add to the original String
	 */
	String& operator << (float append_float);

	/**
	 * Appends the double to the end of the string.
	 *
	 * @param append_double - the double to add to the original String
	 */
	String& operator << (double append_double);

	/**
	 * Appends the bool to the end of the string.
	 *
	 * @param append_bool - the bool to add to the original String
	 */
	String& operator << (bool append_bool);
};

// Typedefs
typedef std::vector<bump::String> StringList;

}   // End of bump namespace

#endif  // End of BUMP_STRING_H
