//
//  CryptographicHash.cpp
//  Bump
//
//  Created by Christian Noon on 1/4/13.
//  Copyright (c) 2013 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/CryptographicHash.h>

// Smallsha1 headers
#include <smallsha1/sha1.h>

namespace bump {

CryptographicHash::CryptographicHash(const Algorithm& algorithm) :
	_algorithm(algorithm),
	_data(NULL),
	_length(0)
{
	;
}

CryptographicHash::~CryptographicHash()
{
	;
}

void CryptographicHash::setData(const String& data)
{
	_data = data.c_str();
	_length = data.length();
}

void CryptographicHash::setData(const char* data, int length)
{
	_data = data;
	_length = length;
}

void CryptographicHash::reset()
{
	_data = NULL;
	_length = 0;
}

String CryptographicHash::result()
{
	// Make sure the data has been set
	if (_data == NULL || _length == 0)
	{
		return String();
	}

	// Compute the hash using the sha1 algorithm
	unsigned char hash[20];
	char hexstring[41];
	hexstring[40] = 0;
	sha1::calc(_data, _length, hash);
	sha1::toHexString(hash, hexstring);

	return String(hexstring);
}

}	// End of bump namespace
