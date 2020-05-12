
add_executable(addition_appendto appendto.cc)
add_test(NAME "addition::append" COMMAND addition_appendto)
