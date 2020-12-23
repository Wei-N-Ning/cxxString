add_executable(search_endswith endswith.cpp)
target_link_libraries(search_endswith doctest)
add_test(NAME "search::endswith" COMMAND search_endswith)

add_executable(search_find_substr_searcher find_substr_searcher.cpp)
target_link_libraries(search_find_substr_searcher PRIVATE doctest)
add_test(NAME "search::find-substr-with-searcher" COMMAND search_find_substr_searcher)

add_executable(search_palindrome palindrome.cpp)
target_link_libraries(search_palindrome doctest)
add_test(NAME "search::palindrome" COMMAND search_palindrome)

add_executable(search_word_count word_count.cpp)
target_link_libraries(search_word_count PRIVATE doctest)
target_include_directories(search_word_count PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(search_word_count
        PRIVATE TEXT_FILE=${PROJECT_SOURCE_DIR}/resources/text)
add_test(NAME "search::word-count" COMMAND search_word_count)