cmake_minimum_required(VERSION 3.12)
project(jf-linuxish)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/src)
include(cmake/nodes.cmake)
add_definitions(-Werror -Wswitch -Wswitch-enum)


add_subdirectory(src)
add_subdirectory(unittests)
add_subdirectory(topics)
