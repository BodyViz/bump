//
//  String.cpp
//  Bump
//
//  Created by Christian Noon on 11/7/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#include <bump/String.h>

using namespace bump;

String::String() : std::string() {}
String::String(const char* c_string) : std::string(c_string) {}
String::String(const std::string& std_string) : std::string(std_string) {}
String::String(unsigned char number) : std::string(_itoa(number)) {}
String::String(char number) : std::string(_itoa(number)) {}
String::String(unsigned short number) : std::string(_itoa(number)) {}
String::String(short number) : std::string(_itoa(number)) {}
String::String(unsigned int number) : std::string(_itoa(number)) {}
String::String(int number) : std::string(_itoa(number)) {}
String::String(unsigned long number) : std::string(_itoa(number)) {}
String::String(long number) : std::string(_itoa(number)) {}
String::String(float number) : std::string(_ftoa(number)) {}
String::String(double number) : std::string(_dtoa(number)) {}
String::String(bool bool_value) : std::string(_btoa(bool_value)) {}

String String::join(String path, String fname)
{
    String joined;
#ifdef _MSC_VER
    if (path.size() == 0 || fname.size() == 0)
    {
        joined = path + "\\" + fname;
    }
    else
    {
        char* end = &(path.at(path.length() - 1));
        char* begin = &(fname.at(0));
        if (String(end) == "\\" || String(begin) == "\\")
        {
            joined = path + fname;
        }
        else
        {
            joined = path + "\\" + fname;
        }
    }
#else
    if (path.size() == 0 || fname.size() == 0)
    {
        joined = path + "/" + fname;
    }
    else
    {
        char* end = &(path.at(path.length() - 1));
        char* begin = &(fname.at(0));
        if (String(end) == "/" || String(begin) == "/")
        {
            joined = path + fname;
        }
        else
        {
            joined = path + "/" + fname;
        }
    }
#endif

    return joined;
}

String String::joinVector(std::vector<String> strings)
{
    if (strings.size() == 0)
    {
        return String("");
    }

    String joined = strings.at(0);
    for (unsigned int i = 1; i < strings.size(); i++)
    {
#ifdef _MSC_VER
        joined += "\\" + strings.at(i);
#else
        joined += "/" + strings.at(i);
#endif
    }

    return joined;
}

void String::append(const String& append_string)
{
    *this += append_string;
}

void String::append(const char* append_char)
{
    *this += append_char;
}

char& String::at(int position)
{
    return this->std::string::at(position);
}

const char* String::c_str()
{
    return this->std::string::c_str();
}

const char* String::c_str() const
{
    return this->std::string::c_str();
}

void String::capitalize()
{
    at(0) = toupper(at(0));
}

void String::clear()
{
    this->std::string::clear();
}

bool String::compare(const String& str) const
{
    if (this->std::string::compare(str) == 0)
    {
        return true;
    }

    return false;
}

bool String::compare(const char* char_star) const
{
    if (this->std::string::compare(char_star) == 0)
    {
        return true;
    }

    return false;
}

bool String::contains(String contain_string, String::CaseSensitivity cs)
{
    size_t found;
    String sub = *this;

    if (cs == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        contain_string.toLowerCase();
    }

    found = sub.find(contain_string);
    if (found != std::string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool String::contains(const char* contain_char, String::CaseSensitivity cs)
{
    return this->contains(String(contain_char), cs);
}

int String::count(String contain_string, String::CaseSensitivity cs)
{
    size_t found;
    std::string temp_str;
    int contains_count = 0;
    String sub = *this;

    if (cs == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        contain_string.toLowerCase();
    }

    for (int i = 0; i < sub.length(); i++)
    {
        temp_str = sub.substr(i, contain_string.length());
        found = temp_str.find(contain_string);
        if (found != std::string::npos)
        {
            contains_count++;
        }
    }

    return contains_count;
}

int String::count(const char* contain_char, String::CaseSensitivity cs)
{
    return this->count(String(contain_char), cs);
}

bool String::empty() const
{
    return this->std::string::empty();
}

bool String::endsWith(String end_string, String::CaseSensitivity cs)
{
    String sub = *this;
    if (cs == String::NotCaseSensitive)
    {
        sub.toLowerCase();
        end_string.toLowerCase();
    }

    int index = sub.length() - end_string.length();
    String last_part(sub.substr(index, sub.length()));

    if (last_part == end_string)
    {
        return true;
    }

    return false;
}

bool String::endsWith(String end_string, String::CaseSensitivity cs) const
{
	return String(*this).endsWith(end_string, cs);
}

bool String::endsWith(const char* end_char, String::CaseSensitivity cs)
{
    return this->endsWith(String(end_char), cs);
}

bool String::endsWith(const char* end_char, String::CaseSensitivity cs) const
{
	return String(*this).endsWith(end_char, cs);
}

void String::erase(int position, int width)
{
    this->std::string::erase(position, width);
}

void String::erase(iterator position)
{
    this->std::string::erase(position);
}

void String::erase(iterator first, iterator last)
{
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

String String::_itoa(int input)
{
    std::ostringstream output;
    if (!(output << input))
    {
        return "ERROR - Conversion did not work";
    }

    return String(output.str());
}

String String::_ftoa(float input)
{
    char floatChars[256];
#ifdef _MSC_VER
    sprintf_s(floatChars, "%f", input);
#else
    sprintf(floatChars, "%f", input);
#endif

    return String(floatChars);
}

String String::_dtoa(double input)
{
    char floatChars[512];
#ifdef _MSC_VER
    sprintf_s(floatChars, "%f", input);
#else
    sprintf(floatChars, "%f", input);
#endif

    return String(floatChars);
}

String String::_btoa(bool input)
{
    if (input == true)
        return String("true");
    else
        return String("false");
}
