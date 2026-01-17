cmake_minimum_required(VERSION 3.16)
project(rut VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# find_package for deps here 
find_package(yaml-cpp REQUIRED)
find_package(Eigen REQUIRED)


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

target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp Eigen3::Eigen)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# cmake install stuff
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# install the library 
install(
    TARGETS ${PROJECT_NAME}
    EXPORT rutTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# install public headers 
install(
    DIRECTORY include/${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
 
# export targets 
install(
    EXPORT rutTargets
    FILE rutTargets.cmake
    NAMESPACE rut::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rut
)

# Generate package config
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/rutConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/rutConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rut
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/rutConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# install package config 
install(
    FILES 
        ${CMAKE_CURRENT_BINARY_DIR}/rutConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/rutConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rut
)