#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <numeric>
#include "car_manager.h"

void CarManager::statistics() {
    auto it = std::max_element(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
        return a.price < b.price;
    });
    if ( it != cars.end()) {
        std::cout   << "Самая дорогая машина: " 
                    << it->brand << " " 
                    << it->model << " " 
                    << it->price << " руб \n";
    }
    auto it2 = std::min_element(cars.begin(), cars.end(), [](const Car& a, Car& b) {
        return a.price < b.price;
    });
    if ( it2 != cars.end()) {
        std::cout   << "Самая дешевая машина: "
                    << it2->brand << " "
                    << it2->model << " "
                    << it2->price << " руб \n";
    }
    if (!cars.empty()) {
        int it3 = std::accumulate(cars.begin(), cars.end(), 0.0, [](double sum, const Car& car) {
        return sum + car.price;
        }) / cars.size();
        std::cout << "Средняя цена: " << it3 << "\n";
    }
}

void CarManager::findByPrice() {
    std::cout << "Введите минимальную цену: ";
    int min{};
    std::cin >> min;
    std::cout << "Введите максимальную цену: ";
    int max{};
    std::cin >> max;

    bool found = false;
    int index = 1;

    std::cout   << "\nСписок машин:\n"
                    << std::left
                    << std::setw(6) << "№" <<  " | "
                    << std::setw(4) << "ID" << " | "
                    << std::setw(20) << "Марка" << " | "
                    << std::setw(20) << "Модель" << " | "
                    << std::setw(8) << "Год" << " | "
                    << std::setw(15) << "Цена" << "\n"
                    << std::string(72, '-') << "\n";


    for (const auto& Car : cars) {
        if (Car.price >= min && Car.price <= max) {
            std::cout   << std::left
                        << std::setw(4) << index++ << " | "
                        << std::setw(4) << Car.id << " | "
                        << std::setw(15) << Car.brand << " | "
                        << std::setw(14) << Car.model << " | "
                        << std::setw(5) << Car.year << " | "
                        << std::setw(11) << Car.price << " руб\n";
        found = true;
        }
    }

    if (!found){
        std::cout << "Не найдено машин!\n";
    }

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

    int maxid = 0;

    while (input >> car.id >>car.brand >> car.model >> car.year >> car.price) {
        cars.push_back(car);
        if (car.id > maxid) {
            maxid = car.id;
        }
    }
    nextid = maxid + 1;
}

void CarManager::removeCarByID() {
    int id;

    std::cout << "Введите ID: ";
    std::cin >> id;

    auto it = std::find_if(cars.begin(), cars.end(),
        [id](const Car& car) {
            return car.id == id;
        });

    if (it != cars.end()) {
        cars.erase(it);
        std::cout << "Машина " << id << " удалена!\n";
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
    int index = 1;
    if (it != cars.end()) {
        std::cout   << "Найдена машина: \n"
                    << std::left
                    << std::setw(6) << "№" <<  " | "
                    << std::setw(4) << "ID" << " | "
                    << std::setw(20) << "Марка" << " | "
                    << std::setw(20) << "Модель" << " | "
                    << std::setw(8) << "Год" << " | "
                    << std::setw(15) << "Цена" << "\n"
                    << std::string(72, '-') << "\n"
                    << std::setw(4) << index++ << " | "
                    << std::setw(4) << it->id << " | "
                    << std::setw(15) << it->brand << " | "
                    << std::setw(14) << it->model << " | "
                    << std::setw(5) << it->year << " | "
                    << std::setw(11) << it->price << " руб\n";
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
                    << std::left
                    << std::setw(6) << "№" <<  " | "
                    << std::setw(4) << "ID" << " | "
                    << std::setw(20) << "Марка" << " | "
                    << std::setw(20) << "Модель" << " | "
                    << std::setw(8) << "Год" << " | "
                    << std::setw(15) << "Цена" << "\n"
                    << std::string(72, '-') << "\n";

        int index = 1;

        for (const auto& car : cars) {
            std::cout   << std::left
                        << std::setw(4) << index++ << " | "
                        << std::setw(4) << car.id << " | "
                        << std::setw(15) << car.brand << " | "
                        << std::setw(14) << car.model << " | "
                        << std::setw(5) << car.year << " | "
                        << std::setw(11) << car.price << " руб\n";
}

        std::cout << "Всего машин: " << cars.size() << "\n\n";    
}
