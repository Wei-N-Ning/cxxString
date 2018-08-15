
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