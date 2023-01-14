cmake_minimum_required(VERSION 3.24)
project(mbed)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

add_definitions(-DMBED_VERSION="1.0.0")

include_directories(lib/termcolor/include)

add_executable(${PROJECT_NAME} main.cpp)
