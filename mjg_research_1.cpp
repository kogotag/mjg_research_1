#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include <list>
#include <filesystem>
#include "Point2D.h"
#include "read_env.h"
#include "read_data.h"

int main()
{
    // Файл с настройками
    std::map<std::string, std::string> env = ReadEnv();

    // Путь к папке программы
    // Либо проверяем путь в .env, либо используем папку программы
    std::string pointsFilePath = env["DATA_PATH"];
    if (pointsFilePath.empty()) {
        pointsFilePath = std::filesystem::current_path().string();
    }

    // Название файла с данными, задаётся в файле .env
    // Пример: DATA_FILENAME='Airfoil for OpenVSP.dat'
    std::string pointsFileName = env["DATA_FILENAME"];

    // Поток чтения из файла
    std::ifstream readStream(pointsFilePath + "\\" + pointsFileName);
    
    // Прочитали из второй строки размеры массивов точек
    std::array<int, 2> size = ReadSize(readStream);
    
    // Буфер построчного чтения
    std::string line;

    // Одна строка пустая
    std::getline(readStream, line);

    // Временный список точек в порядке считывания файла
    std::list<Point2D> temp;
    // Заполняем список точками верхней части профиля, обход по часовой
    for (int i = 0; i < size[0]; i++) {
        std::getline(readStream, line);
        int splitIndex = line.find('\t');
        temp.push_back(Point2D(std::stof(line.substr(0, splitIndex)), std::stof(line.substr(splitIndex + 1, line.size() - splitIndex - 1))));
    }

    // Итоговый "список" точек от (1, 0) против часовой
    std::vector<Point2D> points;
    // Резервируем память под точки для быстрого заполнения
    points.reserve(size[0] + size[1]);

    // Копируем точки из верхней части профиля в обратном порядке — против часовой от (1, 0)
    for (auto iter = temp.rbegin(); iter != temp.rend(); ++iter) {
        points.push_back(*iter);
    }

    // Очищаем временный список
    temp.clear();
    // Пропускаем пустую строчку
    std::getline(readStream, line);

    // Заполняем список точками верхней части профиля, обход по часовой
    for (int i = 0; i < size[1]; i++) {
        std::getline(readStream, line);
        int splitIndex = line.find('\t');
        points.push_back(Point2D(std::stof(line.substr(0, splitIndex)), std::stof(line.substr(splitIndex + 1, line.size() - splitIndex - 1))));
    }

    // Закрываем поток чтения файла
    readStream.close();

    for (auto iter = points.begin(); iter != points.end(); iter++) {
        std::cout << (*iter).string() << std::endl;
    }
}