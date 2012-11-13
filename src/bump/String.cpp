//
//  String.cpp
//  Bump
//
//  Created by Christian Noon on 11/7/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// C++ headers
#include <iomanip>

// Boost headers
#include <boost/lexical_cast.hpp>

// Bump headers
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

String::String(float number, unsigned int precision)
{
	std::ostringstream result;
	result.setf(std::ios::fixed, std::ios::floatfield);
    result << std::setprecision(precision) << number;
	*this = result.str();
}

String::String(double number, unsigned int precision)
{
	std::ostringstream result;
	result.setf(std::ios::fixed, std::ios::floatfield);
    result << std::setprecision(precision) << number;
	*this = result.str();
}

String::String(bool boolValue)
{
	*this = boolValue == true ? String("true") : String("false");
}

void String::append(const String& appendString)
{
    *this += appendString;
}

void String::append(const char* appendString)
{
    *this += appendString;
}

char& String::at(int position)
{
    return this->std::string::at(position);
}

const char* String::c_str() const
{
    return this->std::string::c_str();
}

void String::capitalize()
{
	if (!isEmpty())
	{
		at(0) = toupper(at(0));
	}
}

void String::clear()
{
    this->std::string::clear();
}

bool String::compare(const String& otherString) const
{
    if (this->std::string::compare(otherString) == 0)
    {
        return true;
    }

    return false;
}

bool String::compare(const char* otherString) const
{
    if (this->std::string::compare(otherString) == 0)
    {
        return true;
    }

    return false;
}

bool String::contains(const String& containString, String::CaseSensitivity caseSensitivity) const
{
    size_t found;
    String sub = *this;
	String containStringCopy = containString;

    if (caseSensitivity == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        containStringCopy.toLowerCase();
    }

    found = sub.find(containStringCopy);
    if (found != std::string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool String::contains(const char* containString, String::CaseSensitivity caseSensitivity) const
{
    return this->contains(String(containString), caseSensitivity);
}

int String::count(const String& containString, String::CaseSensitivity caseSensitivity) const
{
    size_t found;
    std::string temp_str;
    int contains_count = 0;
    String sub = *this;
	String containStringCopy = containString;

    if (caseSensitivity == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        containStringCopy.toLowerCase();
    }

    for (int i = 0; i < sub.length(); i++)
    {
        temp_str = sub.substr(i, containStringCopy.length());
        found = temp_str.find(containString);
        if (found != std::string::npos)
        {
            contains_count++;
        }
    }

    return contains_count;
}

int String::count(const char* containString, String::CaseSensitivity caseSensitivity) const
{
    return this->count(String(containString), caseSensitivity);
}

bool String::empty() const
{
    return this->std::string::empty();
}

bool String::endsWith(const String& endString, String::CaseSensitivity caseSensitivity) const
{
    String sub = *this;
	String endStringCopy = endString;
    if (caseSensitivity == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        endStringCopy.toLowerCase();
    }

    int index = sub.length() - endStringCopy.length();
    String last_part(sub.substr(index, sub.length()));

    if (last_part == endString)
    {
        return true;
    }

    return false;
}

bool String::endsWith(const char* endString, String::CaseSensitivity caseSensitivity) const
{
    return this->endsWith(String(endString), caseSensitivity);
}

void String::erase(int position, int width)
{
	// Make sure the position is valid
	if (position < 0)
	{
		throw std::range_error("bump::String::erase cannot handle a negative position");
	}

	// Make sure the width is valid
	if (width < 0)
	{
		throw std::range_error("bump::String::erase cannot handle a negative width");
	}

    this->std::string::erase(position, width);
}

void String::erase(iterator position)
{
    this->std::string::erase(position);
}

void String::erase(iterator first, iterator last)
{
	// Throw an exception if the iterators are reversed
	if (last < first)
	{
		throw std::range_error("bump::String::erase was passed reversed iterators meaning the last comes before the first");
	}

    this->std::string::erase(first, last);
}

void String::fill(const char* ch, int size)
{
    if (String(ch).length() > 1)
    {
        assert(false);
    }

    if (size != -1)
    {
        this->resize(size);
    }

    for (int i = 0; i < this->size(); i++)
    {
        at(i) = *ch;
    }
}

int String::find(const String& str, int position)
{
    if (position > this->size() - 1)
    {
        return -1;
    }

    return int(this->std::string::find(str, position));
}

int String::find(const char* char_star, int position)
{
    if (position > this->size() - 1)
    {
        return -1;
    }

    return int(this->std::string::find(char_star, position));
}

int String::indexOf(String index_string, int from, String::CaseSensitivity cs)
{
    if (from > this->size() - 1)
    {
        assert(false);
    }

    size_t found;
    String sub = this->substr(from, this->length());

    if (cs == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        index_string.toLowerCase();
    }

    found = sub.find(index_string);
    if (found != std::string::npos)
    {
        return int(found);
    }

    return -1;
}

int String::indexOf(const char* index_char, int from, String::CaseSensitivity cs)
{
    return this->indexOf(String(index_char), from, cs);
}

void String::insert(int position, String insert_string)
{
    if (position > this->size())
    {
        assert(false);
    }

    String first = this->substr(0, position);
    String end = this->substr(position, this->length());

    *this = first + insert_string + end;
}

void String::insert(int position, const char* insert_char)
{
    insert(position, String(insert_char));
}

bool String::isEmpty()
{
    return this->empty();
}

bool String::isNumber()
{
    String temp = *this;
    double num;
    std::istringstream iss(temp);
    iss >> num;
    return (iss.fail() || (int)iss.tellg() != (int)temp.length()) ? false : true;
}

int String::lastIndexOf(String index_string, int from, String::CaseSensitivity cs)
{
    if (from > this->size() - 1)
    {
        assert(false);
    }

    size_t found;
    String sub = this->substr(from, this->length());

    if (cs == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        index_string.toLowerCase();
    }

    found = sub.rfind(index_string);
    if (found != std::string::npos)
    {
        return int(found);
    }

    return -1;
}

int String::lastIndexOf(const char* index_char, int from, String::CaseSensitivity cs)
{
    return this->lastIndexOf(String(index_char), from, cs);
}

String String::left(int num)
{
    if (num > this->size() - 1)
    {
        assert(false);
    }

    return this->substr(0, num);
}

int String::length()
{
    return this->std::string::length();
}

void String::padWithZeroes(unsigned int length)
{
	while (length > (unsigned int)this->length())
		this->prepend("0");
}

void String::prepend(const String& prepend_string)
{
    this->std::string::insert(0, prepend_string);
}

void String::prepend(const char* prepend_char)
{
    this->std::string::insert(0, prepend_char);
}

void String::print()
{
    std::cout << *this << std::endl;
}

void String::remove(int position, int width)
{
    erase(position, width);
}

void String::remove(String remove_string, String::CaseSensitivity cs)
{
    size_t found = 0;
    String sub = *this;

    if (cs == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        remove_string.toLowerCase();
    }

    while (found != std::string::npos)
    {
        found = sub.rfind(remove_string);
        if (found != std::string::npos)
        {
            this->erase(int(found), remove_string.length());
            sub.erase(int(found), remove_string.length());
        }
    }
}

void String::remove(const char* remove_char, String::CaseSensitivity cs)
{
    remove(String(remove_char), cs);
}

void String::replace(int position, int width, const String& replace_string)
{
    erase(position, width);
    insert(position, replace_string);
}

void String::replace(int position, int width, const char* replace_char)
{
    replace(position, width, String(replace_char));
}

void String::replace(String before_string, String after_string, String::CaseSensitivity cs)
{
    size_t found = 0;
    String sub = *this;

    if (before_string == after_string)
    {
		return;
    }

    if (cs == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        before_string.toLowerCase();
    }

    while (found != std::string::npos)
    {
        found = sub.find(before_string, found);
        if (found != std::string::npos)
        {
            erase(int(found), before_string.length());
            sub.erase(int(found), before_string.length());
            insert(found, after_string);
            sub.insert(found, after_string);
			found += after_string.length();
        }
    }
}

void String::replace(const char* before_char, const char* after_char, String::CaseSensitivity cs)
{
    replace(String(before_char), String(after_char), cs);
}

void String::resize(int n)
{
    this->std::string::resize(n);
}

void String::resize(int n, const char* c)
{
    this->std::string::resize(n, *c);
}

int String::rfind(const String& str)
{
    return int(this->std::string::rfind(str));
}

int String::rfind(const char* char_star)
{
    return int(this->std::string::rfind(char_star));
}

String String::right(int num)
{
    if (num > this->size() - 1)
    {
        assert(false);
    }

    return this->substr(this->length() - num, this->length());
}

String String::section(int start, int length)
{
    if (length == -1)
    {
        length = this->length();
    }

    return subString(start, length);
}

int String::size()
{
    return this->std::string::size();
}

std::vector<String> String::split(const char* sep)
{
    size_t found = 0;
    String search_str = *this;
    std::vector<String> split_strings;

    while (found != std::string::npos)
    {
        found = search_str.find(sep);
        if (found != std::string::npos)
        {
            split_strings.push_back(search_str.substr(0, found));
            search_str.erase(0, int(found) + 1);
        }
    }
    split_strings.push_back(search_str);

    return split_strings;
}

bool String::startsWith(String start_string, String::CaseSensitivity cs)
{
    String sub = *this;
    if (cs == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        start_string.toLowerCase();
    }

    String first_part(sub.substr(0, start_string.length()));

    if (first_part == start_string)
    {
        return true;
    }

    return false;
}

bool String::startsWith(String start_string, String::CaseSensitivity cs) const
{
	return String(*this).startsWith(start_string, cs);
}

bool String::startsWith(const char* start_char, String::CaseSensitivity cs)
{
    return this->startsWith(String(start_char), cs);
}

bool String::startsWith(const char* start_char, String::CaseSensitivity cs) const
{
	return String(*this).startsWith(start_char, cs);
}

String String::substr(int start, int length)
{
    return String(this->std::string::substr(start, length));
}

String String::subString(int start, int length)
{
    return substr(start, length);
}

bool String::toBool()
{
    String temp = *this;
    temp.toLowerCase();
    if (temp == "true")
    {
        return true;
    }

    return false;
}

double String::toDouble()
{
    return strtod(this->c_str(), NULL);
}

float String::toFloat()
{
    return (float)atof(this->c_str());
}

int String::toInt()
{
    return atoi(this->c_str());
}

void String::toLowerCase()
{
    for (int i = 0; i < this->length(); i++)
    {
        at(i) = tolower(at(i));
    }
}

std::string String::toStdString()
{
    return (std::string)*this;
}

void String::toUpperCase()
{
    for (int i = 0; i < this->length(); i++)
    {
        at(i) = toupper(at(i));
    }
}

String& String::operator << (const String& append_string)
{
    *this += append_string;
    return *this;
}

String& String::operator << (const char* append_char_array)
{
    *this += String(append_char_array);
    return *this;
}

String& String::operator << (unsigned char append_char)
{
    *this += String(append_char);
    return *this;
}

String& String::operator << (char append_char)
{
    *this += String(append_char);
    return *this;
}

String& String::operator << (unsigned short append_short)
{
    *this += String(append_short);
    return *this;
}

String& String::operator << (short append_short)
{
    *this += String(append_short);
    return *this;
}

String& String::operator << (unsigned int append_int)
{
    *this += String(append_int);
    return *this;
}

String& String::operator << (int append_int)
{
    *this += String(append_int);
    return *this;
}

String& String::operator << (unsigned long append_long)
{
    *this += String(append_long);
    return *this;
}

String& String::operator << (long append_long)
{
    *this += String(append_long);
    return *this;
}

String& String::operator << (float append_float)
{
    *this += String(append_float);
    return *this;
}

String& String::operator << (double append_double)
{
    *this += String(append_double);
    return *this;
}

String& String::operator << (bool append_bool)
{
    *this += String(append_bool);
    return *this;
}
