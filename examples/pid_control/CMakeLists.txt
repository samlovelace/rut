cmake_minimum_required(VERSION 3.16)
project(pid_controller LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(rut REQUIRED)

add_executable(pid_controller main.cpp)

target_link_libraries(pid_controller
    PRIVATE
        rut::rut
)
