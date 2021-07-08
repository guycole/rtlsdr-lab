#
# lab01
#
cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -o3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJ_NAME "lab01")
project(${PROJ_NAME} VERSION 0.0)
set(CMAKE_BUILD_TYPE Debug) # Debug, Release, RelWithDebInfo

include_directories("include")

file(GLOB SOURCES "src/*.cc")

add_executable(${PROJ_NAME} ${SOURCES})
