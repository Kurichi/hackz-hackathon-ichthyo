#pragma once
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

/*
やり取りするデータの構造
----------------------
[name]
[id]
[division_index]
[division_count]
[のこりデータ]

----------------------
*/

namespace Util {
	struct ReceivedData {
		struct User {
			std::string name;
			std::string uuid;
		} user;

		struct Division {
			int index;
			int count;
		} division;

		std::string data;

		ReceivedData(const std::string& receivedData) :
			user{ "", "" },
			division{ 0, 0 }
		{
			std::stringstream ss(receivedData);

			std::string tmpStr;
			std::getline(ss, tmpStr);
			user.name = tmpStr;
			std::getline(ss, tmpStr);
			user.uuid = tmpStr;
			std::getline(ss, tmpStr);
			try {
				division.index = boost::lexical_cast<int>(tmpStr);
				std::getline(ss, tmpStr);
				division.count = boost::lexical_cast<int>(tmpStr);
			}
			catch (boost::bad_lexical_cast& e) {
				division.index = -1;
				division.count = -1;
			}
			this->data = std::string{ std::istreambuf_iterator<char>(ss),std::istreambuf_iterator<char>() };


		}
	};

	void CreateWav(const std::string& path, const std::string& data) {
		std::ofstream ofs(path, std::ios::binary);
		ofs << data;
	}

	void ReadBinary(std::string& data, const std::string& path) {
		data = "";
		std::ifstream ifs(path, std::ios::binary);
		if (!ifs) {
			return;
		}
		data = std::string{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
	}
}


