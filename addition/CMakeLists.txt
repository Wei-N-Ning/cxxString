
add_executable(appendto appendto.cc)
set_target_properties(appendto
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "addition::append" COMMAND appendto)
