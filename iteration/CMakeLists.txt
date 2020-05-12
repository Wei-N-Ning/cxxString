
add_executable(iteration_iterlines iterlines.cpp)
target_include_directories(iteration_iterlines PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(iteration_iterlines PRIVATE doctest)
