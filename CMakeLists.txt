cmake_minimum_required(VERSION 3.10)
project(scheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#source files
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

#Executable
add_executable(scheduler ${SRC_FILES})

#include directories
target_include_directories(scheduler PRIVATE ${PROJECT_SOURCE_DIR}/src)