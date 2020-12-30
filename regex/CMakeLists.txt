
add_executable(regex_sregex_token_iterator iterator/sregex_token_iterator.cpp)
target_link_libraries(regex_sregex_token_iterator PRIVATE doctest absl_strings)
add_test(NAME "regex::iterator::sregex_token_iterator" COMMAND regex_sregex_token_iterator)

add_executable(regex_option_modifiers modifiers/option_modifiers.cpp)
target_link_libraries(regex_option_modifiers PRIVATE doctest)
add_test(NAME "regex::modifiers::option-modifiers" COMMAND regex_option_modifiers)

add_executable(regex_iterator iterator/regex_iterator.cpp)
target_link_libraries(regex_iterator PRIVATE doctest)
add_test(NAME "regex::iterator" COMMAND regex_iterator)

add_executable(regex_capture_groups group/capture_groups.cpp)
target_link_libraries(regex_capture_groups PRIVATE doctest)
add_test(NAME "regex::groups::capture-group" COMMAND regex_capture_groups)

add_executable(regex_varlength_lookbehind lookaround/varlength_lookbehind.cpp)
target_include_directories(regex_varlength_lookbehind PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(regex_varlength_lookbehind doctest ${Boost_LIBRARIES})
add_test(NAME "regex::variable-length-lookbehind" COMMAND regex_varlength_lookbehind)

add_executable(regex_lookbehind lookaround/lookbehind.cpp)
target_link_libraries(regex_lookbehind PRIVATE doctest)
add_test(NAME "regex::lookbehind" COMMAND regex_lookbehind)

add_executable(regex_plate_number_extraction plate_number_extraction.cpp)
target_link_libraries(regex_plate_number_extraction doctest ${Boost_LIBRARIES})
target_include_directories(regex_plate_number_extraction PUBLIC ${Boost_INCLUDE_DIRS})
add_test(NAME "regex::plate-number-extraction" COMMAND regex_plate_number_extraction)

add_executable(regex_with_cstring with_cstring.cpp)
target_link_libraries(regex_with_cstring doctest ${Boost_LIBRARIES})
target_include_directories(regex_with_cstring PUBLIC ${Boost_INCLUDE_DIRS})
add_test(NAME "regex::with-cstring" COMMAND regex_with_cstring)

add_executable(regex_ctre_test ctre_test.cpp)
target_link_libraries(regex_ctre_test PRIVATE doctest)
target_include_directories(regex_ctre_test PRIVATE ${PROJECT_SOURCE_DIR}/vendor/compile-time-regular-expressions/single-header)
add_test(NAME "regex::ctre::test" COMMAND regex_ctre_test)

add_executable(regex_replace_words replace/replace_words.cpp)
target_link_libraries(regex_replace_words PRIVATE doctest)
add_test(NAME "regex::replace-words" COMMAND regex_replace_words)

add_executable(regex_capitalize_words replace/capitalize_words.cpp)
target_link_libraries(regex_capitalize_words PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(regex_capitalize_words PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "regex::capitalize-words" COMMAND regex_capitalize_words)