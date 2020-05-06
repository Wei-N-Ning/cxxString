
add_executable(strip_space strip_space.cpp)
target_link_libraries(strip_space PRIVATE doctest)
add_test(NAME "strip::space" COMMAND strip_space)