cmake_minimum_required(VERSION 3.16)
project(rut VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${PROJECT_NAME}
    src/config/config.cpp
    src/config/yaml_loader.cpp
    src/config/json_loader.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include> 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# find_package for deps here 

# ---- Warnings (optional but recommended) ----
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
