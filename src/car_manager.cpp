#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <numeric>
#include "car_manager.h"

void CarManager::printGUI() const {
    std::cout   << "\nСписок машин:\n"
                << std::left
                << std::setw(6) << "№" <<  " | "
                << std::setw(4) << "ID" << " | "
                << std::setw(20) << "Марка" << " | "
                << std::setw(20) << "Модель" << " | "
                << std::setw(8) << "Год" << " | "
                << std::setw(15) << "Цена" << "\n"
                << std::string(72, '-') << "\n";
}

void CarManager::printCar(const Car& car, int index) const {
    std::cout   << std::left
                << std::setw(4) << index++ << " | "
                << std::setw(4) << car.id << " | "
                << std::setw(15) << car.brand << " | "
                << std::setw(14) << car.model << " | "
                << std::setw(5) << car.year << " | "
                << std::setw(11) << car.price << " руб\n";
}

void CarManager::editCar() {
    std::cout << "Введите ID автомобиля: "; 
    int id{}; 
    if (!(std::cin >> id)) { 
        std::cout << "Ошибка. Вводите числовое значение.\n"; 
        std::cin.clear(); 
        std::cin.ignore(10000, '\n'); 
        return; 
    }

    bool found = false;
    int index = 1;

    for (auto& car : cars) {
        if (car.id == id) {
            while (true) {
                std::cout << "\nРедактирование машины ID: " << car.id << "\n";
                std::cout << "1. Марка\n2. Модель\n3. Год\n4. Цена\n5. Назад\n";

                int choice;
                if (!(std::cin >> choice)) {
                    std::cout << "Ошибка ввода\n";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    continue;
                }
                if (choice == 1) {
                    std::cout << "Новая марка: ";
                    std::cin >> car.brand;
                    printGUI();
                    printCar(car, index++);
                } else if (choice == 2) {
                    std::cout << "Новая модель: ";
                    std::cin >> car.model;
                    printGUI();
                    printCar(car, index++);
                } else if (choice == 3) {
                    std::cout << "Новый год: ";
                    int year;
                    if (!(std::cin >> year)) {
                        std::cout << "Ошибка\n";
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        continue;
                    }
                    car.year = year;
                    printGUI();
                    printCar(car, index++);
                } else if (choice == 4) {
                    std::cout << "Новая цена: ";
                    int price;
                    if (!(std::cin >> price)) {
                        std::cout << "Ошибка\n";
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        continue;
                    }
                    car.price = price;
                    printGUI();
                    printCar(car, index++);
                } else if (choice == 5) {
                    break;
                }
            }
            found = true;
        }
    }

    if (!found){
        std::cout << "Не найдено машин!\n";
    }
}

void CarManager::statistics() {
    auto max_price = std::max_element(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
        return a.price < b.price;
    });
    if ( max_price != cars.end()) {
        std::cout   << "Самая дорогая машина: " 
                    << max_price->brand << " " 
                    << max_price->model << " " 
                    << max_price->price << " руб \n";
    }
    auto min_price = std::min_element(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
        return a.price < b.price;
    });
    if ( min_price != cars.end()) {
        std::cout   << "Самая дешевая машина: "
                    << min_price->brand << " "
                    << min_price->model << " "
                    << min_price->price << " руб \n";
    }
    if (!cars.empty()) {
        double average_price = std::accumulate(cars.begin(), cars.end(), 0.0, [](double sum, const Car& car) {
        return sum + car.price;
        }) / cars.size();
        std::cout << "Средняя цена: " << average_price << "\n";
    }
}

void CarManager::findByModel() const {
    std::cout << "Введите модель: ";
    std::string model;
    std::cin >> model;

    bool found = false;
    int index = 1;

    printGUI();

    for (const auto& car : cars) {
        if (car.model == model) {
            printCar(car, index++);
            found = true;
        }
    }

    if (!found){
        std::cout << "Не найдено машин!\n";
    }
}

void CarManager::findByYear() const {
    std::cout   << "Введите диапазон годов от и до\n"
                << "От: ";
    int from_year{};
    if (!(std::cin >> from_year)) {
        std::cout << "Ошибка, вводите числовое значение!";
        return;
    }
    std::cout << "До: ";
    int to_year{};
    if(!(std::cin >> to_year)) {
        std::cout << "Ошибка, вводите числовое значение!";
        return;
    }

    bool found = false;
    int index = 1;

    printGUI();

    for (const auto& car : cars) {
        if (car.year >= from_year && car.year <= to_year) {
            printCar(car, index++);
            found = true;
        }
    }

    if (!found){
        std::cout << "Не найдено машин!\n";
    }
}

void CarManager::findByPrice() const {
    std::cout << "Введите минимальную цену: ";
    int min{};
    std::cin >> min;
    std::cout << "Введите максимальную цену: ";
    int max{};
    std::cin >> max;

    bool found = false;
    int index = 1;

    printGUI();


    for (const auto& car : cars) {
        if (car.price >= min && car.price <= max) {
            printCar(car, index++);
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
        saveToFile();
    } else {
        std::cout << "Машина не найдена!\n";
    }
}

void CarManager::findCarByBrand() const {
    std::string brand;

    std::cout << "Введите бренд: \n";
    std::cin >> brand;

    bool found = false;
    int index = 1;

    printGUI();

    for (const auto& car : cars) {
        if (car.brand == brand) {
            printCar(car, index++);
            found = true;
        }
    }

    if (!found){
        std::cout << "Не найдено машин!\n";
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
        saveToFile();

}

void CarManager::showCars() const {

    if (cars.empty()) {
        std::cout << "Список машин пуст! \n";
        return;
    }

    int index = 1;
    printGUI();
    for (const auto& car : cars) {
        printCar(car, index++);
    }


    std::cout << "Всего машин: " << cars.size() << "\n\n";    
}
