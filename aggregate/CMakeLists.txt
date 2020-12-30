add_executable(aggregate_join join.cpp)
target_link_libraries(aggregate_join PRIVATE doctest)
add_test(NAME "aggregate::join" COMMAND aggregate_join)

add_executable(aggregate_repeat repeat.cpp)
target_link_libraries(aggregate_repeat PRIVATE doctest autotimer)
add_test(NAME "aggregate::repeat" COMMAND aggregate_repeat)