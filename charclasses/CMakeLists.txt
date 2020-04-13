add_executable(charclasses predicates.cc)
target_link_libraries(charclasses doctest)
add_test(NAME "charclasses::predicates" COMMAND charclasses)