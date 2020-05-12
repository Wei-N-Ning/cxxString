cmake_minimum_required(VERSION 3.10)
project(C++String LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_USE_STATIC_LIBS TRUE)
set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/vendor/boost-1.72.0)
find_package(Boost 1.72.0 REQUIRED COMPONENTS regex)

add_subdirectory(vendor/doctest)
enable_testing()

# source:
# http://voices.canonical.com/jussi.pakkanen/2013/03/26/a-list-of-common-cmake-antipatterns/
# the user might set values with the ccmake configuration tool.
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -Wextra")

# source:
# how to integrate bash script in ctest
# https://stackoverflow.com/questions/25627336/integrate-bash-test-scripts-in-cmake
find_program(BASH_PROGRAM bash)

add_subdirectory(aggregate)
add_subdirectory(addition)
add_subdirectory(conversion)
add_subdirectory(creation)
add_subdirectory(iteration)
add_subdirectory(inplace)
add_subdirectory(search)
add_subdirectory(literals)
add_subdirectory(partition)
add_subdirectory(regex)
add_subdirectory(stream)
add_subdirectory(charclasses)
add_subdirectory(strip)
add_subdirectory(parsing)
add_subdirectory(formatting)
add_subdirectory(str_as_container)
