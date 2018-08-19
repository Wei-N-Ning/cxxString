
add_executable(multi_lines multi_lines.cpp)
set_target_properties(multi_lines
    PROPERTIES
    CXX_STANDARD 14)
add_test(
    NAME
    "string-literal::multiple-lines"
    COMMAND
    multi_lines
)

add_executable(embedded_text_file embedded_text_file.cpp)
set_target_properties(embedded_text_file
    PROPERTIES
    CXX_STANDARD 14)
