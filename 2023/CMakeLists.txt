cmake_minimum_required(VERSION 3.1...3.27)

project(
  AdventOfCode
  VERSION 23.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Common
	"common/TaskSolver.h"
	"common/TaskSolver.cpp"
	"common/StringManipulation.h"
	"common/StringManipulation.cpp"
 "common/FileParser.h" "common/FileParser.cpp")

include_directories(common)

# 29 stars at end of December 25th
add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(04)
add_subdirectory(05)
add_subdirectory(06)
add_subdirectory(07)
add_subdirectory(08)
add_subdirectory(09)
add_subdirectory(10)
add_subdirectory(13)
add_subdirectory(15)
add_subdirectory(16)
add_subdirectory(17)
add_subdirectory(18)
add_subdirectory(19)
add_subdirectory(20)
add_subdirectory(21)
add_subdirectory(23)
