//
//	UuidTest.cpp
//	Bump
//
//	Created by Christian Noon on 11/19/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/uuid/uuid_io.hpp>

// Bump headers
#include <bump/String.h>
#include <bump/TypeCastError.h>
#include <bump/Uuid.h>

// bumpTest headers
#include "../bumpTest/BaseTest.h"

namespace bumpTest {

/**
 * This is our main uuid testing class. The SetUp and TearDown methods are
 * executed before the test runs and after it completes. This is where we can
 * add any custom set up for each test without having to add this to "every"
 * test individually.
 */
class UuidTest : public BaseTest
{
protected:

	/** Run immediately before a test starts. Starts the timer. */
	void SetUp()
	{
		// Call the parent setup method
		BaseTest::SetUp();

		// Any custom setup we may need
	}

	/** Invoked immediately after a test finishes. Stops the timer. */
	void TearDown()
	{
		// Call the parent tear down method
		BaseTest::TearDown();

		// Any custom teardown you may need
	}
};

TEST_F(UuidTest, testEmptyConstructor)
{
	// Create two default uuids
	bump::Uuid uuid1;
	bump::Uuid uuid2 = bump::Uuid();

	// Test the string versions
	EXPECT_STREQ("00000000-0000-0000-0000-000000000000", uuid1.toString().c_str());
	EXPECT_STREQ("00000000-0000-0000-0000-000000000000", uuid2.toString().c_str());

	// Make sure they are null
	EXPECT_TRUE(uuid1.isNull());
	EXPECT_TRUE(uuid2.isNull());

	// Test the boost is_nil function as well
	EXPECT_TRUE(uuid1.is_nil());
	EXPECT_TRUE(uuid2.is_nil());
}

TEST_F(UuidTest, testCopyConstructorUuid)
{
	// Create a uuid and use the copy constructor to create a second
	bump::Uuid uuid1;
	bump::Uuid uuid2 = bump::Uuid(uuid1);

	// Test the string versions
	EXPECT_STREQ("00000000-0000-0000-0000-000000000000", uuid1.toString().c_str());
	EXPECT_STREQ("00000000-0000-0000-0000-000000000000", uuid2.toString().c_str());

	// Make sure they are equal
	EXPECT_TRUE(uuid1 == uuid2);

	// Try the same thing with a randomly generated uuid
	uuid1 = bump::Uuid::genarateRandom();
	uuid2 = bump::Uuid(uuid1);
	EXPECT_STREQ(uuid1.toString().c_str(), uuid2.toString().c_str());
}

TEST_F(UuidTest, testCopyConstructorBoost)
{
	// Create a uuid and use the copy constructor to create a second
	boost::uuids::uuid uuid1;
	bump::Uuid uuid2 = bump::Uuid(uuid1);

	// Test the string versions
	EXPECT_STREQ(boost::uuids::to_string(uuid1).c_str(), uuid2.toString().c_str());
}

TEST_F(UuidTest, testGenerateRandom)
{
	// Randomly generate 20 uuids and make sure they're all different
	std::set<bump::String> uuid_counts;
	for (unsigned int i = 0; i < 20; ++i)
	{
		// Generate the uuid and the uuid string
		bump::Uuid uuid = bump::Uuid::genarateRandom();
		bump::String uuid_str = uuid.toString();

		// Make sure it isn't null
		EXPECT_FALSE(uuid.isNull());

		// Make sure it hasn't already been generated
		EXPECT_EQ(0, (int)uuid_counts.count(uuid_str));

		// Store it for the next check
		uuid_counts.insert(uuid_str);
	}
}

TEST_F(UuidTest, testFromString)
{
	// Create a null uuid from a string
	bump::Uuid uuid = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	EXPECT_STREQ("00000000-0000-0000-0000-000000000000", uuid.toString().c_str());
	EXPECT_TRUE(uuid.isNull());
	uuid = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3");
	EXPECT_STREQ("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3", uuid.toString().c_str());
	EXPECT_FALSE(uuid.isNull());

	// Try with brackets
	uuid = bump::Uuid::fromString("{4605d211-2d5b-4ab4-8feb-d7c38e4e38c3}");
	EXPECT_STREQ("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3", uuid.toString().c_str());
	EXPECT_FALSE(uuid.isNull());

	// Test an invalid string
	EXPECT_THROW(bump::Uuid::fromString("this is NOT valid"), bump::TypeCastError);
}

TEST_F(UuidTest, testIsNull)
{
	// Create a default uuid
	bump::Uuid uuid;
	EXPECT_TRUE(uuid.isNull());

	// Create a null uuid from a string
	uuid = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	EXPECT_TRUE(uuid.isNull());

	// Create a valid uuid from a string
	uuid = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3");
	EXPECT_FALSE(uuid.isNull());
}

TEST_F(UuidTest, testEqualToOperator)
{
	// Create two null uuids
	bump::Uuid uuid1;
	bump::Uuid uuid2;
	EXPECT_TRUE(uuid1 == uuid2);

	// Create two null uuids from strings
	uuid1 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	uuid2 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	EXPECT_TRUE(uuid1 == uuid2);

	// Create two random uuids
	uuid1 = bump::Uuid::genarateRandom();
	uuid2 = bump::Uuid::genarateRandom();
	EXPECT_FALSE(uuid1 == uuid2);

	// Create two different uuids from strings
	uuid1 = bump::Uuid::fromString("c9226c75-2e16-4bad-bd27-f4b782869dfb");
	uuid2 = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3");
	EXPECT_FALSE(uuid1 == uuid2);
}

TEST_F(UuidTest, testNotEqualOperator)
{
	// Create two null uuids
	bump::Uuid uuid1;
	bump::Uuid uuid2;
	EXPECT_FALSE(uuid1 != uuid2);

	// Create two null uuids from strings
	uuid1 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	uuid2 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	EXPECT_FALSE(uuid1 != uuid2);

	// Create two random uuids
	uuid1 = bump::Uuid::genarateRandom();
	uuid2 = bump::Uuid::genarateRandom();
	EXPECT_TRUE(uuid1 != uuid2);

	// Create two different uuids from strings
	uuid1 = bump::Uuid::fromString("c9226c75-2e16-4bad-bd27-f4b782869dfb");
	uuid2 = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3");
	EXPECT_TRUE(uuid1 != uuid2);
}

TEST_F(UuidTest, testLessThanOperator)
{
	// Create two null uuids
	bump::Uuid uuid1;
	bump::Uuid uuid2;
	EXPECT_FALSE(uuid1 < uuid2);

	// Create two null uuids from strings
	uuid1 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	uuid2 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	EXPECT_FALSE(uuid1 < uuid2);

	// Create two different uuids from strings
	uuid1 = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3");
	uuid2 = bump::Uuid::fromString("c9226c75-2e16-4bad-bd27-f4b782869dfb");
	EXPECT_TRUE(uuid1 < uuid2);
}

TEST_F(UuidTest, testGreaterThanOperator)
{
	// Create two null uuids
	bump::Uuid uuid1;
	bump::Uuid uuid2;
	EXPECT_FALSE(uuid1 > uuid2);

	// Create two null uuids from strings
	uuid1 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	uuid2 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	EXPECT_FALSE(uuid1 > uuid2);

	// Create two different uuids from strings
	uuid1 = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3");
	uuid2 = bump::Uuid::fromString("c9226c75-2e16-4bad-bd27-f4b782869dfb");
	EXPECT_FALSE(uuid1 > uuid2);
}

TEST_F(UuidTest, testLessThanOrEqualToOperator)
{
	// Create two null uuids
	bump::Uuid uuid1;
	bump::Uuid uuid2;
	EXPECT_TRUE(uuid1 <= uuid2);

	// Create two null uuids from strings
	uuid1 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	uuid2 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	EXPECT_TRUE(uuid1 <= uuid2);

	// Create two different uuids from strings
	uuid1 = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3");
	uuid2 = bump::Uuid::fromString("c9226c75-2e16-4bad-bd27-f4b782869dfb");
	EXPECT_TRUE(uuid1 <= uuid2);
}

TEST_F(UuidTest, testGreaterThanOrEqualToOperator)
{
	// Create two null uuids
	bump::Uuid uuid1;
	bump::Uuid uuid2;
	EXPECT_TRUE(uuid1 >= uuid2);

	// Create two null uuids from strings
	uuid1 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	uuid2 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	EXPECT_TRUE(uuid1 >= uuid2);

	// Create two different uuids from strings
	uuid1 = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3");
	uuid2 = bump::Uuid::fromString("c9226c75-2e16-4bad-bd27-f4b782869dfb");
	EXPECT_FALSE(uuid1 >= uuid2);
}

}	// End of bumpTest namespace
