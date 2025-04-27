#include "read_data.h"

/*
Функция, считывающая размеры массивов точек из 2-ой строчки .dat файла
*/
std::array<int, 2> ReadSize(std::ifstream& stream)
{
	std::array<int, 2> res;
	std::string line;

	// Читаем первую строку, в ней вроде ничего полезного
	std::getline(stream, line);
	// Читаем вторую строку, в ней размеры
	std::getline(stream, line);

	int substrIndexes[2];
	// 2-ая строка не должна быть пустой
	if (line.empty()) {
		throw std::runtime_error("Line 2 in .dat must contain lengths of points arrays");
	}

	// Ищем ближайший не-пробел
	substrIndexes[0] = FindNextNotSpaceSymbol(line, 0);
	// После него ищем ближайший пробел
	substrIndexes[1] = FindNextSpaceSymbol(line, substrIndexes[0]);
	// Это позволит вырезать число из строки

	// Если не нашли, то, возможно, числа разделены не пробелами.
	// Это не ожидаемый формат файла...
	if (substrIndexes[0] == -1 || substrIndexes[1] == -1) {
		throw std::runtime_error("Expected space delimiter symbols in .dat file in line 2");
	}

	// Вырезаем первое число
	res[0] = std::stoi(line.substr(substrIndexes[0], substrIndexes[1] - substrIndexes[0]));

	// Вырезаем второе число
	substrIndexes[0] = FindNextNotSpaceSymbol(line, substrIndexes[1]);
	substrIndexes[1] = line.size() - 1;

	if (substrIndexes[0] == -1) {
		throw std::runtime_error("Expected space delimiter symbols in .dat file in line 2");
	}

	res[1] = std::stoi(line.substr(substrIndexes[0], substrIndexes[1] - substrIndexes[0]));

	return res;
}

/*
Найти позицию следующего не-пробела в строке
*/
int FindNextNotSpaceSymbol(std::string str, int pos)
{
	if (str.empty()) {
		return -1;
	}

	int i = pos;
	char c = str[pos];
	while (c == ' ') {
		i++;
		if (i >= str.size()) {
			return -1;
		}
		c = str[i];
	}

	return i;
}

/*
Найти позицию следующего пробела в строке
*/
int FindNextSpaceSymbol(std::string str, int pos)
{
	if (str.empty()) {
		return -1;
	}

	int i = pos;
	char c = str[pos];
	while (c != ' ') {
		i++;
		if (i >= str.size()) {
			return -1;
		}
		c = str[i];
	}

	return i;
}
