//
//	Enviroment.h
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_ENVIROMENT_H
#define BUMP_ENVIROMENT_H

// Bump headers
#include <bump/Export.h>

namespace bump {

// Forward declarations
class String;

/**
 * The Bump Environment namespace is designed to make it easy to work with environment
 * variables. You can easily fetch, set and unset environment variables.
 */
namespace Environment {

/**
 * Finds the string value for the given enviroment variable.
 *
 * @param name The environment variable's name you wish to find the value for.
 * @return The enviroment variable's value as a string.
 */
BUMP_EXPORT String environmentVariable(const String& name);

/**
 * Sets the environment variable to the given value.
 *
 * NOTE: If the environment variable already exists, the value is only overwritten if the
 * overwrite flag is true. If the environment variable does not exist, then the environment
 * variable is added to the runtime and set to the given value.
 *
 * @param name The environment variable's name you wish to set.
 * @param value The value of the environment variable you wish to set.
 * @param overwrite Whether to reset the value by overwritting the previous value with the new one.
 * @return True if the operation was successful, false otherwise.
 */
BUMP_EXPORT bool setEnvironmentVariable(const String& name, const String& value, bool overwrite = true);

/**
 * Removes all instances of the variable name.
 *
 * @param name The environment variable's name you wish to unset.
 * @return True if the operation was successful, false otherwise.
 */
BUMP_EXPORT bool unsetEnvironmentVariable(const String& name);

/**
 * Returns the username of the current user.
 *
 * @return The username of the current user.
 */
BUMP_EXPORT String currentUsername();

}	// End of Environment namespace

}	// End of bump namespace

#endif	// End of BUMP_ENVIRONMENT_H
