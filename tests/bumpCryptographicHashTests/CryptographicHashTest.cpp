//
//	CryptographicHashTest.cpp
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#include <bump/CryptographicHash.h>
#include <bump/Environment.h>
#include <gtest/gtest.h>

#include <cstring>

namespace bumpTest {

/**
 * Test fixture for the bump::CryptographicHash class. There is no shared state
 * or per-test setup, so the fixture exists only to group the suite.
 */
class CryptographicHashTest : public ::testing::Test {};

TEST_F(CryptographicHashTest, testSetDataString) {
    // Normal case #1
    bump::CryptographicHash hash;
    bump::String data = "This is a simple string that I'm going to hash";
    hash.setData(data);
    bump::String result = hash.result();
    EXPECT_STREQ("364fd3e0c0c454cb0c0fb393ede75f7f66b28eb6", result.c_str());

    // Normal case #2
    hash = bump::CryptographicHash();
    data = "Let's try another one with some numbers: 98 730384 93.48390";
    hash.setData(data);
    result = hash.result();
    EXPECT_STREQ("4e5afbcbc9701c5db9a61daea6f7f5760bf44652", result.c_str());

    // String created with a double
    hash = bump::CryptographicHash();
    double number = 98.047384;
    data = bump::String(number);
    hash.setData(data);
    result = hash.result();
    EXPECT_STREQ("635bba26166e81450efee4a9bcd8b9ade60c0ee5", result.c_str());

    // Empty case
    hash = bump::CryptographicHash();
    data = "";
    hash.setData(data);
    result = hash.result();
    EXPECT_STREQ("", result.c_str());
}

TEST_F(CryptographicHashTest, testSetDataStringLifetime) {
    // The same content as testSetDataString's first case, so the expected hash
    // is the one that case already pins down.
    const char* const text = "This is a simple string that I'm going to hash";
    const char* const expected = "364fd3e0c0c454cb0c0fb393ede75f7f66b28eb6";

    // A temporary. String has a non-explicit constructor from const char*, so
    // this is what the obvious one-argument call actually does.
    bump::CryptographicHash hash;
    hash.setData(text);
    EXPECT_STREQ(expected, hash.result().c_str());

    // An explicit temporary, which dies at the end of the full expression
    hash = bump::CryptographicHash();
    hash.setData(bump::String(text));
    EXPECT_STREQ(expected, hash.result().c_str());

    // The result of an expression, which is the same thing a caller writes when
    // building the input inline
    hash = bump::CryptographicHash();
    hash.setData(bump::String("This is a simple string ") +
                 bump::String("that I'm going to hash"));
    EXPECT_STREQ(expected, hash.result().c_str());

    // A named string that outlives the call but is reassigned before the hash
    // is asked for. Nothing here is a temporary; the data still has to have
    // been taken at setData time.
    hash = bump::CryptographicHash();
    bump::String data = text;
    hash.setData(data);
    data =
        "a completely different and rather longer string, forcing the "
        "original buffer to be given up";
    EXPECT_STREQ(expected, hash.result().c_str());
}

TEST_F(CryptographicHashTest, testSetDataCharStar) {
    // Normal case #1
    bump::CryptographicHash hash;
    const char* data = "This is a simple string that I'm going to hash";
    hash.setData(data, static_cast<int>(std::strlen(data)));
    bump::String result = hash.result();
    EXPECT_STREQ("364fd3e0c0c454cb0c0fb393ede75f7f66b28eb6", result.c_str());

    // Normal case #2
    hash = bump::CryptographicHash();
    data = "Let's try another one with some numbers: 98 730384 93.48390";
    hash.setData(data, static_cast<int>(std::strlen(data)));
    result = hash.result();
    EXPECT_STREQ("4e5afbcbc9701c5db9a61daea6f7f5760bf44652", result.c_str());

    // String created with a double
    hash = bump::CryptographicHash();
    data = "98.047384";
    hash.setData(data, static_cast<int>(std::strlen(data)));
    result = hash.result();
    EXPECT_STREQ("3f44cca1bbe945abf54da6c0f65cd8bcad6a9eb2", result.c_str());

    // Empty case
    hash = bump::CryptographicHash();
    data = "";
    hash.setData(data, static_cast<int>(std::strlen(data)));
    result = hash.result();
    EXPECT_STREQ("", result.c_str());
}

TEST_F(CryptographicHashTest, testReset) {
    // Normal case #1
    bump::CryptographicHash hash;
    const char* data = "This is a simple string that I'm going to hash";
    hash.setData(data, static_cast<int>(std::strlen(data)));
    bump::String result = hash.result();
    EXPECT_STREQ("364fd3e0c0c454cb0c0fb393ede75f7f66b28eb6", result.c_str());

    // Normal case #2
    data = "Let's try another one with some numbers: 98 730384 93.48390";
    hash.reset();
    hash.setData(data, static_cast<int>(std::strlen(data)));
    result = hash.result();
    EXPECT_STREQ("4e5afbcbc9701c5db9a61daea6f7f5760bf44652", result.c_str());

    // String created with a double
    data = "98.047384";
    hash.reset();
    hash.setData(data, static_cast<int>(std::strlen(data)));
    result = hash.result();
    EXPECT_STREQ("3f44cca1bbe945abf54da6c0f65cd8bcad6a9eb2", result.c_str());

    // Empty case
    data = "";
    hash.reset();
    hash.setData(data, static_cast<int>(std::strlen(data)));
    result = hash.result();
    EXPECT_STREQ("", result.c_str());
}

TEST_F(CryptographicHashTest, testResult) {
    // Normal case
    bump::CryptographicHash hash;
    bump::String data = "This is a simple string that I'm going to hash";
    hash.setData(data);
    bump::String result = hash.result();
    EXPECT_STREQ("364fd3e0c0c454cb0c0fb393ede75f7f66b28eb6", result.c_str());

    // Empty case
    data = "";
    hash.reset();
    hash.setData(data);
    result = hash.result();
    EXPECT_STREQ("", result.c_str());

    // Char array case
    hash = bump::CryptographicHash();
    unsigned char values_char[10];
    values_char[0] = 55;
    values_char[1] = 0;
    values_char[2] = 255;
    values_char[3] = 19;
    values_char[4] = 3;
    values_char[5] = 206;
    values_char[6] = 17;
    values_char[7] = 68;
    values_char[8] = 27;
    values_char[9] = 107;
    hash.setData(reinterpret_cast<char*>(values_char), 10);
    result = hash.result();
    EXPECT_STREQ("884095846c4f9390655c48ee2819da470b35fb60", result.c_str());

    // Short array case
    hash = bump::CryptographicHash();
    short values_short[5];
    values_short[0] = -3084;
    values_short[1] = 27;
    values_short[2] = 20676;
    values_short[3] = 1047;
    values_short[4] = -10;
    hash.setData(reinterpret_cast<char*>(values_short), 10);
    result = hash.result();
    EXPECT_STREQ("bc1ed3c73cb98a7c3742a0f41e6e703f4472f679", result.c_str());
}

}  // namespace bumpTest
