
add_executable(inplace_arraylikemodification array_like_modification.cc)
target_link_libraries(inplace_arraylikemodification doctest)
add_test(NAME "inplace-editing::array-like-modification"
    COMMAND inplace_arraylikemodification)

add_executable(inplace_replaceChars replaceChars.cpp)
target_link_libraries(inplace_replaceChars doctest)
add_test(NAME "inplace-editing::replace-chars"
    COMMAND inplace_replaceChars)

add_executable(inplace_capitalize capitalize.cpp)
target_link_libraries(inplace_capitalize doctest ${Boost_LIBRARIES})
target_include_directories(inplace_capitalize PUBLIC ${Boost_INCLUDE_DIRS})
add_test(NAME "inplace-editing::capitalize" COMMAND inplace_capitalize)