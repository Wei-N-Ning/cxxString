
add_executable(conversion_tolower_toint tolower_toint.cpp)
target_link_libraries(conversion_tolower_toint PRIVATE doctest)
add_test(NAME "conversion::tolower-toint" COMMAND conversion_tolower_toint)

add_executable(conversion_tointeger tointeger.cpp)
target_link_libraries(conversion_tointeger PRIVATE doctest)
target_include_directories(conversion_tointeger PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "conversion::tointeger" COMMAND conversion_tointeger)

add_executable(conversion_from_numeric from_numeric.cpp)
target_link_libraries(conversion_from_numeric PRIVATE doctest)
target_include_directories(conversion_from_numeric PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "conversion::from-numeric-values" COMMAND conversion_from_numeric)

add_executable(conversion_from_time from_time.cpp)
target_link_libraries(conversion_from_time  PRIVATE doctest)
add_test(NAME "conversion::from-time" COMMAND conversion_from_time)

add_executable(conversion_to_readable to_readable.cpp)
target_link_libraries(conversion_to_readable PRIVATE doctest)
add_test(NAME "conversion::to-readable" COMMAND conversion_to_readable)

add_executable(conversion_lower_upper_cases lower_upper_cases.cpp)
target_link_libraries(conversion_lower_upper_cases PRIVATE doctest)
target_include_directories(conversion_lower_upper_cases PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "conversion::lower-upper-cases" COMMAND conversion_lower_upper_cases)

add_executable(conversion_parse_to_numeric parse_to_numeric.cpp)
target_link_libraries(conversion_parse_to_numeric PRIVATE doctest)
add_test(NAME "conversion::parse_to_numeric_types" COMMAND conversion_parse_to_numeric)

