#pragma once
#include <sqlite3.h>

#include <string>

class Database {
   private:
    sqlite3* db;
    std::string dbPath;

   public:
    Database(const std::string& path = "cars.db");
    ~Database();

    bool open();
    void close();
    bool isOpen() const;

    sqlite3* getHandle() const { return db; }

    bool createTables();

   private:
    bool executeSQL(const std::string& sql);
};