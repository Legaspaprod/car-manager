// utils.cpp
#include "utils.h"
#include <iostream>
#include <limits>

int safeInputInt(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Ошибка. Введите целое число: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return value;
}

std::string safeInputString(const std::string& prompt) {
    std::cout << prompt;
    return "";
}