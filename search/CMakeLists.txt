add_executable(endswith endswith.cpp)
target_link_libraries(endswith doctest)
add_test(NAME "search::endswith" COMMAND endswith)

add_executable(find_substr find_substr.cpp)
target_link_libraries(find_substr doctest)
add_test(NAME "search::find-substr" COMMAND find_substr)

add_executable(palindrome palindrome.cpp)
target_link_libraries(palindrome doctest)
add_test(NAME "search::palindrome" COMMAND palindrome)
