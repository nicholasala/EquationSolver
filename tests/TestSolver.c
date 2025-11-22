//
// Created by nicholas on 15/11/2025.
//
#include "TestSolver.h"
#include "../src/Solver.h"
#include "../Unity/src/unity.h"

void test_solve() {
    float result = solve("x = 6");
    TEST_ASSERT_EQUAL(6, result);
}

void test_solve2() {
    float result = solve("x + 4 =");
    TEST_ASSERT_EQUAL(-4, result);
}

void test_solve3() {
    float result = solve("x + 4 = 8 - 7x");
    TEST_ASSERT_EQUAL(0.5, result);
}

void test_solve4() {
    float result = solve("x + 45x - 89 + 2 = 8 - 7x + 64x - 29");
    TEST_ASSERT_EQUAL(-6, result);
}

//TODO test error cases

void testSolver_runTests() {
    RUN_TEST(test_solve);
    RUN_TEST(test_solve2);
    RUN_TEST(test_solve3);
    RUN_TEST(test_solve4);
}