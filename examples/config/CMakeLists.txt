cmake_minimum_required(VERSION 3.16)
project(rut_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(rut REQUIRED)

add_executable(rut_test main.cpp)

target_link_libraries(rut_test
    PRIVATE
        rut::rut
)
