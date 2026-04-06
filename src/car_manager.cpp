#include "car_manager.h"

#include <sqlite3.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>

void CarManager::printAllCars(const std::vector<Car>& list) const {
    if (list.empty()) {
        std::cout << "Ничего не найдено!\n";
        return;
    }

    int index = 1;
    printHeader();

    for (const auto& car : list) {
        printCar(car, index++);
    }

    std::cout << "Всего " << list.size() << " автомобилей." << "\n";
}

void CarManager::printHeader() const {
    std::cout << "\nСписок машин:\n"
              << std::left << std::setw(6) << "№" << " | " << std::setw(4) << "ID" << " | "
              << std::setw(20) << "Марка" << " | " << std::setw(20) << "Модель" << " | "
              << std::setw(8) << "Год" << " | " << std::setw(15) << "Цена" << "\n"
              << std::string(72, '-') << "\n";
}

void CarManager::printCar(const Car& car, int index) const {
    std::cout << std::left << std::setw(4) << index << " | " << std::setw(4) << car.id << " | "
              << std::setw(15) << car.brand << " | " << std::setw(14) << car.model << " | "
              << std::setw(5) << car.year << " | " << std::setw(11) << car.price << " руб\n";
}

void CarManager::statistics() {
    auto max_price = std::max_element(cars.begin(), cars.end(),
                                      [](const Car& a, const Car& b) { return a.price < b.price; });
    if (max_price != cars.end()) {
        std::cout << "Самая дорогая машина: " << max_price->brand << " " << max_price->model << " "
                  << max_price->price << " руб \n";
    }
    auto min_price = std::min_element(cars.begin(), cars.end(),
                                      [](const Car& a, const Car& b) { return a.price < b.price; });
    if (min_price != cars.end()) {
        std::cout << "Самая дешевая машина: " << min_price->brand << " " << min_price->model << " "
                  << min_price->price << " руб \n";
    }
    if (!cars.empty()) {
        double average_price =
            std::accumulate(cars.begin(), cars.end(), 0.0,
                            [](double sum, const Car& car) { return sum + car.price; }) /
            cars.size();
        std::cout << "Средняя цена: " << average_price << "\n";
    }
}

void CarManager::findByModel() const {
    std::cout << "Введите модель: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::string model;

    std::getline(std::cin, model);

    std::vector<Car> result;
    for (const auto& car : cars) {
        if (car.model == model) {
            result.push_back(car);
        }
    }
    printAllCars(result);
}

void CarManager::findByYear() const {
    std::cout << "Введите диапазон годов от и до\n"
              << "От: ";
    int from_year{};
    if (!(std::cin >> from_year)) {
        std::cout << "Ошибка, вводите числовое значение!";
        return;
    }
    std::cout << "До: ";
    int to_year{};
    if (!(std::cin >> to_year)) {
        std::cout << "Ошибка, вводите числовое значение!";
        return;
    }

    std::vector<Car> result;
    for (const auto& car : cars) {
        if (car.year >= from_year && car.year <= to_year) {
            result.push_back(car);
        }
    }
    printAllCars(result);
}

void CarManager::findByPrice() const {
    std::cout << "Введите минимальную цену: ";
    int min{};
    std::cin >> min;
    std::cout << "Введите максимальную цену: ";
    int max{};
    std::cin >> max;

    std::vector<Car> result;
    for (const auto& car : cars) {
        if (car.price >= min && car.price <= max) {
            result.push_back(car);
        }
    }
    printAllCars(result);
}

void CarManager::sortByPriceDescending() {
    std::sort(cars.begin(), cars.end(),
              [](const Car& a, const Car& b) { return a.price > b.price; });

    std::cout << "Отсортировано.\n";
}

void CarManager::sortByPrice() {
    std::sort(cars.begin(), cars.end(),
              [](const Car& a, const Car& b) { return a.price < b.price; });

    std::cout << "Отсортировано.\n";
}

void CarManager::findCarByBrand() const {
    std::string brand;

    std::cout << "Введите бренд: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, brand);

    std::vector<Car> result;
    for (const auto& car : cars) {
        if (car.brand == brand) {
            result.push_back(car);
        }
    }
    printAllCars(result);
}

void CarManager::showCars() const {
    printAllCars(cars);
}

void CarManager::addCar(const Car& car) {
    Car newCar = car;
    newCar.id = nextid++;
    cars.push_back(newCar);
    saveToDB();
}

void CarManager::findCarById(int id) const {
    for (const auto& car : cars) {
        if (car.id == id) {
            printAllCars({car});
            return;
        }
    }
    std::cout << "Не найдено\n";
}

bool CarManager::removeCarById(int id) {
    auto it = std::find_if(cars.begin(), cars.end(), [id](const Car& car) { return car.id == id; });

    if (it != cars.end()) {
        cars.erase(it);
        return true;
    }
    return false;
}

std::vector<Car> CarManager::getAllCars() const {
    return cars;
}

void CarManager::editCar(int id, int field, const std::string& value) {
    for (auto& car : cars) {
        if (car.id == id) {
            switch (field) {
                case 1:
                    car.brand = value;
                    break;
                case 2:
                    car.model = value;
                    break;
            }
        }
    }
    saveToDB();
}

void CarManager::editCar(int id, int field, int value) {
    for (auto& car : cars) {
        if (car.id == id) {
            switch (field) {
                case 3:
                    car.year = value;
                    break;
                case 4:
                    car.price = value;
                    break;
            }
        }
    }
}

// Конструктор
CarManager::CarManager(Database& database) : db(database) {
    loadFromDB();
}

// Деструктор
CarManager::~CarManager() {
    // Пока пустой
}

// НОВЫЙ МЕТОД: загрузка из БД
void CarManager::loadFromDB() {
    cars.clear();

    const char* sql = "SELECT id, brand, model, year, price FROM cars ORDER BY id";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db.getHandle(), sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return;
    }

    int maxId = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Car car;
        car.id = sqlite3_column_int(stmt, 0);
        car.brand = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        car.model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        car.year = sqlite3_column_int(stmt, 3);
        car.price = sqlite3_column_int(stmt, 4);

        cars.push_back(car);

        if (car.id > maxId) maxId = car.id;
    }

    sqlite3_finalize(stmt);
    nextid = maxId + 1;

    std::cout << "Загружено " << cars.size() << " машин из БД" << std::endl;
}

// НОВЫЙ МЕТОД: сохранение в БД
void CarManager::saveToDB() {
    // Очищаем старые данные
    const char* deleteSql = "DELETE FROM cars";
    sqlite3_stmt* deleteStmt;
    sqlite3_prepare_v2(db.getHandle(), deleteSql, -1, &deleteStmt, nullptr);
    sqlite3_step(deleteStmt);
    sqlite3_finalize(deleteStmt);

    // Вставляем все машины заново
    const char* insertSql =
        "INSERT INTO cars (id, brand, model, year, price) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt* insertStmt;
    sqlite3_prepare_v2(db.getHandle(), insertSql, -1, &insertStmt, nullptr);

    for (const auto& car : cars) {
        sqlite3_bind_int(insertStmt, 1, car.id);
        sqlite3_bind_text(insertStmt, 2, car.brand.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(insertStmt, 3, car.model.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(insertStmt, 4, car.year);
        sqlite3_bind_int(insertStmt, 5, car.price);

        sqlite3_step(insertStmt);
        sqlite3_reset(insertStmt);
    }

    sqlite3_finalize(insertStmt);
    std::cout << "Сохранено " << cars.size() << " машин в БД" << std::endl;
}