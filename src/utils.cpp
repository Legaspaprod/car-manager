// utils.cpp
#include "utils.h"
#include <iostream>
#include <limits>

int safeInputInt(const std::string& prompt) {
    std::cout << prompt;
    return 0;
}

std::string safeInputString(const std::string& prompt) {
    std::cout << prompt;
    return "";
}