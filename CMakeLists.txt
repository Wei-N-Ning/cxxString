cmake_minimum_required(VERSION 3.8)
project(C++String)

enable_testing()

# source:
# http://voices.canonical.com/jussi.pakkanen/2013/03/26/a-list-of-common-cmake-antipatterns/
# the user might set values with the ccmake configuration tool.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -Wextra")
include(cmake/tinyCUnit.cmake)

# source:
# how to integrate bash script in ctest
# https://stackoverflow.com/questions/25627336/integrate-bash-test-scripts-in-cmake
find_program(BASH_PROGRAM bash)

add_subdirectory(addition)
add_subdirectory(conversion)
add_subdirectory(creation)
add_subdirectory(inplace)
add_subdirectory(literals)
add_subdirectory(partition)
add_subdirectory(regex)
add_subdirectory(stream)
add_subdirectory(charclasses)