cmake_minimum_required(VERSION 3.1...3.27)

project(
  AdventOfCode
  VERSION 23.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_library(MyLibExample simple_lib.cpp simple_lib.hpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/02/input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/01/sample_input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/01/sample_input2.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/02/sample_input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01 01/main.cpp)
add_executable(02 02/main.cpp)

# target_link_libraries(01 PRIVATE MyLibExample)