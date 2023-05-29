cmake_minimum_required(VERSION 3.10)

project(nndescent
    VERSION 0.0.0
    LANGUAGES CXX
    DESCRIPTION "A C++ implementation of the nearest neighbour descent algorithm")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS
    "-Wall -g -pg -Ofast -march=native -flto -fno-math-errno -fopenmp -pg")

# Collect source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Library
add_library(nndescent STATIC ${SRC_FILES})

# Source code
target_include_directories(nndescent PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Tests
add_executable(test_distances tests/test_distances.cpp)
target_link_libraries(test_distances PRIVATE nndescent)

add_executable(simple tests/simple.cpp)
target_link_libraries(simple PRIVATE nndescent)

add_executable(faces tests/faces.cpp)
target_link_libraries(faces PRIVATE nndescent)

add_executable(fmnist tests/fmnist.cpp)
target_link_libraries(fmnist PRIVATE nndescent)