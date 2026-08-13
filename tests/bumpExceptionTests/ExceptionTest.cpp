//
//	ExceptionTest.cpp
//	Bump
//

#include <bump/InvalidArgumentError.h>
#include <bump/OutOfRangeError.h>
#include <gtest/gtest.h>

#include <exception>
#include <string>

namespace bumpTest {

/**
 * Test fixture for the bump::Exception hierarchy. There is no shared state or
 * per-test setup, so the fixture exists only to group the suite.
 */
class ExceptionTest : public ::testing::Test {};

TEST_F(ExceptionTest, testCaughtAsStdException) {
    // The handler a consumer writes without knowing anything about bump.
    try {
        throw bump::InvalidArgumentError("a bad argument", BUMP_LOCATION);
    } catch (const std::exception& e) {
        EXPECT_NE(std::string(e.what()).find("a bad argument"),
                  std::string::npos);
    } catch (...) {
        FAIL() << "A bump exception was not caught as a std::exception, so a "
                  "consumer's ordinary catch handler misses it entirely.";
    }
}

TEST_F(ExceptionTest, testWhatMatchesDescription) {
    bump::InvalidArgumentError error("a bad argument", BUMP_LOCATION);
    EXPECT_STREQ(error.description().c_str(), error.what());
}

TEST_F(ExceptionTest, testExtendDescriptionReachesBoth) {
    // A re-throw appends a line. description() and what() are two views of one
    // piece of state, so neither may go stale when it changes.
    bump::OutOfRangeError error("the first throw", BUMP_LOCATION);
    error.extendDescription("the second throw", BUMP_LOCATION);

    const std::string description = error.description().toStdString();
    EXPECT_NE(description.find("the first throw"), std::string::npos);
    EXPECT_NE(description.find("the second throw"), std::string::npos);
    EXPECT_NE(description.find('\n'), std::string::npos);

    EXPECT_STREQ(description.c_str(), error.what());
}

TEST_F(ExceptionTest, testCaughtAsBumpExceptionBase) {
    // The hierarchy still works for a consumer that does know bump.
    try {
        throw bump::OutOfRangeError("out of range", BUMP_LOCATION);
    } catch (const bump::Exception& e) {
        EXPECT_NE(std::string(e.what()).find("out of range"),
                  std::string::npos);
    } catch (...) {
        FAIL() << "Not caught as a bump::Exception";
    }
}

}  // namespace bumpTest
