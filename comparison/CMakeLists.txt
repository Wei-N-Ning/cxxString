
add_executable(comparison_equal equal.cpp)
target_link_libraries(comparison_equal PRIVATE doctest)
target_include_directories(comparison_equal PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "comparison::equal" COMMAND comparison_equal)
