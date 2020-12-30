
add_executable(formatting_ostream ostream_format.cpp)
target_link_libraries(formatting_ostream PRIVATE doctest)
add_test(NAME "formatting::ostream" COMMAND formatting_ostream)

# temporarily disabled due to a cxx20 compatibility issue:
# https://github.com/boostorg/format/issues/67

#add_executable(formatting_printf printf.cpp)
#target_link_libraries(formatting_printf PRIVATE doctest)
#target_include_directories(formatting_printf PRIVATE ${Boost_INCLUDE_DIRS})
#add_test(NAME "formatting::printf" COMMAND formatting_printf)

add_executable(formatting_cxx_format_function cxx20_format.cpp)
target_link_libraries(formatting_cxx_format_function PRIVATE doctest autotimer)
add_test(NAME "formatting::cxx20_format_function" COMMAND formatting_cxx_format_function)