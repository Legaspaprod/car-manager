#include <iostream>

#include "car_manager.h"
#include "utils.h"

void findMenu(CarManager& manager) {
    while (true) {
        std::cout << "\n--- Поиск ---\n"
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
            case 1:
                manager.findCarByBrand();
                break;
            case 2:
                manager.findByModel();
                break;
            case 3:
                manager.findByYear();
                break;
            case 4:
                manager.findByPrice();
                break;
            case 5: {
                std::cin.ignore();
                std::cout << "Введите ID: ";
                int id;
                std::cin >> id;
                manager.findCarById(id);
                break;
            }
            case 6:
                return;
            default:
                std::cout << "Ошибка\n";
        }
    }
}

void sortMenu(CarManager& manager) {
    while (true) {
        std::cout << "\n--- Сортировка ---\n"
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
    Database db("cars.db");  // создаём базу данных
    if (!db.isOpen()) {
        std::cerr << "Не удалось открыть БД" << std::endl;
        return 1;
    }

    CarManager manager(db);

    int choice;

    while (true) {
        std::cout << "==========Car Manager v1.0==========\n"
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
                } else {
                    std::cout << "Не найдено\n";
                }
                break;
            }
            case 5: {
                break;
            }
            case 6: {
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

                std::cin.ignore();

                while (true) {
                    int choice;
                    std::cout << "\nРедактирование машины ID: " << id << "\n";
                    std::cout << "1. Марка\n2. Модель\n3. Год\n4. Цена\n5. Назад\n";
                    choice = safeInputInt("Выбор: ");

                    if (choice == 1) {
                        std::string newBrand = safeInputString("Новая марка: ");
                        manager.editCar(id, 1, newBrand);
                    } else if (choice == 2) {
                        std::string newModel = safeInputString("Новая модель: ");
                        manager.editCar(id, 2, newModel);
                    } else if (choice == 3) {
                        int newYear = safeInputInt("Новый год: ");
                        manager.editCar(id, 3, newYear);
                    } else if (choice == 4) {
                        int newPrice = safeInputInt("Новая цена: ");
                        manager.editCar(id, 4, newPrice);
                    } else if (choice == 5) {
                        break;
                    }
                }
                break;
            }

            case 10: {
                manager.saveToDB();
                std::cout << "Выход.\n";
                return 0;
            }
            default: {
                std::cout << "Выберите 1–10\n";
            }
        }
    }
}