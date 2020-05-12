add_executable(aggregate_join join.cpp)
target_link_libraries(aggregate_join PRIVATE doctest)
add_test(NAME "aggregate::join" COMMAND aggregate_join)
