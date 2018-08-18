
add_executable(iomanipHexFormat strstream_hexformat.cpp)
set_target_properties(iomanipHexFormat
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "stringstream::iomanip::hex-format"
    COMMAND iomanipHexFormat)

add_executable(iomanipAdjustify strstream_padding.cpp)
set_target_properties(iomanipAdjustify
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "stringstream::iomanip::adjustify"
    COMMAND iomanipAdjustify)

add_executable(istream_iterator istream_iterator.cpp)
set_target_properties(istream_iterator
    PROPERTIES
    CXX_STANDARD 14)

add_executable(istreambuf_iterator istreambuf_iterator.cpp)
set_target_properties(istreambuf_iterator
    PROPERTIES
    CXX_STANDARD 14)

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
endif (BASH_PROGRAM)
