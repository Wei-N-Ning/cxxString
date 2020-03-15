add_tinytest_executable(charclasses predicates.cc predicates.hh)
set_target_properties(charclasses
    PROPERTIES
    CXX_STANDARD 17)
add_test(NAME "charclasses::predicates" COMMAND charclasses)