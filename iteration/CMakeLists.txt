
add_executable(iterlines iterlines.cpp)
target_include_directories(iterlines PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(iterlines doctest)
