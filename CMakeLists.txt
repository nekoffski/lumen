cmake_minimum_required(VERSION 3.10)
project(lumen)

add_definitions(-DSPDLOG_COMPILED_LIB=1)

enable_testing()

add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(sandbox)