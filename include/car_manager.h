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
    void addCar(); // 1
    void showCars() const; // 2
    void findCarByBrand() const;
    void removeCarByID(); // 3
    void saveToFile();
    void loadFromFile();
    void sortByPrice();
    void sortByPriceDescending();
    void findByPrice() const;
    void findByModel() const;
    void findByYear() const;
    void statistics();
    void editCar();
    void printCar(const Car& car, int index) const;
    void printHeader() const;
    void printAllCars(const std::vector<Car>& list) const;

    void addCar(const Car& car);
    Car* findCarById(int id); // 4
    bool removeCarById(int id);
    std::vector<Car> getAllCars() const;
};



#endif