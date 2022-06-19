#pragma once
#define BOOST_UUID_RANDOM_PROVIDER_FORCE_WINCRYPT
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

struct User {
	std::string name;
	std::string uuids;
	int iconIndex;

	User(const std::string& name, const std::string& uuid):
		name(name),
		uuids(uuid),
		iconIndex(0)
	{	}
	
	User(const std::string& name) :
		name(name),
		uuids(),
		iconIndex(0)
	{
		this->GenerateUUID();
	}

	void GenerateUUID() {
		this->uuids = boost::lexical_cast<std::string>(boost::uuids::random_generator{}());
	}
};
