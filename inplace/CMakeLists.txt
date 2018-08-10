
add_executable(arraylikemodification array_like_modification.cc)
set_target_properties(arraylikemodification
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "inplace-editing::array-like-modification"
    COMMAND arraylikemodification)

add_tinytest_executable(replaceChars replaceChars.cpp)
set_target_properties(replaceChars
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "inplace-editing::replace-chars"
    COMMAND replaceChars)
