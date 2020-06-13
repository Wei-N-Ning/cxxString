
# source:
# https://cmake.org/cmake/help/v3.0/module/FindBoost.html
# find_package(Boost 1.36.0)
#if(Boost_FOUND)
#  include_directories(${Boost_INCLUDE_DIRS})
#  add_executable(foo foo.cc)
#endif()
add_executable(partition_split_string splitString.cpp)
target_link_libraries(partition_split_string doctest ${Boost_LIBRARIES})
target_include_directories(partition_split_string PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "partition::split-string" COMMAND partition_split_string)

add_executable(partition_substring substring.cpp)
target_link_libraries(partition_substring PRIVATE doctest)
add_test(NAME "partition::std-substring" COMMAND partition_substring)

add_executable(partition_string_find_split find_split.cpp)
target_link_libraries(partition_string_find_split PRIVATE doctest)
add_test(
    NAME
    "partition::find-split"
    COMMAND
    partition_string_find_split
)

add_executable(partition_split_to_pair splitToPair.cpp)
target_link_libraries(partition_split_to_pair PRIVATE doctest)
add_test(NAME "partition:split-to-pair" COMMAND partition_split_to_pair)

add_executable(partition_python_style_split python_style_split.cpp)
target_link_libraries(partition_python_style_split PRIVATE doctest)
add_test(NAME "partition::python-style-split" COMMAND partition_python_style_split)
