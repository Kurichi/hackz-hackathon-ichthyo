#pragma once
#include "Core/User.h"

class SingletonUserArray {
private:
	static std::shared_ptr<Array<User>> userArray;
	SingletonUserArray();
public:
	static std::shared_ptr<Array<User>> Get() {
		return userArray;
	}
	bool RegisterUser(const User& user);
	User* Search(const User& user);

};
