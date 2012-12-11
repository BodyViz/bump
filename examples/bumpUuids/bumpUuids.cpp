//
//  bumpUuids.cpp
//  Bump
//
//  Created by Christian Noon on 11/19/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/String.h>
#include <bump/Uuid.h>

/**
 * This example demonstrates how to use the bump::Uuid class.
 *
 * The Bump Uuid class is used for storing Universally Unique Identifiers or UUIDs.
 * A UUID is typically used to identify unique entities throughout your code. This class
 * makes it easy to generate random UUIDs, as well as convert them to/from bump::Strings.
 */
int main(int argc, char **argv)
{
	// How to generate random uuids
	std::cout << "Generating random uuids:" << std::endl;
	for (unsigned int i = 0; i < 4; ++i)
	{
		bump::Uuid uuid = bump::Uuid::genarateRandom();
		std::cout << "- Random UUID: \"" << uuid.toString() << "\"" << std::endl;
	}

	// How to create uuids from strings
	std::cout << "\nCreating uuids from strings:" << std::endl;
	bump::Uuid uuid1 = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3");
	bump::Uuid uuid2 = bump::Uuid::fromString("c9226c75-2e16-4bad-bd27-f4b782869dfb");
	std::cout << "- UUID fromString: \"" << uuid1.toString() << "\"" << std::endl;
	std::cout << "- UUID fromString: \"" << uuid2.toString() << "\"" << std::endl;

	// How to create strings from uuids
	std::cout << "\nCreating strings from uuids:" << std::endl;
	bump::String uuid_str1 = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3").toString();
	bump::String uuid_str2 = bump::Uuid::fromString("c9226c75-2e16-4bad-bd27-f4b782869dfb").toString();
	std::cout << "- String from UUID: \"" << uuid_str1 << "\"" << std::endl;
	std::cout << "- String from UUID: \"" << uuid_str2 << "\"" << std::endl;

	// How to create null uuids (doubtful this will ever really come in handy)
	std::cout << "\nCreating null uuids:" << std::endl;
	bump::Uuid uuid3;
	bump::Uuid uuid4 = bump::Uuid();
	bump::Uuid uuid5 = bump::Uuid::fromString("00000000-0000-0000-0000-000000000000");
	bump::Uuid uuid6 = bump::Uuid::fromString("c9226c75-2e16-4bad-bd27-f4b782869dfb");
	std::cout << "- Is \"" << uuid3.toString() << "\" null: " << bump::String(uuid3.isNull()) << std::endl;
	std::cout << "- Is \"" << uuid4.toString() << "\" null: " << bump::String(uuid4.isNull()) << std::endl;
	std::cout << "- Is \"" << uuid5.toString() << "\" null: " << bump::String(uuid5.isNull()) << std::endl;
	std::cout << "- Is \"" << uuid6.toString() << "\" null: " << bump::String(uuid6.isNull()) << std::endl;

	// Using operators
	std::cout << "\nUsing UUID operators:" << std::endl;
	uuid1 = bump::Uuid::fromString("4605d211-2d5b-4ab4-8feb-d7c38e4e38c3");
	uuid2 = bump::Uuid::fromString("c9226c75-2e16-4bad-bd27-f4b782869dfb");
	std::cout << "- Are \"" << uuid1.toString() << "\" and \"" << uuid2.toString() << "\" equal : " << bump::String(uuid1 == uuid2) << std::endl;
	std::cout << "- Is \"" << uuid1.toString() << "\" less than \"" << uuid2.toString() << "\" : " << bump::String(uuid1 < uuid2) << std::endl;
	std::cout << "- Is \"" << uuid1.toString() << "\" greater than \"" << uuid2.toString() << "\" : " << bump::String(uuid1 > uuid2) << std::endl;

    return 0;
}
