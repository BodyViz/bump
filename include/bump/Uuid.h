//
//	Uuid.h
//	Bump
//
//	Created by Christian Noon on 11/19/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_UUID_H
#define BUMP_UUID_H

// Boost headers
#include <boost/uuid/uuid.hpp>

// Bump headers
#include <bump/Export.h>

namespace bump {

// Forward declarations
class String;

/**
 * The Bump Uuid class is used for storing Universally Unique Identifiers or UUIDs.
 * A UUID is typically used to identify unique entities throughout your code. This class
 * makes it easy to generate random UUIDs, as well as convert them to/from bump::Strings.
 */
class BUMP_EXPORT Uuid : public boost::uuids::uuid
{
public:

	/**
	 * Default constructor creates a null uuid (i.e. "00000000-0000-0000-0000-000000000000").
	 */
	Uuid();

	/**
	 * Copy constructor creates a new uuid from a bump::Uuid uuid.
	 *
	 * @param uuid The bump::Uuid to create a copy of.
	 */
	Uuid(const Uuid& uuid);

	/**
	 * Copy constructor creates a new uuid from a boost uuid.
	 */
	Uuid(const boost::uuids::uuid& uuid);

	/**
	 * Destructor.
	 */
	~Uuid();

	/**
	 * Generates a random uuid by automatically seedings a random number generator.
	 *
	 * @return A random uuid.
	 */
	static Uuid genarateRandom();

	/**
	 * Generates a uuid from the given string (i.e. "00000000-0000-0000-0000-000000000000").
	 *
	 * @throw bump::TypeCastError When string cannot be converted to uuid.
	 *
	 * @param uuidString A string formatted as a uuid to create the uuid from.
	 * @return A new uuid based on the uuid string parameter.
	 */
	static Uuid fromString(const String& uuidString);

	/**
	 * Determines whether the uuid is null or equal to "00000000-0000-0000-0000-000000000000".
	 *
	 * @return Whether the uuid is null or equal to "00000000-0000-0000-0000-000000000000".
	 */
	bool isNull() const;

	/**
	 * Converts the uuid to a string.
	 *
	 * @return A string representation of the uuid.
	 */
	String toString() const;
};

/**
 * Determines whether the left-hand side and right-hand side uuids are equal.
 *
 * @param lhs The left-hand side uuid.
 * @param rhs The right-hand side uuid.
 * @return True if the left and right side uuids are equal, otherwise returns false.
 */
bool operator == (const Uuid& lhs, const Uuid& rhs)
{
	return boost::uuids::operator==(lhs, rhs);
}

/**
 * Determines whether the left-hand side and right-hand side uuids are not equal.
 *
 * @param lhs The left-hand side uuid.
 * @param rhs The right-hand side uuid.
 * @return True if the left and right side uuids are not equal, otherwise returns false.
 */
bool operator != (const Uuid& lhs, const Uuid& rhs)
{
	return boost::uuids::operator!=(lhs, rhs);
}

/**
 * Determines whether the left-hand side uuid is less than the right-hand side uuid.
 *
 * @param lhs The left-hand side uuid.
 * @param rhs The right-hand side uuid.
 * @return True if the left-hand side uuid is less than the right-side uuid, otherwise returns false.
 */
bool operator < (const Uuid& lhs, const Uuid& rhs)
{
	return boost::uuids::operator<(lhs, rhs);
}

/**
 * Determines whether the left-hand side uuid is greater than the right-hand side uuid.
 *
 * @param lhs The left-hand side uuid.
 * @param rhs The right-hand side uuid.
 * @return True if the left-hand side uuid is greater than the right-side uuid, otherwise returns false.
 */
bool operator > (const Uuid& lhs, const Uuid& rhs)
{
	return boost::uuids::operator>(lhs, rhs);
}

/**
 * Determines whether the left-hand side uuid is less than or equal to the right-hand side uuid.
 *
 * @param lhs The left-hand side uuid.
 * @param rhs The right-hand side uuid.
 * @return True if the left-hand side uuid is less than or equal to the right-side uuid, otherwise returns false.
 */
bool operator <= (const Uuid& lhs, const Uuid& rhs)
{
	return boost::uuids::operator<=(lhs, rhs);
}

/**
 * Determines whether the left-hand side uuid is greater than or equal to the right-hand side uuid.
 *
 * @param lhs The left-hand side uuid.
 * @param rhs The right-hand side uuid.
 * @return True if the left-hand side uuid is greater than or equal to the right-side uuid, otherwise returns false.
 */
bool operator >= (const Uuid& lhs, const Uuid& rhs)
{
	return boost::uuids::operator>=(lhs, rhs);
}

}	// End of bump namespace

#endif	// End of BUMP_UUID_H
