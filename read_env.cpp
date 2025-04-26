#include "read_env.h"

std::map<std::string, std::string> ReadEnv()
{
	std::map<std::string, std::string> map;
	std::filesystem::path path = std::filesystem::current_path();

	std::ifstream readStream(path.string() + "\\.env");

	std::string line;
	while (std::getline(readStream, line)) {
		size_t eq_pos = line.find('=');
		if (eq_pos < 0) {
			continue;
		}

		std::string key = line.substr(0, eq_pos);
		std::array<size_t, 2> quotesIndexes = FindSingleQuotesIndexes(line, eq_pos);
		if (quotesIndexes[0] < 0 || quotesIndexes[1] < 0) {
			quotesIndexes = FindDoubleQuotesIndexes(line, eq_pos);
		}

		if (quotesIndexes[0] < 0 || quotesIndexes[1] < 0) {
			continue;
		}

		std::string val = line.substr(quotesIndexes[0] + 1, quotesIndexes[1] - 1);
		map[key] = val;
	}

	readStream.close();

	return map;
}

std::array<size_t, 2> FindCharIndexes(std::string str, char c, size_t pos) {
	std::array<size_t, 2> res{};
	res[0] = str.find(c, pos);
	res[1] = str.find(c, res[0] + 1) - res[0];
	return res;
}

std::array<size_t, 2> FindSingleQuotesIndexes(std::string str, size_t pos) {
	return FindCharIndexes(str, '\'', pos);
}

std::array<size_t, 2> FindDoubleQuotesIndexes(std::string str, size_t pos) {
	return FindCharIndexes(str, '\"', pos);
}