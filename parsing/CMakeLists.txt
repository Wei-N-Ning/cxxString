
add_executable(parsing_comma_separate_list parse_csl.cpp)
target_link_libraries(parsing_comma_separate_list PRIVATE doctest)
add_test(NAME "parsing::comma-separate-list" COMMAND parsing_comma_separate_list)