
# source:
# https://cmake.org/cmake/help/v3.0/module/FindBoost.html
# find_package(Boost 1.36.0)
#if(Boost_FOUND)
#  include_directories(${Boost_INCLUDE_DIRS})
#  add_executable(foo foo.cc)
#endif()
add_executable(splitString splitString.cpp)
target_link_libraries(splitString doctest ${Boost_LIBRARIES})
target_include_directories(splitString PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "partition::split-string" COMMAND splitString)

add_executable(substring substring.cpp)
target_link_libraries(substring doctest)
add_test(NAME "partition::std-substring" COMMAND substring)

add_executable(string_find_split find_split.cpp)
target_link_libraries(string_find_split doctest)
add_test(
    NAME
    "partition::find-split"
    COMMAND
    string_find_split
)