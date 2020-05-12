
add_executable(str_as_container_bitset bitset.cpp)
target_link_libraries(str_as_container_bitset PRIVATE doctest)
add_test(NAME "str-as-container::bitset" COMMAND str_as_container_bitset)