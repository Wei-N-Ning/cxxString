
find_package(Boost)
if(DEFINED Boost_FOUND)
    add_tinytest_executable(boostSplit splitString.cpp)
    set_target_properties(boostSplit
        PROPERTIES
        CXX_STANDARD 14)
    add_test(NAME "partition::boost-string-split-perf" COMMAND boostSplit)
endif()

add_tinytest_executable(substring substring.cpp)
set_target_properties(substring
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "partition::std-substring" COMMAND substring)

