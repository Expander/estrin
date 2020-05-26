add_executable(test_estrin_c test_estrin_c.cpp)
target_link_libraries(test_estrin_c estrin)
add_test(NAME test_estrin_c COMMAND test_estrin_c)
