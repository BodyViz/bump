//
//	Uuid.cpp
//	Bump
//
//	Created by Christian Noon on 11/19/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

// Bump headers
#include <bump/Exception.h>
#include <bump/String.h>
#include <bump/Uuid.h>

using namespace bump;

Uuid::Uuid() : boost::uuids::uuid(boost::uuids::nil_uuid())
{
	;
}

Uuid::Uuid(const Uuid& uuid) : boost::uuids::uuid(uuid)
{
	;
}

Uuid::Uuid(const boost::uuids::uuid& uuid) : boost::uuids::uuid(uuid)
{
	;
}

Uuid::~Uuid()
{
	;
}

Uuid Uuid::genarateRandom()
{
	boost::uuids::random_generator generator;
	boost::uuids::uuid uuid = generator();
	return uuid;
}

Uuid Uuid::fromString(const String& uuidString)
{
	try
	{
		boost::uuids::string_generator generator;
		return generator(uuidString);
	}
	catch (const std::exception& e)
	{
		throw TypeCastError(String("Could not convert %1 to uuid").arg(uuidString), BUMP_LOCATION);
	}
}

bool Uuid::isNull() const
{
	return boost::uuids::uuid::is_nil();
}

String Uuid::toString() const
{
	return boost::uuids::to_string(*this);
}
