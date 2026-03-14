# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(CarManager VERSION 1.0.0)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опции компиляции для Linux
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Отдельные флаги для Debug и Release сборки
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")

# Указываем где искать заголовочные файлы
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Список исходных файлов
set(SOURCES
    main.cpp
    car_manager.cpp
)

# Заголовочные файлы (для отслеживания изменений в IDE)
set(HEADERS
    car.h
    car_manager.h
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Если нужна поддержка многопоточности (часто используется в Linux)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

# Опция для сборки с санитайзерами (полезно для отладки в Linux)
option(ENABLE_SANITIZERS "Включить санитайзеры для отладки" OFF)
if(ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address -fsanitize=undefined)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address -fsanitize=undefined)
endif()

# Вывод информации о сборке
message(STATUS "Configuring ${PROJECT_NAME} for Linux")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")