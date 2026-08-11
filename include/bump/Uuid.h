//
//	Uuid.h
//	Bump
//
//	Created by Christian Noon on 11/19/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#pragma once

#include <bump/Export.h>

#include <boost/uuid/uuid.hpp>

namespace bump {

// Forward declarations
class String;

/**
 * The Bump Uuid class is used for storing Universally Unique Identifiers or
 * UUIDs. A UUID is typically used to identify unique entities throughout your
 * code. This class makes it easy to generate random UUIDs, as well as convert
 * them to/from bump::Strings.
 */
class Uuid : public boost::uuids::uuid {
public:
    /**
     * Default constructor creates a null uuid (i.e.
     * "00000000-0000-0000-0000-000000000000").
     */
    BUMP_EXPORT Uuid();

    /**
     * Copy constructor creates a new uuid from a boost uuid.
     *
     * @param uuid The boost uuid to create a copy of.
     */
    BUMP_EXPORT Uuid(const boost::uuids::uuid& uuid);

    /**
     * Generates a random uuid by automatically seeding a random number
     * generator.
     *
     * @return A random uuid.
     */
    BUMP_EXPORT static Uuid generateRandom();

    /**
     * Generates a uuid from the given string (i.e.
     * "00000000-0000-0000-0000-000000000000").
     *
     * @throw bump::TypeCastError When string cannot be converted to uuid.
     *
     * @param uuidString A string formatted as a uuid to create the uuid from.
     * @return A new uuid based on the uuid string parameter.
     */
    BUMP_EXPORT static Uuid fromString(const String& uuidString);

    /**
     * Determines whether the uuid is null or equal to
     * "00000000-0000-0000-0000-000000000000".
     *
     * @return Whether the uuid is null or equal to
     * "00000000-0000-0000-0000-000000000000".
     */
    BUMP_EXPORT bool isNull() const;

    /**
     * Converts the uuid to a string.
     *
     * @return A string representation of the uuid.
     */
    BUMP_EXPORT String toString() const;

    /**
     * Determines whether this uuid and the right-hand side uuid are equal.
     *
     * @param rhs The right-hand side uuid.
     * @return True if this uuid and the right-hand side uuid are equal,
     * otherwise returns false.
     */
    BUMP_EXPORT bool operator==(const Uuid& rhs);

    /**
     * Determines whether this uuid and the right-hand side uuid are not equal.
     *
     * @param rhs The right-hand side uuid.
     * @return True if this uuid and the right-hand side uuid are not equal,
     * otherwise returns false.
     */
    BUMP_EXPORT bool operator!=(const Uuid& rhs);

    /**
     * Determines whether this uuid is less than the right-hand side uuid.
     *
     * @param rhs The right-hand side uuid.
     * @return True if this uuid is less than the right-hand side uuid,
     * otherwise returns false.
     */
    BUMP_EXPORT bool operator<(const Uuid& rhs);

    /**
     * Determines whether this uuid is greater than the right-hand side uuid.
     *
     * @param rhs The right-hand side uuid.
     * @return True if this uuid is greater than the right-side uuid, otherwise
     * returns false.
     */
    BUMP_EXPORT bool operator>(const Uuid& rhs);

    /**
     * Determines whether this uuid is less than or equal to the right-hand side
     * uuid.
     *
     * @param rhs The right-hand side uuid.
     * @return True if this uuid is less than or equal to the right-side uuid,
     * otherwise returns false.
     */
    BUMP_EXPORT bool operator<=(const Uuid& rhs);

    /**
     * Determines whether this uuid is greater than or equal to the right-hand
     * side uuid.
     *
     * @param rhs The right-hand side uuid.
     * @return True if this uuid is greater than or equal to the right-side
     * uuid, otherwise returns false.
     */
    BUMP_EXPORT bool operator>=(const Uuid& rhs);
};

}  // namespace bump
