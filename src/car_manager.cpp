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

void CarManager::findByPrice() {
    std::cout << "Введите минимальную цену: \n";
    int min{};
    std::cin >> min;
    std::cout << "Введите максимальную цену: \n";
    int max{};
    std::cin >> max;
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

    std::ofstream output("data/carbase.txt");
    if (!output) {
        std::cout << "Ошибка открытия файла\n";
        return;
    }

    for (const auto& car : cars) {
        output  << car.id << " "
                << car.brand << " "
                << car.model << " "
                << car.year << " "
                << car.price << "\n";
    }
}

void CarManager::loadFromFile() {
    cars.clear();
    
    std::ifstream input("data/carbase.txt");

    if (!input) {
        std::cout << "Файл базы не найден\n";
        return;
    }

    Car car;

    while (input >> car.id >>car.brand >> car.model >> car.year >> car.price) {
        cars.push_back(car);
    }
    nextid = car.id + 1;
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

        std::cout << "Введите год: ";
        int year;
        while (true) {
            if (!(std::cin >> year)) {
                std::cout << "Ошибка, вводите только цифры!\n";

                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Введите цену: ";
            } else {
                break;
            }
        }
        newCar.year = year;

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
        
        newCar.id = nextid++;
        cars.push_back(newCar);

        std::cout << "\nМашина добавлена!\n";

}

void CarManager::showCars() const {

        if (cars.empty()) {
            std::cout << "Список машин пуст! \n";
            return;
        }

        std::cout   << "\nСписок машин:\n"
                    << "№  |ID |    Марка    |  Модель  | Год | Цена \n"
                    << "---------------------------------------------\n";

        int index = 1;

        for (const auto& car : cars) {
            std::cout   << index++ << ". "
                        << car.id << " "
                        << car.brand << " "
                        << car.model << " "
                        << car.year << " Цена: "
                        << car.price << " руб.\n";
}

        std::cout << "Всего машин: " << cars.size() << "\n\n";    
}
