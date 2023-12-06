cmake_minimum_required(VERSION 3.1...3.27)

project(
  AdventOfCode
  VERSION 23.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Common "common/TaskSolver.h" "common/TaskSolver.cpp" "common/StringManipulation.h" "common/StringManipulation.cpp" common/BigInt.hpp)

include_directories(common)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/01/input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/03/sample_input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/01/sample_input2.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/02/sample_input.txt
#        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01 01/main.cpp "01/FirstTask.h" "01/FirstTask.cpp" "01/SecondTask.h" "01/SecondTask.cpp")
add_executable(02 02/main.cpp)
add_executable(03 03/main.cpp)

target_link_libraries(01 PRIVATE Common)
target_link_libraries(02 PRIVATE Common)

add_subdirectory(04)
add_subdirectory(05)
add_subdirectory(06)
