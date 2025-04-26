#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include "Point2D.h"
#include "read_env.h"
#include <filesystem>

std::array<int, 2> readSize(std::string sizeLine) {
    std::array<int, 2> res;

    int j = 0;
    int beg = 0, len = 0;
    bool inNumber = false;
    for (int i = 0; i < sizeLine.size(); i++) {
        if (sizeLine[i] == ' ') {
            if (inNumber) {
                res[j] = std::stoi(sizeLine.substr(beg, len));
                j++;
            }

            inNumber = false;
            

            if (j > 1) {
                break;
            }

            continue;
        }

        if (!inNumber) {
            beg = i;
            len = 0;
            inNumber = true;
        }

        len++;
    }

    return res;
}

int main()
{
    // Файл с настройками
    std::map<std::string, std::string> env = ReadEnv();

    // Путь к папке программы
    std::string pointsFilePath = std::filesystem::current_path().string();

    // Название файла с данными, задаётся в файле .env
    // Пример: DATA_FILENAME='Airfoil for OpenVSP.dat'
    std::string pointsFileName = env["DATA_FILENAME"];

    // Поток чтения из файла
    std::ifstream pointsFileReadStream(pointsFilePath + "\\" + pointsFileName);
    
    std::string line;
    std::getline(pointsFileReadStream, line);
    std::getline(pointsFileReadStream, line);
    std::array<int, 2> res = readSize(line);
    int size1 = res[0];
    int size2 = res[1];
    std::getline(pointsFileReadStream, line);
    std::vector<Point2D> upperPoints(size1);
    for (int i = 0; i < size1; i++) {
        std::getline(pointsFileReadStream, line);
        int splitIndex = line.find(' ');
        upperPoints[i] = Point2D(std::stof(line.substr(0, splitIndex)), std::stof(line.substr(splitIndex + 1, line.size() - splitIndex - 1)));
    }

    std::vector<Point2D> downPoints(size2);
    for (int i = 0; i < size2; i++) {
        std::getline(pointsFileReadStream, line);
        int splitIndex = line.find(' ');
        downPoints[i] = Point2D(std::stof(line.substr(0, splitIndex)), std::stof(line.substr(splitIndex + 1, line.size() - splitIndex - 1)));
    }

    pointsFileReadStream.close();
}