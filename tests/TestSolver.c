//
// Created by nicholas on 15/11/2025.
//
#include "TestSolver.h"
#include "../src/Solver.h"
#include "../Unity/src/unity.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
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

void test_solveMultiplication() {
    float result = solve("x + 16 * 3x = 42x * 3 + 8 * 2");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, -0.2077922, result);
}

void test_solveDivision() {
    float result = solve("x + 16 / 4 = 42x / 2 + 8 / 2");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0, result);
}

void test_solveFloatNumbers() {
    float result = solve("32.5x * 2 = 129.75 + 0.25");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 2, result);
}

void test_solveFloatNumbers2() {
    float result = solve("983.456x + 78.4 / 2 = 42.8x * 7.2 + 8.897 * 789.2 - 43x");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 9.720661, result);
}

void test_solveGrammarError() {
    pid_t pid = fork();
    if (pid == 0) {
        solve("2x 6x = 9");
        exit(0);
    }

    int status;
    wait(&status);
    TEST_ASSERT_EQUAL(1, WEXITSTATUS(status));
}

void testSolver_runTests() {
    RUN_TEST(test_solve);
    RUN_TEST(test_solve2);
    RUN_TEST(test_solve3);
    RUN_TEST(test_solve4);
    RUN_TEST(test_solve5);
    RUN_TEST(test_solve6);
    RUN_TEST(test_solve7);
    RUN_TEST(test_solveMultiplication);
    RUN_TEST(test_solveDivision);
    RUN_TEST(test_solveFloatNumbers);
    RUN_TEST(test_solveFloatNumbers2);
    RUN_TEST(test_solveGrammarError);
}