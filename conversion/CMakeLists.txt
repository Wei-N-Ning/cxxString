
add_tinytest_executable(tolower_toint tolower_toint.cpp)
set_target_properties(tolower_toint
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "conversion::tolower,toint" COMMAND tolower_toint)

add_tinytest_executable(tointeger tointeger.cpp)
set_target_properties(tointeger
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "conversion::tointeger" COMMAND tointeger)

add_tinytest_executable(from_numeric from_numeric.cpp)
set_target_properties(from_numeric
    PROPERTIES
    CXX_STANDARD 14)
add_test(
    NAME
    "conversion::from-numeric-values"
    COMMAND
    from_numeric
)