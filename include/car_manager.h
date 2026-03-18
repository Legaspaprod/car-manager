#ifndef CAR_MANAGER_H
#define CAR_MANAGER_H

#include <vector>
#include "car.h"

class CarManager
{
private:
    std::vector<Car> cars;
    int nextid = 1;

public:
    void addCar();
    void showCars() const;
    void findCarByBrand() const;
    void removeCarByID();
    void saveToFile();
    void loadFromFile();
    void sortByPrice();
    void sortByPriceDescending();
    void findByPrice() const;
    void findByModel() const;
    void findByYear() const;
    void statistics();
    void editCar();
};



#endif