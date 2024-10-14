cmake_minimum_required(VERSION 3.29)
project(FixedPoint)

set(CMAKE_CXX_STANDARD 20)

include(CTest)

add_executable(
        FixedPoint
        src/main.cpp
        src/FixedPoint.h
)

include(${CMAKE_CURRENT_BINARY_DIR}/../generated_tests.cmake)