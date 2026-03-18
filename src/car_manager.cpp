#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <numeric>
#include "car_manager.h"

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

    
    for (auto& car : cars) {
        if (car.id == id) {
            std::cout   << "\nСписок машин:\n"
                    << std::left
                    << std::setw(6) << "№" <<  " | "
                    << std::setw(4) << "ID" << " | "
                    << std::setw(20) << "Марка" << " | "
                    << std::setw(20) << "Модель" << " | "
                    << std::setw(8) << "Год" << " | "
                    << std::setw(15) << "Цена" << "\n"
                    << std::string(72, '-') << "\n";
            std::cout   << std::left
                        << std::setw(4) << car.id << " | "
                        << std::setw(15) << car.brand << " | "
                        << std::setw(14) << car.model << " | "
                        << std::setw(5) << car.year << " | "
                        << std::setw(11) << car.price << " руб\n";
        found = true;

        while (true) {
                std::cout   << "1. Изменить марку\n"
                            << "2. Изменить модель\n"
                            << "3. Изменить год\n"
                            << "4. Изменить цену\n"
                            << "5. Назад\n"
                            << "Выбор: ";

                int choice{};
                std::cin >> choice;


                if (choice == 1) {
                    std::cout << "Введите новое значение: ";
                    auto ex_edit = car.brand;
                    std::cin >> car.brand;
                    for (auto& car : cars) {
                        if (car.id == id) {
                            std::cout   << "\nСписок машин:\n"
                                        << std::left
                                        << std::setw(6) << "№" <<  " | "
                                        << std::setw(4) << "ID" << " | "
                                        << std::setw(20) << "Марка" << " | "
                                        << std::setw(20) << "Модель" << " | "
                                        << std::setw(8) << "Год" << " | "
                                        << std::setw(15) << "Цена" << "\n"
                                        << std::string(72, '-') << "\n";
                            std::cout   << std::left
                                        << std::setw(4) << car.id << " | "
                                        << std::setw(15) << car.brand << " | "
                                        << std::setw(14) << car.model << " | "
                                        << std::setw(5) << car.year << " | "
                                        << std::setw(11) << car.price << " руб\n";
                        }
                    }
                    while (true) {
                        std::cout   << "1. Сохранить\n"
                                    << "2. Отменить изменения\n"
                                    << "Выбор: ";
                        std::cin >> choice;
                        if (choice == 1) {
                            break;
                        } else if (choice == 2) {
                            car.brand = ex_edit;
                            break;
                        } else {
                            std::cout << "Выберете число от 1 до 2.\n";
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                        }
                    }
                } else if (choice == 2) {
                    std::cout << "Введите новое значение: ";
                    auto ex_edit = car.model;
                    std::cin >> car.model;
                    for (auto& car : cars) {
                        if (car.id == id) {
                            std::cout   << "\nСписок машин:\n"
                                        << std::left
                                        << std::setw(6) << "№" <<  " | "
                                        << std::setw(4) << "ID" << " | "
                                        << std::setw(20) << "Марка" << " | "
                                        << std::setw(20) << "Модель" << " | "
                                        << std::setw(8) << "Год" << " | "
                                        << std::setw(15) << "Цена" << "\n"
                                        << std::string(72, '-') << "\n";
                            std::cout   << std::left
                                        << std::setw(4) << car.id << " | "
                                        << std::setw(15) << car.brand << " | "
                                        << std::setw(14) << car.model << " | "
                                        << std::setw(5) << car.year << " | "
                                        << std::setw(11) << car.price << " руб\n";
                        }
                    }
                    while (true) {
                        std::cout   << "1. Сохранить\n"
                                    << "2. Отменить изменения\n"
                                    << "Выбор: ";
                        std::cin >> choice;
                        if (choice == 1) {
                            break;
                        } else if (choice == 2) {
                            car.model = ex_edit;
                            break;
                        } else {
                            std::cout << "Выберете число от 1 до 2.\n";
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                        }
                    }
                } else if (choice == 3) {
                    std::cout << "Введите новое значение: ";
                    int ex_edit = car.year;
                    int year{};
                    if (!(std::cin >> year)) {
                        std::cout << "Ошибка, вводите числовое значение!\n";
                        break;
                    }
                    car.year = year;
                    for (auto& car : cars) {
                        if (car.id == id) {
                            std::cout   << "\nСписок машин:\n"
                                        << std::left
                                        << std::setw(6) << "№" <<  " | "
                                        << std::setw(4) << "ID" << " | "
                                        << std::setw(20) << "Марка" << " | "
                                        << std::setw(20) << "Модель" << " | "
                                        << std::setw(8) << "Год" << " | "
                                        << std::setw(15) << "Цена" << "\n"
                                        << std::string(72, '-') << "\n";
                            std::cout   << std::left
                                        << std::setw(4) << car.id << " | "
                                        << std::setw(15) << car.brand << " | "
                                        << std::setw(14) << car.model << " | "
                                        << std::setw(5) << car.year << " | "
                                        << std::setw(11) << car.price << " руб\n";
                        }
                    }
                    while (true) {
                        std::cout   << "1. Сохранить\n"
                                    << "2. Отменить изменения\n"
                                    << "Выбор: ";
                        std::cin >> choice;
                        if (choice == 1) {
                            break;
                        } else if (choice == 2) {
                            car.year = ex_edit;
                            break;
                        } else {
                            std::cout << "Выберете число от 1 до 2.\n";
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                        }
                    }                  
                } else if (choice == 4) {
                    std::cout << "Введите новое значение: ";
                    int ex_edit = car.price;
                    int price{};
                    if (!(std::cin >> price)) {
                        std::cout << "Ошибка, вводите числовое значение!\n";
                        break;
                    }
                    car.price = price;
                    for (auto& car : cars) {
                        if (car.id == id) {
                            std::cout   << "\nСписок машин:\n"
                                        << std::left
                                        << std::setw(6) << "№" <<  " | "
                                        << std::setw(4) << "ID" << " | "
                                        << std::setw(20) << "Марка" << " | "
                                        << std::setw(20) << "Модель" << " | "
                                        << std::setw(8) << "Год" << " | "
                                        << std::setw(15) << "Цена" << "\n"
                                        << std::string(72, '-') << "\n";
                            std::cout   << std::left
                                        << std::setw(4) << car.id << " | "
                                        << std::setw(15) << car.brand << " | "
                                        << std::setw(14) << car.model << " | "
                                        << std::setw(5) << car.year << " | "
                                        << std::setw(11) << car.price << " руб\n";
                        }
                    }
                    while (true) {
                        std::cout   << "1. Сохранить\n"
                                    << "2. Отменить изменения\n"
                                    << "Выбор: ";
                        std::cin >> choice;
                        if (choice == 1) {
                            break;
                        } else if (choice == 2) {
                            car.price = ex_edit;
                            break;
                        } else {
                            std::cout << "Выберете число от 1 до 2.\n";
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                        }
                    }
                } else if (choice == 5) {
                    break;
                } else {
                    std::cout << "Выберете число от 1 до 5.\n";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
            }
        }
    }

    if (!found) {
        std::cout << "Ошибка, автомобиль не найден!\n";
        return;
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
    auto min_price = std::min_element(cars.begin(), cars.end(), [](const Car& a, Car& b) {
        return a.price < b.price;
    });
    if ( min_price != cars.end()) {
        std::cout   << "Самая дешевая машина: "
                    << min_price->brand << " "
                    << min_price->model << " "
                    << min_price->price << " руб \n";
    }
    if (!cars.empty()) {
        int average_price = std::accumulate(cars.begin(), cars.end(), 0.0, [](double sum, const Car& car) {
        return sum + car.price;
        }) / cars.size();
        std::cout << "Средняя цена: " << average_price << "\n";
    }
}

void CarManager::findByModel() {
    std::cout << "Введите модель: ";
    std::string model;
    std::cin >> model;

    auto it = std::find_if(cars.begin(), cars.end(), [model](const Car& car) {
        return car.model == model;
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
