
add_executable(sregex_token_iterator sregex_token_iterator.cpp)

add_executable(option_modifiers option_modifiers.cpp)

add_executable(regex_iterator regex_iterator.cpp)

add_executable(capture_groups capture_groups.cpp)

add_executable(varlength_lookbehind varlength_lookbehind.cpp)
target_include_directories(varlength_lookbehind PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(varlength_lookbehind doctest ${Boost_LIBRARIES})

add_executable(plate_number_extraction plate_number_extraction.cpp)
target_link_libraries(plate_number_extraction doctest ${Boost_LIBRARIES})
target_include_directories(plate_number_extraction PUBLIC ${Boost_INCLUDE_DIRS})
add_test(NAME "search::plate number extraction" COMMAND plate_number_extraction)


# //////// test scripts ////////
if (BASH_PROGRAM)
    add_test(
        NAME
        "regex::sregex-token-iterator::delimiter"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/sregex_token_iterator_test.sh $<TARGET_FILE:sregex_token_iterator>
    )
    add_test(
        NAME
        "regex::option-modifier::icase"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/option_modifiers_test.sh $<TARGET_FILE:option_modifiers>
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
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/capture_groups_test.sh $<TARGET_FILE:capture_groups>
    )
endif (BASH_PROGRAM)