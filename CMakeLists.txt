cmake_minimum_required(VERSION 3.8)
project(C++String)

enable_testing()

include(cmake/tinyCUnit.cmake)

add_subdirectory(addition)
add_subdirectory(conversion)
add_subdirectory(creation)
add_subdirectory(inplace)
add_subdirectory(partition)
add_subdirectory(stream)
