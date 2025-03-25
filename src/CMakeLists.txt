cmake_minimum_required(VERSION 3.22)
project(Term CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_library(resources files.cpp files.hpp sequence.hpp display.hpp display.cpp)
add_library(resources_new sequence.hpp terminal.cpp terminal.hpp screen.cpp screen.hpp)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE resources_new)
