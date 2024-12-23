enable_testing()

add_executable(
  13Tests
  13Tests.cpp
)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

target_link_libraries(
  13Tests
  13_lib
  Common
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(13Tests)