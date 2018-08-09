
add_executable(fromCString create_from_cstring.cpp)
set_target_properties(fromCString
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "creation::fromCString" COMMAND fromCString)