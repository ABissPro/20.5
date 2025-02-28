#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    system("chcp 1251"); // Установить кодировку

    //речка
    std::ifstream river("C:\\Users\\user\\Documents\\Программы\\cpp\\20.5\\3. Симуляция игры «Рыбалка»\\river.txt");
    if (!river.is_open()) {
        std::cerr << "Ошибка открытия файла " << std::endl;
        return 1;
    }

    std::string target_fish;
    std::cout << "Введите название рыбы, которую хотите поймать: ";
    std::getline(std::cin, target_fish);

    std::vector<std::string> caught_fishes;

    std::string fish;
    while (std::getline(river, fish)) {
        if (fish == target_fish) {
            caught_fishes.push_back(fish);
        }
    }
    river.close();

    //корзинка
    std::ofstream basket("C:\\Users\\user\\Documents\\Программы\\cpp\\20.5\\3. Симуляция игры «Рыбалка»\\basket.txt", std::ios::app);
    if (!basket.is_open()) {
        std::cerr << "Ошибка открытия файла " << std::endl;
        return 1;
    }

    for (const auto& fish : caught_fishes) {
        basket << fish << std::endl;
    }
    basket.close();

    std::cout << "Поймано " << caught_fishes.size() << " штук рыбы " << target_fish << "." << std::endl;

    return 0;
}
