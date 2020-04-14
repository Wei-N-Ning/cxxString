add_executable(join join.cpp)
target_link_libraries(join doctest)
add_test(NAME "aggregate::join" COMMAND join)
