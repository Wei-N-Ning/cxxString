cmake_minimum_required(VERSION 3.8)
project(C++String)

enable_testing()

include(cmake/tinyCUnit.cmake)

# source:
# how to integrate bash script in ctest
# https://stackoverflow.com/questions/25627336/integrate-bash-test-scripts-in-cmake
find_program(BASH_PROGRAM bash)

add_subdirectory(addition)
add_subdirectory(conversion)
add_subdirectory(creation)
add_subdirectory(inplace)
add_subdirectory(partition)
add_subdirectory(stream)
add_subdirectory(regex)