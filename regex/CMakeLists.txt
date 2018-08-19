
add_executable(sregex_token_iterator sregex_token_iterator.cpp)
set_target_properties(sregex_token_iterator
    PROPERTIES
    CXX_STANDARD 14)

add_executable(option_modifiers option_modifiers.cpp)
set_target_properties(option_modifiers
    PROPERTIES
    CXX_STANDARD 14)

add_executable(regex_iterator regex_iterator.cpp)
set_target_properties(regex_iterator
    PROPERTIES
    CXX_STANDARD 14)

add_executable(capture_groups capture_groups.cpp)
set_target_properties(capture_groups
    PROPERTIES
    CXX_STANDARD 14)

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