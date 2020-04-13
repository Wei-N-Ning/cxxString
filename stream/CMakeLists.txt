
add_executable(iomanipHexFormat strstream_hexformat.cpp)
add_test(NAME "stringstream::iomanip::hex-format"
    COMMAND iomanipHexFormat)

add_executable(iomanipAdjustify strstream_padding.cpp)
add_test(NAME "stringstream::iomanip::adjustify"
    COMMAND iomanipAdjustify)

add_executable(istream_iterator istream_iterator.cpp)

add_executable(istreambuf_iterator istreambuf_iterator.cpp)

add_executable(cin_getline cin_getline.cpp)

add_executable(ostream_iterator ostream_iterator.cpp)
target_link_libraries(ostream_iterator doctest)
add_test(NAME "ostream_iterator::test"
    COMMAND ostream_iterator)

add_executable(overloading overloading.cpp)
target_link_libraries(overloading doctest)
add_test(NAME "ostream-operator::overload-name-lookup"
    COMMAND overloading)

add_executable(echo_program echo_program.cc)

add_executable(read_column_separated_text
    read_column_separated_text.cpp)
target_link_libraries(read_column_separated_text doctest)
add_test(NAME "ifstream::read-column-separated-text"
    COMMAND read_column_separated_text)

# source:
# use ctest to execute test-driver (a bash script)
# 1) how to retrieve target executable path:
# https://cmake.org/cmake/help/v3.0/command/add_test.html
# add_test(NAME mytest
#         COMMAND testDriver --config $<CONFIGURATION>
#                            --exe $<TARGET_FILE:myexe>)
# 2) how to retrieve full path to bash program
# https://stackoverflow.com/questions/25627336/integrate-bash-test-scripts-in-cmake
# find_program (BASH_PROGRAM bash)
#
# 3) how to view the output from the test driver script
# https://stackoverflow.com/questions/5709914/using-cmake-how-do-i-get-verbose-output-from-ctest
# ctest --verbose
#
# //////// test scripts ////////
if (BASH_PROGRAM)
    add_test(
        NAME
        "istream_iterator::test"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/istream_iterator_test.sh $<TARGET_FILE:istream_iterator>)
    add_test(
        NAME
        "istreambuf_iterator::test"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/istreambuf_iterator_test.sh $<TARGET_FILE:istreambuf_iterator>)
    add_test(
        NAME
        "getline::stdin"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/cin_getline_test.sh $<TARGET_FILE:cin_getline>
    )
    add_test(
        NAME "iostream::echo-program"
        COMMAND
        ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/echo_program_test.sh $<TARGET_FILE:echo_program>
    )
endif (BASH_PROGRAM)
