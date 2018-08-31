cmake_minimum_required(VERSION 2.6)

set(CXX_STANDARD 14)

enable_testing()

add_executable(tests
    main.cpp
    low_pass_filter.cpp
    convert_readings.cpp
    )

target_link_libraries(
    tests
    CppUTest
    CppUTestExt
)

add_test(tests tests)
