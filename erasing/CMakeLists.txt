
add_executable(erasing_delete_chars delete_chars.cpp)
target_include_directories(erasing_delete_chars PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(erasing_delete_chars PRIVATE doctest)
add_test(NAME "erasing::delete-chars" COMMAND erasing_delete_chars)

