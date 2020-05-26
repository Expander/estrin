add_executable(test_estrin_c test_estrin_c.cpp)
target_link_libraries(test_estrin_c estrin)
add_test(NAME test_estrin_c COMMAND test_estrin_c)

add_executable(test_bench test_bench.cpp)
target_link_libraries(test_bench estrin)
add_test(NAME test_bench COMMAND test_bench)
