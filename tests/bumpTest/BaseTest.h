//
//	BaseTest.h
//	Bump
//
//	Created by Christian Noon on 11/12/11.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#pragma once

#include <gtest/gtest.h>

namespace bumpTest {

/** Base test class for setting up unit tests for the Bump test suite. */
class BaseTest : public testing::Test {
protected:
    /** Constructor. */
    BaseTest() {}

    /** Destructor. */
    ~BaseTest() {}

    /** Run immediately before a test starts. Starts the timer. */
    virtual void SetUp() {}

    /** Invoked immediately after a test finishes. Stops the timer. */
    virtual void TearDown() {}
};

}  // namespace bumpTest
