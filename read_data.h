#pragma once

#include <fstream>
#include <string>
#include <array>

std::array<int, 2> ReadSize(std::ifstream& stream);
int FindNextNotSpaceSymbol(std::string str, int pos = 0);
int FindNextSpaceSymbol(std::string str, int pos = 0);