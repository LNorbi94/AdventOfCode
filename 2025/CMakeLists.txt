cmake_minimum_required(VERSION 3.31)

project(
  AdventOfCode
  VERSION 25.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# fetch latest argparse
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

file(GLOB MAIN_SRC_FILES CONFIGURE_DEPENDS "source/*.cpp")
add_executable(AoC2025 ${MAIN_SRC_FILES})

add_subdirectory(libs)

set(LIBRARY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(TASKS_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/tasks)
target_link_libraries(AoC2025 PRIVATE Common argparse)
target_include_directories(AoC2025 PRIVATE ${LIBRARY_INCLUDES})
target_include_directories(AoC2025 PRIVATE ${TASKS_INCLUDES})

foreach(X RANGE 1 6) # to 12...
  file(GLOB TASK_SRC_FILES CONFIGURE_DEPENDS "tasks/${X}/*.cpp" "tasks/${X}/*/*.cpp")
  add_library(${X}_lib
    ${TASK_SRC_FILES}
  )
  target_link_libraries(
    ${X}_lib
    Common
  )
  target_link_libraries(AoC2025 PRIVATE ${X}_lib)
  target_include_directories(${X}_lib PRIVATE ${LIBRARY_INCLUDES})

  if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/Debug/${X}.txt")
    execute_process(COMMAND curl https://adventofcode.com/2025/day/${X}/input --cookie "session=$ENV{AOC_SESSION}"
                      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                      OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/Debug/${X}.txt")
    execute_process(COMMAND curl https://adventofcode.com/2025/day/${X}/input --cookie "session=$ENV{AOC_SESSION}"
                      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                      OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/Release/${X}.txt")
  endif()

  file(GLOB TEST_FILES CONFIGURE_DEPENDS "tests/${X}/*.cpp")
  if(NOT TARGET Tests)
    add_executable(Tests ${TEST_FILES})
    target_include_directories(Tests PRIVATE ${LIBRARY_INCLUDES})
    target_include_directories(Tests PRIVATE ${TASKS_INCLUDES})
    
    target_link_libraries(
      Tests
      Common
      GTest::gtest_main
      ${X}_lib
    )
  else()
    target_sources(Tests PRIVATE ${TEST_FILES})
    target_link_libraries(Tests ${X}_lib
    )
  endif()

endforeach()

enable_testing()

include(GoogleTest)
gtest_discover_tests(Tests)
