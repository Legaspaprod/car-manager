#include <iostream>
#include "car_manager.h"

void findMenu(CarManager& manager) {
    while (true) {
        std::cout   << "\n--- Поиск ---\n"
                    << "1. По бренду\n"
                    << "2. По модели\n"
                    << "3. По году\n"
                    << "4. По цене\n"
                    << "5. Назад\n"
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
            case 5: return;
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
                    << "10. Выход\n"
                    << "Выбор: ";
        
        
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка, вводите числовое значение!";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                manager.addCar();
                break;

            case 2:
                manager.showCars();
                break;

            case 3:
                findMenu(manager);
                break;

            case 4:
                manager.removeCarByID();
                break;

            case 5:
                manager.saveToFile();
                break;

            case 6:
                manager.loadFromFile();
                break;

            case 7:
                sortMenu(manager);
                break;

            case 8:
                manager.statistics();
                break;

            case 9:
                manager.editCar();
                break;

            case 10:
                manager.saveToFile();
                std::cout << "Выход.\n";
                return 0;

            default:
                std::cout << "Выберите 1–10\n";
        }
    }
}