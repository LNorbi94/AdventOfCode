cmake_minimum_required(VERSION 3.1...3.27)

project(
  AdventOfCode
  VERSION 23.0
  LANGUAGES CXX)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input/complete.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input/sample.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input/sample2.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(04 main.cpp)

target_link_libraries(04 PRIVATE Common)
