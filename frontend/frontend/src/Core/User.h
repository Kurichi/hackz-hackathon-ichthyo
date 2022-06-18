#pragma once
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

struct User {
	std::string name;
	std::string uuids;
	User(const std::string& namae) {
		const boost::uuids::uuid u1 = boost::uuids::random_generator()();
		uuids = boost::lexical_cast<std::string>(u1);
		name = namae;
	}
};
