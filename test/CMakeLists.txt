add_executable(test_estrin test_estrin.cpp)
target_link_libraries(test_estrin estrin)
add_test(NAME test_estrin COMMAND test_estrin)

add_executable(test_bench test_bench.cpp)
target_link_libraries(test_bench estrin)
add_test(NAME test_bench COMMAND test_bench)
