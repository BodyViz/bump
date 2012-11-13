//
//	EnvironmentFixture.h
//	Bump
//
//	Created by Christian Noon on 11/12/11.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMPTEST_ENVIRONMENT_FIXTURE_H
#define BUMPTEST_ENVIRONMENT_FIXTURE_H

#include <gtest/gtest.h>

namespace bumpTest {

/** Point of entry for the Bump test suite. */
class EnvironmentFixture : public testing::Environment
{
public:

	/** Constructor. */
	EnvironmentFixture() {}

	/** Destructor. */
	~EnvironmentFixture() {}

	/** Run immediately before a test starts. Starts the timer. */
	void SetUp();

	/** Invoked immediately after a test finishes. Stops the timer. */
	void TearDown() {}
};

void EnvironmentFixture::SetUp()
{
	// Set up everything we need to run the test suite
}

}	// End of bumpTest namespace

#endif	// End of BUMPTEST_ENVIRONMENT_FIXTURE_H
