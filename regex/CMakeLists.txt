
add_executable(sregex_token_iterator sregex_token_iterator.cpp)
set_target_properties(sregex_token_iterator
    PROPERTIES
    CXX_STANDARD 14)

add_executable(option_modifiers option_modifiers.cpp)
set_target_properties(option_modifiers
    PROPERTIES
    CXX_STANDARD 14)

# //////// test scripts ////////
if (BASH_PROGRAM)
    add_test(
        NAME
        "sregex-token-iterator::delimiter"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/sregex_token_iterator_test.sh $<TARGET_FILE:sregex_token_iterator>
    )
    add_test(
        NAME
        "regex::option-modifier::icase"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/option_modifiers_test.sh $<TARGET_FILE:option_modifiers>
    )
endif (BASH_PROGRAM)