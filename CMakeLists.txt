cmake_minimum_required(VERSION 3.7)
project(Final)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES projet/main.c projet/csv.c projet/csv.h projet/account.h projet/account.c projet/customer.h projet/customer.c)
add_executable(Final ${SOURCE_FILES})