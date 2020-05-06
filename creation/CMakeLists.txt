
add_executable(creation_modern modern_creation.cpp)
target_link_libraries(creation_modern PRIVATE doctest)
add_test(NAME "creation::modern" COMMAND creation_modern)