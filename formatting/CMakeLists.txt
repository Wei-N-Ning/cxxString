
add_executable(formatting_ostream ostream_format.cpp)
target_link_libraries(formatting_ostream PRIVATE doctest)
add_test(NAME "formatting::ostream" COMMAND formatting_ostream)

add_executable(formatting_printf printf.cpp)
target_link_libraries(formatting_printf PRIVATE doctest)
target_include_directories(formatting_printf PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "formatting::printf" COMMAND formatting_printf)