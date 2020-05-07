
add_executable(formatting_ostream ostream_format.cpp)
target_link_libraries(formatting_ostream PRIVATE doctest)
add_test(NAME "formatting::ostream" COMMAND formatting_ostream)
