add_executable(string_view_ownership ownership.cpp)
target_link_libraries(string_view_ownership PRIVATE doctest)
add_test(NAME "string-view::ownership" COMMAND string_view_ownership)

add_executable(string_view_creation creation.cpp)
target_link_libraries(string_view_creation PRIVATE doctest)
add_test(NAME "string-view::creation" COMMAND string_view_creation)
