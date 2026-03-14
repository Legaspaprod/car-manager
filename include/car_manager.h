#ifndef CAR_MANAGER_H
#define CAR_MANAGER_H

#include <vector>
#include "car.h"

class CarManager
{
private:
    std::vector<Car> cars;
    int nextid = 1;

    std::vector<Car>::iterator findCarIterator(const std::string& brand);

public:
    void addCar();
    void showCars() const;
    void findCarByBrand() const;
    void removeCarByBrand();
    void saveToFile();
    void loadFromFile();
    void sortByPrice();
    void sortByPriceDescending();
    void findByPrice();
};



#endif