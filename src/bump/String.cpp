//
//	String.cpp
//	Bump
//
//	Created by Christian Noon on 11/7/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// C++ headers
#include <iomanip>
#include <limits>
#include <sstream>

// Boost headers
#include <boost/lexical_cast.hpp>

// Bump headers
#include <bump/Exception.h>
#include <bump/String.h>

using namespace bump;

String::String() : std::string()
{
	;
}

String::String(const char* cString) : std::string(cString)
{
	;
}

String::String(const std::string& stdString) : std::string(stdString)
{
	;
}

String::String(unsigned char number)
{
	int value = (int)number;
	*this = boost::lexical_cast<std::string>(value);
}

String::String(char number)
{
	int value = (int)number;
	*this = boost::lexical_cast<std::string>(value);
}

String::String(unsigned short number)
{
	int value = (int)number;
	*this = boost::lexical_cast<std::string>(value);
}

String::String(short number)
{
	int value = (int)number;
	*this = boost::lexical_cast<std::string>(value);
}

String::String(unsigned int number)
{
	*this = boost::lexical_cast<std::string>(number);
}

String::String(int number)
{
	*this = boost::lexical_cast<std::string>(number);
}

String::String(unsigned long number)
{
	*this = boost::lexical_cast<std::string>(number);
}

String::String(long number)
{
	*this = boost::lexical_cast<std::string>(number);
}

String::String(unsigned long long number)
{
	*this = boost::lexical_cast<std::string>(number);
}

String::String(long long number)
{
	*this = boost::lexical_cast<std::string>(number);
}

String::String(float number, int precision)
{
	// Make sure the precision is not less than -1
	if (precision < -1)
	{
		throw InvalidArgumentError("bump::String::String(float) cannot handle a precision less than -1");
	}

	// Convert the float to the proper precision using an ostringstream
	std::ostringstream result;
	if (precision == -1)
	{
		result << std::setprecision(std::numeric_limits<float>::digits10 + 1) << number;
	}
	else
	{
		result.setf(std::ios::fixed, std::ios::floatfield);
		result << std::setprecision(precision) << number;
	}

	*this = result.str();
}

String::String(double number, int precision)
{
	// Make sure the precision is not less than -1
	if (precision < -1)
	{
		throw InvalidArgumentError("bump::String::String(double) cannot handle a precision less than -1");
	}

	// Convert the double to the proper precision using an ostringstream
	std::ostringstream result;

	if (precision == -1)
	{
		result << std::setprecision(std::numeric_limits<double>::digits10 + 1) << number;
	}
	else
	{
		result.setf(std::ios::fixed, std::ios::floatfield);
		result << std::setprecision(precision) << number;
	}

	*this = result.str();
}

String::String(bool boolValue)
{
	*this = boolValue == true ? String("true") : String("false");
}

String::~String()
{
	;
}

String& String::append(const String& appendString)
{
	*this += appendString;
	return *this;
}

String& String::append(const char* appendString)
{
	*this += appendString;
	return *this;
}

const char String::at(int position) const
{
	try
	{
		return std::string::at(position);
	}
	catch (const std::out_of_range& e)
	{
		throw OutOfRangeError("bump::String::at() position is outside string bounds");
	}
}

const char* String::c_str() const
{
	return std::string::c_str();
}

String& String::capitalize()
{
	if (!isEmpty())
	{
		(*this)[0] = toupper(at(0));
	}

	return *this;
}

void String::clear()
{
	std::string::clear();
}

bool String::compare(const String& otherString) const
{
	if (std::string::compare(otherString) == 0)
	{
		return true;
	}

	return false;
}

bool String::compare(const char* otherString) const
{
	if (std::string::compare(otherString) == 0)
	{
		return true;
	}

	return false;
}

bool String::contains(const String& containString, CaseSensitivity caseSensitivity) const
{
	// Make some copies to handle case sensitivity
	String this_copy = *this;
	String contain_string_copy = containString;

	// Adjust if not case sensitive
	if (caseSensitivity == NotCaseSensitive)
	{
		this_copy.toLowerCase();
		contain_string_copy.toLowerCase();
	}

	// Try to find the contain string in this string
	size_t found = this_copy.find(contain_string_copy);
	if (found != std::string::npos)
	{
		return true;
	}

	return false;
}

bool String::contains(const char* containString, CaseSensitivity caseSensitivity) const
{
	return contains(String(containString), caseSensitivity);
}

int String::count(const String& containString, CaseSensitivity caseSensitivity) const
{
	// Make some copies to handle case sensitivity
	String this_copy = *this;
	String contain_string_copy = containString;

	// Adjust if not case sensitive
	if (caseSensitivity == NotCaseSensitive)
	{
		this_copy.toLowerCase();
		contain_string_copy.toLowerCase();
	}

	// Count all the occurrences of the contain string
	size_t found;
	std::string temp_str;
	int contains_count = 0;
	for (int i = 0; i < this_copy.length(); ++i)
	{
		temp_str = this_copy.subString(i, contain_string_copy.length());
		found = temp_str.find(contain_string_copy);
		if (found != std::string::npos)
		{
			++contains_count;
		}
	}

	return contains_count;
}

int String::count(const char* containString, CaseSensitivity caseSensitivity) const
{
	return this->count(String(containString), caseSensitivity);
}

bool String::endsWith(const String& endString, CaseSensitivity caseSensitivity) const
{
	// Make sure the end string isn't empty
	if (endString.isEmpty())
	{
		throw InvalidArgumentError("bump::String::endsWith() passed empty end string");
	}

	// Make some copies to handle case sensitivity
	String this_copy = *this;
	String end_string_copy = endString;

	// Adjust if not case sensitive
	if (caseSensitivity == NotCaseSensitive)
	{
		this_copy.toLowerCase();
		end_string_copy.toLowerCase();
	}

	// Find the end section of the current string
	int index = this_copy.length() - end_string_copy.length();
	String last_part(this_copy.subString(index, this_copy.length()));

	// Test whether they're equal
	if (last_part == endString)
	{
		return true;
	}

	return false;
}

bool String::endsWith(const char* endString, CaseSensitivity caseSensitivity) const
{
	return endsWith(String(endString), caseSensitivity);
}

String& String::fill(const String& character, int size)
{
	// Make sure they character passed in is a single character
	if (character.length() != 1)
	{
		throw InvalidArgumentError("bump::String::fill() passed invalid character...must be length of one");
	}

	// Make sure the size is not less than -1
	if (size < -1)
	{
		throw InvalidArgumentError("bump::String::fill() passed invalid size, must not be less than -1");
	}

	// Change the size of the string if necessary
	if (size > -1)
	{
		this->resize(size);
	}

	// Perform the actual fill
	String character_copy = character;
	char fill_character = character_copy.at(0);
	for (int i = 0; i < this->size(); ++i)
	{
		(*this)[i] = fill_character;
	}

	return *this;
}

int String::indexOf(const String& indexString, int startPosition, CaseSensitivity caseSensitivity) const
{
	// Make sure the index string passed in is not empty
	if (indexString.empty())
	{
		throw InvalidArgumentError("bump::String::indexOf() passed empty index string");
	}

	// Make sure startPosition is inside our bounds
	if (startPosition > length() - 1 || startPosition < 0)
	{
		return -1;
	}

	// Create some copies for manipulation
	String this_copy = *this;
	String index_string_copy = indexString;

	// Adjust for case sensitivity
	if (caseSensitivity == NotCaseSensitive)
	{
		this_copy.toLowerCase();
		index_string_copy.toLowerCase();
	}

	// Try to find the index string
	size_t found = this_copy.find(index_string_copy, startPosition);
	if (found != std::string::npos)
	{
		return int(found);
	}

	return -1;
}

int String::indexOf(const char* indexString, int startPosition, CaseSensitivity caseSensitivity) const
{
	return indexOf(String(indexString), startPosition, caseSensitivity);
}

String& String::insert(const String& insertString, int position)
{
	// Make sure the index string passed in is not empty
	if (insertString.empty())
	{
		throw InvalidArgumentError("bump::String::insert() passed empty insert string");
	}

	// Make sure position is inside our bounds
	if (position > length() || position < 0)
	{
		throw OutOfRangeError("bump::String::insert() position outside string bounds");
	}

	// Split the string in two
	String start;
	String end;
	if (position > 0)
		start = subString(0, position);
	if (length() > position)
		end = subString(position, this->length());

	// Combine them
	*this = start + insertString + end;

	return *this;
}

String& String::insert(const char* insertString, int position)
{
	return insert(String(insertString), position);
}

bool String::isEmpty() const
{
	return std::string::empty();
}

bool String::isNumber() const
{
	String this_copy = *this;
	double num;
	std::istringstream iss(this_copy);
	iss >> num;
	return (iss.fail() || (int)iss.tellg() != (int)this_copy.length()) ? false : true;
}

int String::lastIndexOf(String indexString, int startPosition, CaseSensitivity caseSensitivity) const
{
	// Make sure the index string passed in is not empty
	if (indexString.empty())
	{
		throw InvalidArgumentError("bump::String::lastIndexOf() passed empty index string");
	}

	// Make sure startPosition is inside our bounds
	if (startPosition > (int)length() - 1 || startPosition < -1)
	{
		return -1;
	}

	// Adjust a -1 startPosition to the end of this string
	if (startPosition == -1)
	{
		startPosition = length() - 1;
	}

	// Create some copies for manipulation
	String this_copy = *this;
	String index_string_copy = indexString;

	// Adjust for case sensitivity
	if (caseSensitivity == NotCaseSensitive)
	{
		this_copy.toLowerCase();
		index_string_copy.toLowerCase();
	}

	// Try to find the index string
	size_t found = this_copy.rfind(index_string_copy, startPosition);
	if (found != std::string::npos)
	{
		return int(found);
	}

	return -1;
}

int String::lastIndexOf(const char* indexString, int startPosition, CaseSensitivity caseSensitivity) const
{
	return lastIndexOf(String(indexString), startPosition, caseSensitivity);
}

String String::left(int n) const
{
	// Make sure number is inside our bounds
	if (n > length() || n < 1)
	{
		throw OutOfRangeError("bump::String::left() n is outside string bounds");
	}

	return subString(0, n);
}

unsigned int String::length() const
{
	return std::string::length();
}

String& String::prepend(const String& prependString)
{
	std::string::insert(0, prependString);
	return *this;
}

String& String::prepend(const char* prependString)
{
	std::string::insert(0, prependString);
	return *this;
}

String& String::remove(int position, int n)
{
	// Make sure the position is valid
	if (position < 0 || position > length() - 1)
	{
		throw OutOfRangeError("bump::String::remove() position is outside string bounds");
	}

	// Make sure the width is valid
	if (n < 0)
	{
		throw InvalidArgumentError("bump::String::remove() n cannot be negative");
	}

	std::string::erase(position, n);
	return *this;
}

String& String::remove(const String& removeString, CaseSensitivity caseSensitivity)
{
	// Make sure the remove string passed in is not empty
	if (removeString.empty())
	{
		throw InvalidArgumentError("bump::String::remove() passed empty remove string");
	}

	// Create some copies for manipulation
	String this_copy = *this;
	String remove_string_copy = removeString;

	// Adjust for case sensitivity
	if (caseSensitivity == NotCaseSensitive)
	{
		this_copy.toLowerCase();
		remove_string_copy.toLowerCase();
	}

	// Remove all occurrences of the remove string
	size_t found = 0;
	while (found != std::string::npos)
	{
		found = this_copy.rfind(remove_string_copy);
		if (found != std::string::npos)
		{
			remove(int(found), remove_string_copy.length());
			this_copy.remove(int(found), remove_string_copy.length());
		}
	}

	return *this;
}

String& String::remove(const char* removeString, CaseSensitivity caseSensitivity)
{
	return remove(String(removeString), caseSensitivity);
}

String& String::replace(int position, int n, const String& replaceString)
{
	// Make sure the position is valid
	if (position < 0 || position > length())
	{
		throw OutOfRangeError("bump::String::replace() position is outside string bounds");
	}

	// Make sure n is positive
	if (n < 0)
	{
		throw InvalidArgumentError("bump::String::replace() n cannot be negative");
	}

	remove(position, n);
	if (!replaceString.isEmpty())
		insert(replaceString, position);
	return *this;
}

String& String::replace(int position, int n, const char* replaceString)
{
	return replace(position, n, String(replaceString));
}

String& String::replace(const String& before, const String& after, CaseSensitivity caseSensitivity)
{
	// Make sure the before string is not empty
	if (before.isEmpty())
	{
		throw InvalidArgumentError("bump::String::replace() passed an empty before string");
	}

	// Ignore if the before and after strings are the same
	if (before == after)
	{
		return *this;
	}

	// Create some copies for manipulation
	String this_copy = *this;
	String before_copy = before;

	// Adjust for case sensitivity
	if (caseSensitivity == NotCaseSensitive)
	{
		this_copy.toLowerCase();
		before_copy.toLowerCase();
	}

	// Replace all occurrences of before with after
	size_t found = 0;
	while (found != std::string::npos)
	{
		found = this_copy.find(before, found);
		if (found != std::string::npos)
		{
			remove(int(found), before.length());
			this_copy.remove(int(found), before.length());
			if (!after.isEmpty())
			{
				insert(after, found);
				this_copy.insert(after, found);
				found += after.length();
			}
		}
	}

	return *this;
}

String& String::replace(const char* before, const char* after, CaseSensitivity caseSensitivity)
{
	return replace(String(before), String(after), caseSensitivity);
}

String String::right(int n) const
{
	// Make sure number is inside our bounds
	if (n > length() || n < 1)
	{
		throw OutOfRangeError("bump::String::left() n is outside string bounds");
	}

	return subString(length() - n, length());
}

String String::section(int startPosition, int length) const
{
	// Make sure the start position is valid
	if (startPosition < 0 || startPosition > (int)this->length() - 1)
	{
		throw OutOfRangeError("bump::String::section() position is outside string bounds");
	}

	// Adjust for the default length
	if (length == -1)
	{
		length = this->length();
	}

	// Make sure length is at least 1
	if (length < 1)
	{
		throw InvalidArgumentError("bump::String::section() length must be at least one");
	}

	return subString(startPosition, length);
}

StringList String::split(const String& separator) const
{
	// Make sure we only have a single character
	if (separator.length() != 1)
	{
		throw InvalidArgumentError("bump::String::split() separator can only be a single character");
	}

	// Make mutable copy of this string
	String this_copy = *this;

	// Split up the copy into a separated string list
	std::vector<String> split_strings;
	int index = 0;
	while (index != -1)
	{
		index = this_copy.indexOf(separator);
		if (index != -1)
		{
			split_strings.push_back(this_copy.substr(0, index));
			this_copy.remove(0, index + 1);
		}
	}
	split_strings.push_back(this_copy);

	return split_strings;
}

bool String::startsWith(const String& startString, CaseSensitivity caseSensitivity) const
{
	// Make sure the start string isn't empty
	if (startString.isEmpty())
	{
		throw InvalidArgumentError("bump::String::startsWith() start string cannot be empty");
	}

	// Create some copies for manipulation
	String this_copy = *this;
	String start_string_copy = startString;

	// Adjust for case sensitivity
	if (caseSensitivity == NotCaseSensitive)
	{
		this_copy.toLowerCase();
		start_string_copy.toLowerCase();
	}

	// Find the first substring with the same length as the start string
	String first_part(this_copy.subString(0, start_string_copy.length()));

	// Test whether they're equal
	if (first_part == start_string_copy)
	{
		return true;
	}

	return false;
}

bool String::startsWith(const char* startString, CaseSensitivity caseSensitivity) const
{
	return startsWith(String(startString), caseSensitivity);
}

String String::subString(int startPosition, int length) const
{
	// Make sure startPosition is inside our bounds
	if (startPosition < 0 || startPosition > (int)this->length())
	{
		throw OutOfRangeError("bump::String::subString() start position is outside string bounds");
	}

	// Make sure length is at least 1
	if (length < 1)
	{
		throw InvalidArgumentError("bump::String::subString() length must be at least one");
	}

	return substr(startPosition, length);
}

bool String::toBool() const
{
	// Make a copy and cast make it lowercase
	String this_copy = *this;
	this_copy.toLowerCase();

	// Make sure we have a valid bool or throw an exception
	if (this_copy != "true" && this_copy != "false")
	{
		throw TypeCastError("bump::String::toBool() cannot convert string to bool");
	}

	return this_copy == "true" ? true : false;
}

double String::toDouble() const
{
	try
	{
		return boost::lexical_cast<double>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("bump::String::toDouble() cannot convert string to double");
	}
}

float String::toFloat() const
{
	try
	{
		return boost::lexical_cast<float>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("bump::String::toFloat() cannot convert string to float");
	}
}

int String::toInt() const
{
	try
	{
		return boost::lexical_cast<int>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("bump::String::toInt() cannot convert string to int");
	}
}

long String::toLong() const
{
	try
	{
		return boost::lexical_cast<long>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("bump::String::toLong() cannot convert string to long");
	}
}

long long String::toLongLong() const
{
	try
	{
		return boost::lexical_cast<long long>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("bump::String::toLongLong() cannot convert string to long long");
	}
}

String& String::toLowerCase()
{
	for (int i = 0; i < length(); ++i)
	{
		(*this)[i] = tolower(at(i));
	}

	return *this;
}

int String::toShort() const
{
	try
	{
		return boost::lexical_cast<short>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("bump::String::toShort() cannot convert string to short");
	}
}

std::string String::toStdString() const
{
	return *this;
}

unsigned int String::toUInt() const
{
	try
	{
		return boost::lexical_cast<unsigned int>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("bump::String::toUInt() cannot convert string to unsigned int");
	}
}

unsigned long String::toULong() const
{
	try
	{
		return boost::lexical_cast<unsigned long>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("bump::String::toULong() cannot convert string to unsigned long");
	}
}

unsigned long long String::toULongLong() const
{
	try
	{
		return boost::lexical_cast<unsigned long long>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("bump::String::toULongLong() cannot convert string to unsigned long long");
	}
}

String& String::toUpperCase()
{
	for (int i = 0; i < length(); ++i)
	{
		(*this)[i] = toupper(at(i));
	}

	return *this;
}

unsigned short String::toUShort() const
{
	try
	{
		return boost::lexical_cast<unsigned short>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("bump::String::toUShort() cannot convert string to unsigned short");
	}
}

String& String::operator << (const String& appendString)
{
	*this += appendString;
	return *this;
}

String& String::operator << (const char* appendString)
{
	*this += String(appendString);
	return *this;
}

String& String::operator << (unsigned char appendChar)
{
	*this += String(appendChar);
	return *this;
}

String& String::operator << (char appendChar)
{
	*this += String(appendChar);
	return *this;
}

String& String::operator << (unsigned short appendShort)
{
	*this += String(appendShort);
	return *this;
}

String& String::operator << (short appendShort)
{
	*this += String(appendShort);
	return *this;
}

String& String::operator << (unsigned int appendInt)
{
	*this += String(appendInt);
	return *this;
}

String& String::operator << (int appendInt)
{
	*this += String(appendInt);
	return *this;
}

String& String::operator << (unsigned long appendLong)
{
	*this += String(appendLong);
	return *this;
}

String& String::operator << (long appendLong)
{
	*this += String(appendLong);
	return *this;
}

String& String::operator << (unsigned long long appendLongLong)
{
	*this += String(appendLongLong);
	return *this;
}

String& String::operator << (long long appendLongLong)
{
	*this += String(appendLongLong);
	return *this;
}

String& String::operator << (float appendFloat)
{
	*this += String(appendFloat);
	return *this;
}

String& String::operator << (double appendDouble)
{
	*this += String(appendDouble);
	return *this;
}

String& String::operator << (bool appendBool)
{
	*this += String(appendBool);
	return *this;
}
