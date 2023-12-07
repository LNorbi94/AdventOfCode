cmake_minimum_required(VERSION 3.1...3.27)

project(
  AdventOfCode
  VERSION 23.0
  LANGUAGES CXX)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input/complete.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input/sample.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
add_executable(${ProjectId} main.cpp source/Card.cpp "source/Card2.h" "source/Card2.cpp")

target_link_libraries(${ProjectId} PRIVATE Common)
