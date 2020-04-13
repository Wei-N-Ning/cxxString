
set(Boost_USE_STATIC_LIBS on)
find_package(Boost REQUIRED)

# source:
# https://cmake.org/cmake/help/v3.0/module/FindBoost.html
# find_package(Boost 1.36.0)
#if(Boost_FOUND)
#  include_directories(${Boost_INCLUDE_DIRS})
#  add_executable(foo foo.cc)
#endif()
add_executable(boostSplit splitString.cpp)
target_link_libraries(boostSplit doctest)
target_include_directories(boostSplit PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "partition::boost-string-split-perf" COMMAND boostSplit)

add_executable(substring substring.cpp)
target_link_libraries(substring doctest)
add_test(NAME "partition::std-substring" COMMAND substring)

add_executable(string_find_split find_split.cpp)
target_link_libraries(string_find_split doctest)
add_test(
    NAME
    "partition::find-split"
    COMMAND
    string_find_split
)