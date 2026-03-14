#include <iostream>
#include <algorithm>
#include <fstream>
#include "car_manager.h"

std::vector<Car>::iterator CarManager::findCarIterator(const std::string& brand)
{
    return std::find_if(
        cars.begin(),
        cars.end(),
        [brand](const Car& car) {
            return car.brand == brand;
        }
    );
}

void CarManager::sortByPriceDescending() {
    std::sort(cars.begin(), cars.end(), [](const Car& a, const Car&b) {
            return a.price > b.price;
        } 
    );
    
    std::cout << "Отсортировано.\n";    
}

void CarManager::sortByPrice() {
    std::sort(cars.begin(), cars.end(), [](const Car& a, const Car&b) {
            return a.price < b.price;
        } 
    ); 
    
    std::cout << "Отсортировано.\n";
}

void CarManager::saveToFile() {

    std::ofstream output("carbase.txt");
    if (!output) {
        std::cout << "Ошибка открытия файла\n";
        return;
    }

    for (const auto& car : cars) {
        output << car.brand << " "
               << car.model << " "
               << car.price << "\n";
    }
}

void CarManager::loadFromFile() {
    cars.clear();
    
    std::ifstream input("carbase.txt");

    if (!input) {
        std::cout << "Файл базы не найден\n";
        return;
    }

    Car car;

    while (input >> car.brand >> car.model >> car.price) {
        cars.push_back(car);
    }
}

void CarManager::removeCarByBrand() {
    std::string brand;

    std::cout << "Введите бренд: \n";
    std::cin >> brand;

    auto it = findCarIterator(brand);

    if (it != cars.end()) {
        cars.erase(it);
        std::cout << "Машина " << brand << " удалена!\n";
    } else {
        std::cout << "Машина не найдена!\n";
    }
}

void CarManager::findCarByBrand() const {
    std::string brand;

    std::cout << "Введите бренд: \n";
    std::cin >> brand;

    auto it = std::find_if(cars.begin(), cars.end(), [brand](const Car& car) {
        return car.brand == brand;
        }
    );

    if (it != cars.end()) {
        std::cout   << "Найдена машина: "
                    << it->brand << " "
                    << it->model << " "
                    << it->price << "$\n";
    } else {
        std::cout << "Машина не найдена!\n";
    }
}

void CarManager::addCar() {
        Car newCar;

        std::cout << "Введите бренд: ";
        std::cin >> newCar.brand;

        std::cout << "Введите модель: ";
        std::cin >> newCar.model;

        std::cout << "Введите цену: ";
        int prices{};
        while (true) {
            if (!(std::cin >> prices)) {
                std::cout << "Ошибка, вводите только цифры!\n";

                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Введите цену: ";
            } else {
                break;
            }
        }
        newCar.price = prices;

        cars.push_back(newCar);

        std::cout << "\nМашина добавлена!\n";

}

void CarManager::showCars() const {

        if (cars.empty()) {
            std::cout << "Список машин пуст! \n";
            return;
        }

        std::cout << "\nСписок машин:\n";

        int index = 1;

        for (const auto& car : cars) {
            std::cout   << index++ << ". "
                        << car.brand << " "
                        << car.model << " Цена: "
                        << car.price << "$\n";
}

        std::cout << "Всего машин: " << cars.size() << "\n\n";    
}
