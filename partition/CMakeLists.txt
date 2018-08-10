
add_tinytest_executable(boostSplit splitString.cpp)
set_target_properties(boostSplit
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "partition::boost-string-split" COMMAND boostSplit)

add_tinytest_executable(substring substring.cpp)
set_target_properties(substring
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "partition::std-substring" COMMAND substring)

