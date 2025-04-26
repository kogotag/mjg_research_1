#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <fstream>
#include <array>

std::map<std::string, std::string> ReadEnv();
std::array<size_t, 2> FindCharIndexes(std::string str, char c, size_t pos = 0);
std::array<size_t, 2> FindSingleQuotesIndexes(std::string str, size_t pos = 0);
std::array<size_t, 2> FindDoubleQuotesIndexes(std::string str, size_t pos = 0);