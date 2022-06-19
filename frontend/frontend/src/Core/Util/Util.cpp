#include "Core/Util.h"
namespace Util {
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
