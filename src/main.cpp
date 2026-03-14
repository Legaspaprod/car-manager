#include <iostream>
#include "car_manager.h"

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
                    << "8. Выход\n"
                    << "Выбор: ";
        
        std::cin >> choice;

        if (choice == 1) {
            manager.addCar();
        } else if (choice == 2) {
            manager.showCars();
        } else if (choice == 3) {
            while (true) {
                std::cout   << "1. Найти по бренду\n"
                            << "2. Найти по цене\n"
                            << "3. Назад\n";
                
                std::cin >> choice;
                
                if (choice == 1) {
                    manager.findCarByBrand();
                } else if (choice == 2) {
                    
                } else if (choice == 3) {
                    break;
                }
            }
        } else if (choice == 4) {
            manager.removeCarByBrand();
        } else if (choice == 5) {
            manager.saveToFile();
        } else if (choice == 6) {
            manager.loadFromFile();
        } else if (choice == 7) {
            while (true) {
                std::cout   << "1. Сортировать по возрастанию\n"
                            << "2. Сортировать по убыванию\n"
                            << "3. Назад\n"
                            << "Выбор: ";

                std::cin >> choice;

                if (choice == 1) {
                    manager.sortByPrice();
                    break;
                } else if (choice == 2) {
                    manager.sortByPriceDescending();
                    break;
                } else if (choice == 3) {
                    break;
                }
            }
        } else if (choice == 8) {
            manager.saveToFile();
            std::cout << "Выход из программы. \n";
            break;
        } else {
            std::cout << "Выберете число от 1 до 8.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    return 0;
}