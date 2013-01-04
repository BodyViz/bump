//
//  CryptographicHash.h
//  Bump
//
//  Created by Christian Noon on 1/4/13.
//  Copyright (c) 2013 Christian Noon. All rights reserved.
//

#ifndef BUMP_CRYPTOGRAPHIC_HASH_H
#define BUMP_CRYPTOGRAPHIC_HASH_H

// Bump headers
#include <bump/Export.h>
#include <bump/String.h>

namespace bump {

/**
 * The CryptographicHash class is used to generate a sha1 hash for textual
 * and binary data. It is designed to make it easy to add additional hash
 * algorithms in the future.
 */
class BUMP_EXPORT CryptographicHash
{
public:

	/**
	 * Defines the possible types of output formatting to be printed to std::cout.
	 */
	enum Algorithm
	{
		SHA1	/**< The sha1 hash algorithm. */
	};

	/**
	 * Constructor.
	 *
	 * @param algorithm The algorithm to use to generate the cryptographic hash.
	 */
	CryptographicHash(const Algorithm& algorithm = SHA1);

	/**
	 * Destructor.
	 */
	~CryptographicHash();

	/**
	 * Sets the textual data to generate the cryptographic hash.
	 *
	 * @param data The data string to use to generate the cryptographic hash.
	 */
	void setData(const String& data);

	/**
	 * Sets the binary data to generate the cryptographic hash.
	 *
	 * @param data The binary data to use to generate the cryptographic hash.
	 * @param length The length of the binary data.
	 */
	void setData(const char* data, int length);

	/**
	 * Resets the data and length of the hash to generate another hash.
	 */
	void reset();

	/**
	 * Computes the cryptographic hash and returns the 40 character hex string hash.
	 *
	 * @return The cryptographic hash as a 40 character hex string.
	 */
	String result();

protected:

	// Instance member variables
	Algorithm		_algorithm;		/**< @internal The algorithm to use to generate the cryptographic hash. */
	const char*		_data;			/**< @internal The data used to generate the cryptographic hash. */
	int				_length;		/**< @internal The length of the data used to generate the cryptographic hash. */
};

}	// End of bump namespace

#endif	// End of BUMP_CRYPTOGRAPHIC_HASH_H
