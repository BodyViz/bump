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
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

// Bump headers
#include <bump/InvalidArgumentError.h>
#include <bump/OutOfRangeError.h>
#include <bump/String.h>
#include <bump/StringSearchError.h>
#include <bump/TypeCastError.h>

namespace bump {

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
		throw InvalidArgumentError("Cannot handle a precision less than -1", BUMP_LOCATION);
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
		throw InvalidArgumentError("Cannot handle a precision less than -1", BUMP_LOCATION);
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

String String::join(const StringList& strings, const String& separator)
{
	int last_string = strings.size() - 1;
	String joined;
	for (unsigned int i = 0; i < strings.size(); ++i)
	{
		joined = i != last_string ? joined << strings.at(i) << separator : joined << strings.at(i);
	}

	return joined;
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

String String::arg(const String& argument) const
{
	// Find all the markers (i.e. %1 - %99)
	boost::regex expression("%[1-9][0-9]?");
	std::vector<std::string> markers;
	boost::algorithm::find_all_regex(markers, *this, expression);

	// Throw an arg error if we didn't find any markers
	if (markers.empty())
	{
		throw StringSearchError("Could not find any markers (i.e. %1 - %99", BUMP_LOCATION);
	}

	// Now we need to find the lowest marker so we can replace it. We also need to store each
	// marker's position in a multimap to be able to replace only the exact portion of the
	// string. For example, we need to ensure we don't replace %1 and %10 at the same time.
	// To make sure we only replace the %1 and not the %10 on this call, we use the multimap.
	std::multimap<int, int> marker_position_map;
	unsigned int current_index = 0;
	unsigned int lowest_marker_value = 100;
	String lowest_marker;
	for (unsigned int i = 0; i < markers.size(); ++i)
	{
		// First find the marker index position in this string
		String marker = markers.at(i);
		int marker_position_index = indexOf(marker, current_index);

		// Convert the marker to a value
		unsigned int marker_value = marker.remove("%").toUInt();
		marker = markers.at(i);

		// See if the match is the lowest
		if (marker_value < lowest_marker_value)
		{
			lowest_marker_value = marker_value;
			lowest_marker = marker;
		}

		// Store the match value and position in the map
		marker_position_map.insert(std::pair<int, int>(marker_value, marker_position_index));

		// Update the current index for the next iteration
		current_index = marker_position_index + markers.at(i).length();
	}

	// Create a copy of this string for replacement
	String replaced = *this;

	// Iterate through the marker position map and replace all the lowest markers. We need to also
	// keep track of the difference in length between our match text and the replacement argument
	// text as "skipped_space". Our replacement positions need to then be adjusted by the skipped
	// space each time to map properly.
	int skipped_space = 0;
	std::multimap<int, int>::iterator iter = marker_position_map.find(lowest_marker_value);
	for (iter = marker_position_map.find(lowest_marker_value); iter != marker_position_map.end(); ++iter)
	{
		// Stop once we're finished with the lowest markers
		if (iter->first != lowest_marker_value)
		{
			break;
		}

		// Actually replace the marker with the argument using skipped_space to make sure we're
		// in the right spot regardless of how many iterations we've gone through.
		int start_position = iter->second;
		replaced.replace(start_position + skipped_space, lowest_marker.length(), argument);

		// Update the skipped space
		skipped_space += argument.length() - lowest_marker.length();
	}

	return replaced;
}

String String::arg(const String& a1, const String& a2) const
{
	String replaced = this->arg(a1);
	replaced = replaced.arg(a2);

	return replaced;
}

String String::arg(const String& a1, const String& a2, const String& a3) const
{
	String replaced = this->arg(a1);
	replaced = replaced.arg(a2);
	replaced = replaced.arg(a3);

	return replaced;
}

String String::arg(const String& a1, const String& a2, const String& a3, const String& a4) const
{
	String replaced = this->arg(a1);
	replaced = replaced.arg(a2);
	replaced = replaced.arg(a3);
	replaced = replaced.arg(a4);

	return replaced;
}

String String::arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5) const
{
	String replaced = this->arg(a1);
	replaced = replaced.arg(a2);
	replaced = replaced.arg(a3);
	replaced = replaced.arg(a4);
	replaced = replaced.arg(a5);

	return replaced;
}

String String::arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
				   const String& a6) const
{
	String replaced = this->arg(a1);
	replaced = replaced.arg(a2);
	replaced = replaced.arg(a3);
	replaced = replaced.arg(a4);
	replaced = replaced.arg(a5);
	replaced = replaced.arg(a6);

	return replaced;
}

String String::arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
				   const String& a6, const String& a7) const
{
	String replaced = this->arg(a1);
	replaced = replaced.arg(a2);
	replaced = replaced.arg(a3);
	replaced = replaced.arg(a4);
	replaced = replaced.arg(a5);
	replaced = replaced.arg(a6);
	replaced = replaced.arg(a7);

	return replaced;
}

String String::arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
				   const String& a6, const String& a7, const String& a8) const
{
	String replaced = this->arg(a1);
	replaced = replaced.arg(a2);
	replaced = replaced.arg(a3);
	replaced = replaced.arg(a4);
	replaced = replaced.arg(a5);
	replaced = replaced.arg(a6);
	replaced = replaced.arg(a7);
	replaced = replaced.arg(a8);

	return replaced;
}

String String::arg(const String& a1, const String& a2, const String& a3, const String& a4, const String& a5,
				   const String& a6, const String& a7, const String& a8, const String& a9) const
{
	String replaced = this->arg(a1);
	replaced = replaced.arg(a2);
	replaced = replaced.arg(a3);
	replaced = replaced.arg(a4);
	replaced = replaced.arg(a5);
	replaced = replaced.arg(a6);
	replaced = replaced.arg(a7);
	replaced = replaced.arg(a8);
	replaced = replaced.arg(a9);

	return replaced;
}

const char& String::at(int position) const
{
	try
	{
		return std::string::at(position);
	}
	catch (const std::out_of_range& /*e*/)
	{
		throw OutOfRangeError("Position is outside string bounds", BUMP_LOCATION);
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

String& String::chop(unsigned int n)
{
	// If n is greater than or equal to length(), clear the string
	if ((int)n >= length())
	{
		clear();
	}
	else
	{
		*this = section(0, length() - n);
	}

	return *this;
}

void String::clear()
{
	std::string::clear();
}

bool String::compare(const String& otherString, CaseSensitivity caseSensitivity) const
{
	// Make some copies to handle case sensitivity
	String this_copy = *this;
	String other_string_copy = otherString;

	// Adjust if not case sensitive
	if (caseSensitivity == NotCaseSensitive)
	{
		this_copy.toLowerCase();
		other_string_copy.toLowerCase();
	}

	return this_copy.std::string::compare(other_string_copy) == 0;
}

bool String::compare(const char* otherString, CaseSensitivity caseSensitivity) const
{
	return compare(String(otherString), caseSensitivity);
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
		temp_str = this_copy.section(i, contain_string_copy.length());
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

const char* String::data() const
{
	return std::string::data();
}

bool String::endsWith(const String& endString, CaseSensitivity caseSensitivity) const
{
	if (caseSensitivity == NotCaseSensitive)
	{
		return boost::algorithm::iends_with(*this, endString);
	}

	return boost::algorithm::ends_with(*this, endString);
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
		throw InvalidArgumentError("Passed invalid character...must be length of one", BUMP_LOCATION);
	}

	// Make sure the size is not less than -1
	if (size < -1)
	{
		throw InvalidArgumentError("Passed invalid size, must not be less than -1", BUMP_LOCATION);
	}

	// Change the size of the string if necessary
	if (size > -1)
	{
		this->resize(size);
	}

	// Perform the actual fill
	String character_copy = character;
	char fill_character = character_copy.at(0);
	for (unsigned int i = 0; i < this->size(); ++i)
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
		throw InvalidArgumentError("Passed empty index string", BUMP_LOCATION);
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
		throw InvalidArgumentError("Passed empty insert string", BUMP_LOCATION);
	}

	// Make sure position is inside our bounds
	if (position > length() || position < 0)
	{
		throw OutOfRangeError("Position outside string bounds", BUMP_LOCATION);
	}

	// Split the string in two
	String start;
	String end;
	if (position > 0)
		start = section(0, position);
	if (length() > position)
		end = section(position, this->length());

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
	if(iss >> num){
		if(iss.tellg() != -1){
			return false;
		}
		return true;
	}else {
		return false;
	}
}

int String::lastIndexOf(String indexString, int startPosition, CaseSensitivity caseSensitivity) const
{
	// Make sure the index string passed in is not empty
	if (indexString.empty())
	{
		throw InvalidArgumentError("Passed empty index string", BUMP_LOCATION);
	}

	// Make sure startPosition is inside our bounds
	if (startPosition > length() - 1 || startPosition < -1)
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
		throw OutOfRangeError("The n parameter is outside string bounds", BUMP_LOCATION);
	}

	return section(0, n);
}

int String::length() const
{
	return std::string::length();
}

String& String::padWithString(const String& padString, unsigned int paddedLength)
{
	// Simply return if padString is empty
	if (padString.isEmpty())
	{
		return *this;
	}

	// Prepend the padString onto this string until the paddedLength is hit
	while ((unsigned int)length() < paddedLength)
	{
		prepend(padString);
	}

	return *this;
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

String String::repeated(unsigned int times) const
{
	// Create the repeated string instance
	String repeated_string;

	// Add the data from this string the specified number of times
	for (unsigned int i = 0; i < times; ++i)
	{
		repeated_string += *this;
	}

	return repeated_string;
}

String& String::remove(int position, int n)
{
	// Make sure the position is valid
	if (position < 0 || position > length())
	{
		throw OutOfRangeError("Position is outside string bounds", BUMP_LOCATION);
	}

	// Make sure the width is valid
	if (n < 0)
	{
		throw InvalidArgumentError("The n parameter cannot be negative", BUMP_LOCATION);
	}

	std::string::erase(position, n);
	return *this;
}

String& String::remove(const String& removeString, CaseSensitivity caseSensitivity)
{
	// Make sure the remove string passed in is not empty
	if (removeString.empty())
	{
		throw InvalidArgumentError("Passed empty remove string", BUMP_LOCATION);
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
		throw OutOfRangeError("Position is outside string bounds", BUMP_LOCATION);
	}

	// Make sure n is positive
	if (n < 0)
	{
		throw InvalidArgumentError("The n parameter cannot be negative", BUMP_LOCATION);
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
		throw InvalidArgumentError("Passed an empty before string", BUMP_LOCATION);
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
		throw OutOfRangeError("The n parameter is outside string bounds", BUMP_LOCATION);
	}

	return section(length() - n, length());
}

String String::section(int startPosition, int length) const
{
	// Make sure the start position is valid
	if (startPosition < 0 || startPosition > this->length() - 1)
	{
		throw OutOfRangeError("Position is outside string bounds", BUMP_LOCATION);
	}

	// Adjust for the default length
	if (length == -1)
	{
		length = this->length();
	}

	// Make sure length is at least 1
	if (length < 1)
	{
		throw InvalidArgumentError("Length must be at least one", BUMP_LOCATION);
	}

	return substr(startPosition, length);
}

StringList String::split(const String& separator) const
{
	// Use boost to split the string into a vector of std::strings
	std::vector<std::string> split_strings;
	boost::algorithm::split(split_strings, *this, boost::is_any_of(separator), boost::token_compress_on);

	// Convert the vector to a StringList
	StringList converted_strings;
	converted_strings.insert(converted_strings.end(), split_strings.begin(), split_strings.end());

	return converted_strings;
}

bool String::startsWith(const String& startString, CaseSensitivity caseSensitivity) const
{
	if (caseSensitivity == NotCaseSensitive)
	{
		return boost::algorithm::istarts_with(*this, startString);
	}

	return boost::algorithm::starts_with(*this, startString);
}

bool String::startsWith(const char* startString, CaseSensitivity caseSensitivity) const
{
	return startsWith(String(startString), caseSensitivity);
}

String String::title() const
{
	// Split the string by spaces, then capitalize each word
	String title;
	StringList split_strings = split(" ");
	for (unsigned int i = 0; i < split_strings.size(); ++i)
	{
		title << split_strings.at(i).toLowerCase().capitalize() << " ";
	}

	// Trim of that pesky last space
	title = title.trimmed();

	return title;
}

bool String::toBool() const
{
	// Make a copy and cast make it lowercase
	String this_copy = *this;
	this_copy.toLowerCase();

	// Make sure we have a valid bool or throw an exception
	if (this_copy != "true" && this_copy != "false")
	{
		throw TypeCastError("Cannot convert string to bool", BUMP_LOCATION);
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
		throw TypeCastError("Cannot convert string to double", BUMP_LOCATION);
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
		throw TypeCastError("Cannot convert string to float", BUMP_LOCATION);
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
		throw TypeCastError("Cannot convert string to int", BUMP_LOCATION);
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
		throw TypeCastError("Cannot convert string to long", BUMP_LOCATION);
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
		throw TypeCastError("Cannot convert string to long long", BUMP_LOCATION);
	}
}

String& String::toLowerCase()
{
	boost::algorithm::to_lower(*this);
	return *this;
}

short String::toShort() const
{
	try
	{
		return boost::lexical_cast<short>((*this).data());
	}
	catch (boost::bad_lexical_cast)
	{
		throw TypeCastError("Cannot convert string to short", BUMP_LOCATION);
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
		throw TypeCastError("Cannot convert string to unsigned int", BUMP_LOCATION);
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
		throw TypeCastError("Cannot convert string to unsigned long", BUMP_LOCATION);
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
		throw TypeCastError("Cannot convert string to unsigned long long", BUMP_LOCATION);
	}
}

String& String::toUpperCase()
{
	boost::algorithm::to_upper(*this);
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
		throw TypeCastError("Cannot convert string to unsigned short", BUMP_LOCATION);
	}
}

String String::trimmed() const
{
	return boost::algorithm::trim_copy_if(static_cast<std::string>(*this), boost::algorithm::is_any_of(" \t\n\v\f\r"));
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

}	// End of bump namespace
