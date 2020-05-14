
add_executable(parsing_comma_separate_list parse_csl.cpp)
target_link_libraries(parsing_comma_separate_list PRIVATE doctest)
add_test(NAME "parsing::comma-separate-list" COMMAND parsing_comma_separate_list)

add_executable(parsing_struct parse_struct.cpp)
target_link_libraries(parsing_struct PRIVATE doctest)
add_test(NAME "parsing::struct" COMMAND parsing_struct)

add_executable(parsing_key_value_pairs parse_kv_pairs.cpp)
target_link_libraries(parsing_key_value_pairs PRIVATE doctest)
add_test(NAME "parsing::key-value-pairs" COMMAND parsing_key_value_pairs)

add_executable(parsing_column_separated_text read_column_separated_text.cpp)
target_link_libraries(parsing_column_separated_text PRIVATE doctest)
add_test(NAME "parsing::read-column-separated-text" COMMAND parsing_column_separated_text)
