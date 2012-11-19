//
//	main.cpp
//	Bump
//
//	Created by Christian Noon on 11/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// GTest headers
#include <gtest/gtest.h>

// bumpTest headers
#include "../bumpTest/EnvironmentFixture.h"

/**
 * This application consists of a full coverage set of unit tests for the bump::String
 * class. It uses the GTest framework to each possible runtime path of every function
 * in the String class.
 */
int main(int argc, char **argv)
{
	std::cout << "Begin running all tests...\n\n";

	// Setup the environment
	testing::AddGlobalTestEnvironment(new bumpTest::EnvironmentFixture);

	// Initialize everything and run all the tests
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
