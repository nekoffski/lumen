cmake_minimum_required(VERSION 3.10)
project(lumen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions(-DSPDLOG_COMPILED_LIB=1)

add_subdirectory(vendor)
add_subdirectory(src)
