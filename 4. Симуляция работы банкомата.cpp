#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

const int nominals[] = { 100, 200, 500, 1000, 2000, 5000 };
const int num_nominals = 6;
int counts[num_nominals] = { 0 };

//генератор случайных чисел
static unsigned int rand_seed = time(0);

int simple_rand() {
    rand_seed = rand_seed * 1103515245 + 12345;
    return (rand_seed >> 16) & 32767;
}

int totalBanknotes() {
    int total = 0;
    for (int i = 0; i < num_nominals; ++i) total += counts[i];
    return total;
}

int totalAmount() {
    int total = 0;
    for (int i = 0; i < num_nominals; ++i)
        total += counts[i] * nominals[i];
    return total;
}

void loadState(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return;

    std::vector<int> atm(1000);
    file.read(reinterpret_cast<char*>(atm.data()), 1000 * sizeof(int));
    file.close();

    for (int value : atm) {
        for (int i = 0; i < num_nominals; ++i) {
            if (value == nominals[i]) {
                counts[i]++;
                break;
            }
        }
    }
}

void saveState(const std::string& filename) {
    std::vector<int> atm;
    for (int i = 0; i < num_nominals; ++i) {
        for (int j = 0; j < counts[i]; ++j) {
            atm.push_back(nominals[i]);
        }
    }
    atm.resize(1000, 0);

    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(atm.data()), 1000 * sizeof(int));
    file.close();
}

void refillATM() {
    int current = totalBanknotes();
    if (current >= 1000) {
        std::cout << "Банкомат уже полон.\n";
        return;
    }

    for (int i = 0; i < 1000 - current; ++i) {
        counts[simple_rand() % num_nominals]++;
    }

    std::cout << "Состояние банкомата:\n";
    for (int i = 0; i < num_nominals; ++i)
        std::cout << nominals[i] << ": " << counts[i] << "\n";
    std::cout << "Общая сумма: " << totalAmount() << "\n\n";
}

void withdraw(int amount) {
    if (amount % 100 != 0) {
        std::cout << "Сумма должна быть кратна 100.\n";
        return;
    }

    int remaining = amount;
    int temp[num_nominals] = { 0 };

    for (int i = num_nominals - 1; i >= 0; --i) {
        int possible = remaining / nominals[i];
        possible = (possible < counts[i]) ? possible : counts[i];

        if (possible > 0) {
            temp[i] = possible;
            remaining -= possible * nominals[i];
            counts[i] -= possible;
        }
    }

    if (remaining != 0) {
        for (int i = 0; i < num_nominals; ++i) counts[i] += temp[i];
        std::cout << "Операция невозможна.\n\n";
        return;
    }

    std::cout << "Выдано:\n";
    for (int i = num_nominals - 1; i >= 0; --i)
        if (temp[i] > 0) std::cout << nominals[i] << ": " << temp[i] << "\n";
    std::cout << "Остаток: " << totalAmount() << "\n\n";
}

int main() {
    loadState("atm.bin");
    system("chcp 1251"); // Установить кодировку

    std::cout << "Текущее состояние:\n";
    for (int i = 0; i < num_nominals; ++i)
        std::cout << nominals[i] << ": " << counts[i] << "\n";
    std::cout << "Всего: " << totalAmount() << "\n\n";

    char cmd;
    while (true) {
        std::cout << "Введите команду (+/-/q): ";
        std::cin >> cmd;

        if (cmd == '+') refillATM();
        else if (cmd == '-') {
            int sum;
            std::cout << "Введите сумму: ";
            std::cin >> sum;
            if (sum > 0 && sum <= totalAmount()) withdraw(sum);
            else std::cout << "Некорректная сумма!\n\n";
        }
        else if (cmd == 'q') break;
        else std::cout << "Неизвестная команда!\n\n";
    }

    saveState("atm.bin");
    return 0;
}
