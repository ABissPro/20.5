#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    system("chcp 1251"); // Установить кодировку
    //начальное зерно для генератора случайных чисел от текущего времени
    srand(static_cast<unsigned>(time(nullptr)));

    int height, width;
    std::cout << "Введите высоту и ширину картины в пикселях: ";
    std::cin >> height >> width;

    std::ofstream picture("C:\\Users\\user\\Documents\\Программы\\cpp\\20.5\\2. Рисование случайных картин\\pic.txt");
    if (!picture.is_open()) {
        std::cerr << "Не удалось открыть файл для записи.\n";
        return 1;
    }

    // Генерация случайных нулей и единиц для каждого пикселя
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            picture << (rand() % 2 ? '1' : '0');
        }
        picture << '\n';  // Переход на новую строку после завершения строки пикселей
    }

    picture.close();

    std::cout << "Картина создана и сохранена в файле pic.txt\n";
    return 0;
}
