
find_package(Boost)

# source:
# https://cmake.org/cmake/help/v3.0/module/FindBoost.html
# find_package(Boost 1.36.0)
#if(Boost_FOUND)
#  include_directories(${Boost_INCLUDE_DIRS})
#  add_executable(foo foo.cc)
#endif()
if(Boost_FOUND)
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

