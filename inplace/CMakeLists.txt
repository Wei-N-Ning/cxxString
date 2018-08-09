
add_executable(arraylikemodification array_like_modification.cc)
set_target_properties(arraylikemodification
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "inplace-editing::array-like-modification"
    COMMAND arraylikemodification)