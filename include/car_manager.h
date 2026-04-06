#ifndef CAR_MANAGER_H
#define CAR_MANAGER_H

#include <vector>
#include <string>
#include "car.h"
#include "database.h"

class CarManager {
private:
    std::vector<Car> cars;
    int nextid = 1;
    Database& db;

public:
    explicit CarManager(Database& database);
    ~CarManager();
    
    // Работа с БД
    void loadFromDB();
    void saveToDB();
    
    // CRUD операции
    void addCar(const Car& car);
    void editCar(int id, int field, const std::string& value);
    void editCar(int id, int field, int value);
    bool removeCarById(int id);
    void findCarById(int id) const;
    
    // Поиск и фильтрация
    void findCarByBrand() const;
    void findByModel() const;
    void findByYear() const;
    void findByPrice() const;
    
    // Отображение
    void showCars() const;
    void printAllCars(const std::vector<Car>& list) const;
    
    // Сортировка и статистика
    void sortByPrice();
    void sortByPriceDescending();
    void statistics();
    
    // Вспомогательные
    std::vector<Car> getAllCars() const;

private:
    void printHeader() const;
    void printCar(const Car& car, int index) const;
};

#endif