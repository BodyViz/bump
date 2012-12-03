//
//  main.cpp
//  Bump
//
//  Created by Christian Noon on 12/3/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/String.h>
#include <bump/Environment.h>

/**
 * This example demonstrates how to use the bump::Environment class.
 *
 * The Bump Environment class is designed to make it easy to work with environment
 * variables. You can easily fetch, set and unset environment variables at runtime.
 */
int main(int argc, char **argv)
{
	// How to set environment variables
	std::cout << "Setting environment variables:" << std::endl;
	bump::String bump_home_value("/My/Path/To/Bump");
	bump::Environment::setEnvironmentVariable("BUMP_HOME", bump_home_value, true);
	std::cout << "- Set \"BUMP_HOME\" to \"" << bump_home_value << "\"" << std::endl;
	bump::String bump_output_file_value("output.txt");
	bump::Environment::setEnvironmentVariable("BUMP_OUTPUT_FILE", bump_output_file_value);
	std::cout << "- Set \"BUMP_OUTPUT_FILE\" to \"" << bump_output_file_value << "\"" << std::endl;

	// How to fetch environment variable values
	std::cout << "\nFetching environment variables:" << std::endl;
	bump::String bump_home = bump::Environment::environmentVariable("BUMP_HOME");
	std::cout << "- \"BUMP_HOME\" is \"" << bump_home << "\"" << std::endl;
	bump::String bump_output_file = bump::Environment::environmentVariable("BUMP_OUTPUT_FILE");
	std::cout << "- \"BUMP_OUTPUT_FILE\" is \"" << bump_output_file << "\"" << std::endl;

	// How to unset environment variables
	std::cout << "\nUnsetting environment variables:" << std::endl;
	bump::Environment::unsetEnvironmentVariable("BUMP_HOME");
	bump::Environment::unsetEnvironmentVariable("BUMP_OUTPUT_FILE");
	bump_home = bump::Environment::environmentVariable("BUMP_HOME");
	std::cout << "- \"BUMP_HOME\" is \"" << bump_home << "\"" << std::endl;
	bump_output_file = bump::Environment::environmentVariable("BUMP_OUTPUT_FILE");
	std::cout << "- \"BUMP_OUTPUT_FILE\" is \"" << bump_output_file << "\"" << std::endl;

    return 0;
}
