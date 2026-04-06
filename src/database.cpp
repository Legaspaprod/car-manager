#include "database.h"

#include <iostream>

Database::Database(const std::string& path) : db(nullptr), dbPath(path) {
    open();
    createTables();
}

Database::~Database() {
    close();
}

bool Database::open() {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    std::cout << "База данных открыта: " << dbPath << std::endl;
    return true;
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        std::cout << "База данных закрыта" << std::endl;
    }
}

bool Database::isOpen() const {
    return db != nullptr;
}

bool Database::executeSQL(const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL ошибка: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool Database::createTables() {
    const std::string sql = R"(
        CREATE TABLE IF NOT EXISTS cars (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            brand TEXT NOT NULL,
            model TEXT NOT NULL,
            year INTEGER NOT NULL,
            price INTEGER NOT NULL
        );
    )";

    return executeSQL(sql);
}