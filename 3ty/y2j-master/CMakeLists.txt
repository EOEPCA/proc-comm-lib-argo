cmake_minimum_required (VERSION 2.8.12)

project (y2j)

set(CMAKE_CXX_STANDARD 17)

option(Y2J_BUILD_TESTS "Build tests for Y2J" ON)

add_subdirectory(libyaml)

include_directories(libyaml/include rapidjson)

add_library(y2j y2j.cpp)

target_link_libraries(y2j yaml)

add_executable(parse-test parse-test.cpp)

target_link_libraries(parse-test y2j)

if (Y2J_BUILD_TESTS)
  add_subdirectory(tests)
endif()
