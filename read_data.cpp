#include "read_data.h"

/*
�������, ����������� ������� �������� ����� �� 2-�� ������� .dat �����
*/
std::array<int, 2> ReadSize(std::ifstream& stream)
{
	std::array<int, 2> res;
	std::string line;

	// ������ ������ ������, � ��� ����� ������ ���������
	std::getline(stream, line);
	// ������ ������ ������, � ��� �������
	std::getline(stream, line);

	int substrIndexes[2];
	// 2-�� ������ �� ������ ���� ������
	if (line.empty()) {
		throw std::runtime_error("Line 2 in .dat must contain lengths of points arrays");
	}

	// ���� ��������� ��-������
	substrIndexes[0] = FindNextNotSpaceSymbol(line, 0);
	// ����� ���� ���� ��������� ������
	substrIndexes[1] = FindNextSpaceSymbol(line, substrIndexes[0]);
	// ��� �������� �������� ����� �� ������

	// ���� �� �����, ��, ��������, ����� ��������� �� ���������.
	// ��� �� ��������� ������ �����...
	if (substrIndexes[0] == -1 || substrIndexes[1] == -1) {
		throw std::runtime_error("Expected space delimiter symbols in .dat file in line 2");
	}

	// �������� ������ �����
	res[0] = std::stoi(line.substr(substrIndexes[0], substrIndexes[1] - substrIndexes[0]));

	// �������� ������ �����
	substrIndexes[0] = FindNextNotSpaceSymbol(line, substrIndexes[1]);
	substrIndexes[1] = line.size() - 1;

	if (substrIndexes[0] == -1) {
		throw std::runtime_error("Expected space delimiter symbols in .dat file in line 2");
	}

	res[1] = std::stoi(line.substr(substrIndexes[0], substrIndexes[1] - substrIndexes[0]));

	return res;
}

/*
����� ������� ���������� ��-������� � ������
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
����� ������� ���������� ������� � ������
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
