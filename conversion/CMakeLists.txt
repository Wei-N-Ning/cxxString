
add_executable(tolower_toint tolower_toint.cpp)
target_link_libraries(tolower_toint doctest)
add_test(NAME "conversion::tolower,toint" COMMAND tolower_toint)

add_executable(tointeger tointeger.cpp)
target_link_libraries(tointeger doctest)
add_test(NAME "conversion::tointeger" COMMAND tointeger)

add_executable(from_numeric from_numeric.cpp)
target_link_libraries(from_numeric doctest)
add_test(
    NAME
    "conversion::from-numeric-values"
    COMMAND
    from_numeric
)

add_executable(from_time from_time.cpp)
target_link_libraries(from_time doctest)
add_test(
    NAME
    "conversion::from-time"
    COMMAND
    from_time)

