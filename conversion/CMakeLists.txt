
add_tinytest_executable(tolower_toint tolower_toint.cpp)
set_target_properties(tolower_toint
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "conversion::tolower,toint" COMMAND tolower_toint)
