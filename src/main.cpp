#include <iostream>
#include "car_manager.h"
#include "utils.h"


void findMenu(CarManager& manager) {
    while (true) {
        std::cout   << "\n--- Поиск ---\n"
                    << "1. По бренду\n"
                    << "2. По модели\n"
                    << "3. По году\n"
                    << "4. По цене\n"
                    << "5. По ID\n"
                    << "6. Назад\n"
                    << "Выбор: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: manager.findCarByBrand(); break;
            case 2: manager.findByModel(); break;
            case 3: manager.findByYear(); break;
            case 4: manager.findByPrice(); break;
            case 5: {
                std::cin.ignore();
                std::cout << "Введите ID: ";
                int id;
                std::cin >> id;
                manager.findCarById(id);
                break;
            }
            case 6: return;
            default: std::cout << "Ошибка\n";
        }
    }
}

void sortMenu(CarManager& manager) {
    while (true) {
        std::cout   << "\n--- Сортировка ---\n"
                    << "1. По возрастанию\n"
                    << "2. По убыванию\n"
                    << "3. Назад\n"
                    << "Выбор: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                manager.sortByPrice();
                return;
            case 2:
                manager.sortByPriceDescending();
                return;
            case 3:
                return;
            default:
                std::cout << "Ошибка\n";
        }
    }
}

int main() {

    CarManager manager;

    manager.loadFromFile();

    int choice;

    while (true) {
        std::cout   << "==========Car Manager v1.0==========\n"
                    << "1. Добавить машину\n"
                    << "2. Показать машины\n"
                    << "3. Найти машину\n"
                    << "4. Удалить машину\n"
                    << "5. Сохранить\n"
                    << "6. Загрузить\n"
                    << "7. Сортировать по цене\n"
                    << "8. Статистика\n"
                    << "9. Изменить машину\n"
                    << "10. Выход\n";
        
        
        choice = safeInputInt("Выбор: ");

        switch (choice) {
            case 1: {
                Car car;

                std::cin.ignore();
                std::cout << "Введите бренд: ";
                std::getline(std::cin, car.brand);

                std::cout << "Введите модель: ";
                std::getline(std::cin, car.model);

                std::cout << "Введите год: ";
                std::cin >> car.year;

                std::cout << "Введите цену: ";
                std::cin >> car.price;

                manager.addCar(car);
                manager.saveToFile();

                std::cout << "Машина добавлена!\n";
                break;
            }

            case 2: {
                manager.showCars();
                break;
            }
            case 3: {
                findMenu(manager);
                break;
            }
            case 4: {
                int id;
                std::cout << "Введите ID: ";
                std::cin >> id;

                if (manager.removeCarById(id)) {
                    std::cout << "Удалено\n";
                    manager.saveToFile();
                } else {
                    std::cout << "Не найдено\n";
                }
                break;
            }
            case 5: {
                manager.saveToFile();
                break;
            }
            case 6: {
                manager.loadFromFile();
                break;
            }
            case 7: {
                sortMenu(manager);
                break;
            }
            case 8: {
                manager.statistics();
                break;
            }
            case 9: {
                int id;
                std::cout << "Введите ID: ";
                std::cin >> id;

                Car* car = manager.findCarById(id);

                if (!car) {
                   std::cout << "Не найдено\n";
                    break;
                }

                std::cin.ignore();

                std::cout << "Новая марка: ";
                std::getline(std::cin, car->brand);

                std::cout << "Новая модель: ";
                std::getline(std::cin, car->model);

                std::cout << "Новый год: ";
                std::cin >> car->year;

                std::cout << "Новая цена: ";
                std::cin >> car->price;

                manager.saveToFile();
                break;
            }
            case 10: {
                manager.saveToFile();
                std::cout << "Выход.\n";
                return 0;
            }
            default: {
                std::cout << "Выберите 1–10\n";
            }
        }
    }
}