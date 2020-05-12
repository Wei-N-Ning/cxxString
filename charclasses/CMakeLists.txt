add_executable(charclasses_predicates predicates.cc)
target_link_libraries(charclasses_predicates doctest)
add_test(NAME "charclasses::predicates" COMMAND charclasses_predicates)