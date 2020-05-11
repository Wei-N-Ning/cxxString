
add_executable(regex_sregex_token_iterator sregex_token_iterator.cpp)

add_executable(regex_option_modifiers option_modifiers.cpp)

add_executable(regex_iterator regex_iterator.cpp)

add_executable(regex_capture_groups capture_groups.cpp)

add_executable(regex_varlength_lookbehind varlength_lookbehind.cpp)
target_include_directories(regex_varlength_lookbehind PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(regex_varlength_lookbehind doctest ${Boost_LIBRARIES})

add_executable(regex_plate_number_extraction plate_number_extraction.cpp)
target_link_libraries(regex_plate_number_extraction doctest ${Boost_LIBRARIES})
target_include_directories(regex_plate_number_extraction PUBLIC ${Boost_INCLUDE_DIRS})
add_test(NAME "regex::plate-number-extraction" COMMAND regex_plate_number_extraction)

add_executable(regex_with_cstring with_cstring.cpp)
target_link_libraries(regex_with_cstring doctest ${Boost_LIBRARIES})
target_include_directories(regex_with_cstring PUBLIC ${Boost_INCLUDE_DIRS})
add_test(NAME "regex::with-cstring" COMMAND regex_with_cstring)


# //////// test scripts ////////
if (BASH_PROGRAM)
    add_test(
        NAME
        "regex::sregex-token-iterator::delimiter"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/regex_sregex_token_iterator_test.sh $<TARGET_FILE:regex_sregex_token_iterator>
    )
    add_test(
        NAME
        "regex::option-modifier::icase"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/regex_option_modifiers_test.sh $<TARGET_FILE:regex_option_modifiers>
    )
    add_test(
        NAME
        "regex::sregex_iterator"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/regex_iterator_test.sh $<TARGET_FILE:regex_iterator>
    )
    add_test(
        NAME
        "regex::search::capture-groups"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/regex_capture_groups_test.sh $<TARGET_FILE:regex_capture_groups>
    )
endif (BASH_PROGRAM)
