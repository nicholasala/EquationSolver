//
// Created by nicholas on 15/11/2025.
//
#include "TestSolver.h"
#include "../src/Solver.h"
#include "../Unity/src/unity.h"
#define FLOAT_DELTA 0.0001

void test_solve() {
    float result = solve("x = 6");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA,6, result);
}

void test_solve2() {
    float result = solve("x + 4 =");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA,-4, result);
}

void test_solve3() {
    float result = solve("x + 4 = 8 - 7x");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.5, result);
}

void test_solve4() {
    float result = solve("x + 45x - 89 + 2 = 8 - 7x + 64x - 29");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA,-6, result);
}

void test_solve5() {
    float result = solve("-9x = 8");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, -0.8888, result);
}

void test_solve6() {
    float result = solve("x + 42x + 45= 7345 - 2x");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 162.2222, result);
}

void test_solve7() {
    float result = solve("x + 42x = 42x + x");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0, result);
}

//TODO move these tests into "GrammarCheckerTest"
//Should be error, no x found
void test_solve8() {
    float result = solve("8 =");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0, result);
}

//Should be error, equation can't start with operator
void test_solve9() {
    float result = solve("+ 8x = 16");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 2, result);
}

//Should be error, equation must have an equal
void test_solve10() {
    float result = solve("18 + 9x");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, -2, result);
}

//Should be error, equation can't have two equals
void test_solve11() {
    float result = solve("2x + 4 = 54 =");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 25, result);
}

//Should be error, equation should respect orders of operators and variables/numbers
void test_solve12() {
    float result = solve("2x 4x = 9 + 3");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 2, result);
}

//Should be error, equation should respect orders of operators and variables/numbers
void test_solve13() {
    float result = solve("2x + - 1 = 9 + 3");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 6.5, result);
}

void testSolver_runTests() {
    RUN_TEST(test_solve);
    RUN_TEST(test_solve2);
    RUN_TEST(test_solve3);
    RUN_TEST(test_solve4);
    RUN_TEST(test_solve5);
    RUN_TEST(test_solve6);
    RUN_TEST(test_solve7);
    RUN_TEST(test_solve8);
    RUN_TEST(test_solve9);
    RUN_TEST(test_solve10);
    RUN_TEST(test_solve11);
    RUN_TEST(test_solve12);
    RUN_TEST(test_solve13);
}