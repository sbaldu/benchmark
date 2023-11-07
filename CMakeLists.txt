cmake_minimum_required(VERSION 3.16.0)

project(benchmark VERSION 1.0.0 LANGUAGES CXX)

# set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

install(FILES ${PROJECT_SOURCE_DIR}/Bench.hpp DESTINATION /usr/include/)
