#include "Core/User/SingletonUserArray.h"

std::shared_ptr<Array<User>> SingletonUserArray::userArray{new Array<User>()};

bool SingletonUserArray::RegisterUser(const User& user) {
	for (auto& u : *userArray) {
		if (u.uuids == user.uuids) {
			return false;
		}
	}
	userArray->emplace_back(user);
	return true;
}

User* SingletonUserArray::Search(const User& user) {
	for (auto& u : *userArray) {
		if (u.uuids == user.uuids) {
			return &u;
		}
		return nullptr;
	}

}
