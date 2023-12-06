cmake_minimum_required(VERSION 3.1...3.27)

project(
  AdventOfCode
  VERSION 23.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Common "common/TaskSolver.h" "common/TaskSolver.cpp" "common/StringManipulation.h" "common/StringManipulation.cpp" common/BigInt.hpp)

include_directories(common)

add_executable(03 03/main.cpp)

add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(04)
add_subdirectory(05)
add_subdirectory(06)
