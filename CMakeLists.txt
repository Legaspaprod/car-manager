cmake_minimum_required(VERSION 3.10)

project(CarManager)

set(CMAKE_CXX_STANDARD 20)

find_package(SQLite3 REQUIRED)
include_directories(include)

add_executable(CarManager
    src/main.cpp
    src/car_manager.cpp
    src/utils.cpp
    src/database.cpp
)

target_link_libraries(CarManager PRIVATE SQLite::SQLite3)
