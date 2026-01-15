cmake_minimum_required(VERSION 3.16)
project(rut_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rut_test main.cpp)

# Tell CMake where rut headers are
target_include_directories(rut_test
    PRIVATE
        /home/sam/dev/cpp/rut/include
)

# Tell CMake where librut.a is
target_link_directories(rut_test
    PRIVATE
        /home/sam/dev/cpp/rut/build
)

# Link rut and its deps (static lib → deps are YOUR problem)
target_link_libraries(rut_test
    PRIVATE
        rut
)
