add_executable(
        TEST_src_tests_tests
        src/FixedPoint.h
        src/tests/tests.cpp
)
add_test(NAME urmom COMMAND TEST_src_tests_tests)

