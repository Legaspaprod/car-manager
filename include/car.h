#ifndef CAR_H
#define CAR_H

#include <string>

struct Car {
    int id;
    std::string brand;
    std::string model;
    int year;
    int price{};
};

#endif