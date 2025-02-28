#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

bool isValidDate(const std::string& dateStr) {
    if (dateStr.length() != 10 || dateStr[2] != '.' || dateStr[5] != '.') {
        return false;
    }

    try {
        int day = std::stoi(dateStr.substr(0, 2));
        int month = std::stoi(dateStr.substr(3, 2));
        int year = std::stoi(dateStr.substr(6, 4));

        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2025) {
            return false;
        }
    }
    catch (...) {
        return false;
    }

    return true;
}

void addRecordToFile(const std::string& fullName, const std::string& date, double amount) {
    std::ofstream list("C:\\Users\\user\\Documents\\Программы\\cpp\\20.5\\1. Запись в ведомость\\list.txt", std::ios::app);
    if (!list.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    // Добавляем новую запись в файл
    list << fullName << " " << amount << " " << date << "\n";
    list.close();
}

int main() {
    system("chcp 1251"); // Установить кодировку
    
    std::cout << "Введите ФИО получателя: ";
    std::string fullName;
    std::getline(std::cin, fullName);

    std::cout << "Введите дату в формате ДД.ММ.ГГГГ: ";
    std::string date;
    std::getline(std::cin, date);

    if (!isValidDate(date)) {
        std::cerr << "Неверный формат даты" << std::endl;
        return 1;
    }

    std::cout << "Введите сумму выплаты: ";
    double amount;
    std::cin >> amount;

    addRecordToFile(fullName, date, amount);

    std::cout << "Запись успешно добавлена в файл." << std::endl;

    return 0;
}
