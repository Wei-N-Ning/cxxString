
add_executable(literals_multi_lines multi_lines.cpp)
add_test(NAME "literals::multiple-lines" COMMAND literals_multi_lines)

add_executable(literals_r_string r_string.cpp)
add_test(NAME "literals::r-string" COMMAND literals_r_string)

add_executable(literals_custom_literals custom_literal.cpp)
target_link_libraries(literals_custom_literals PRIVATE doctest)
add_test(NAME "literals::custom-literals" COMMAND literals_custom_literals)