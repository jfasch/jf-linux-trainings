cmake_minimum_required(VERSION 3.12)
project(jf-linuxish)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
find_package(Threads)

include_directories(${PROJECT_SOURCE_DIR}/src)
include(cmake/nodes.cmake)

add_subdirectory(src)
add_subdirectory(programs)
