
add_executable(arraylikemodification array_like_modification.cc)
target_link_libraries(arraylikemodification doctest)
add_test(NAME "inplace-editing::array-like-modification"
    COMMAND arraylikemodification)

add_executable(replaceChars replaceChars.cpp)
target_link_libraries(replaceChars doctest)
add_test(NAME "inplace-editing::replace-chars"
    COMMAND replaceChars)

add_executable(capitalize capitalize.cpp)
target_link_libraries(capitalize doctest)
add_test(NAME "inplace-editing::capitalize" COMMAND capitalize)