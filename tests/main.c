//
// Created by nicholas on 09/11/2025.
//
#include "../Unity/src/unity.h"
#include "TestTokenizer.h"
#include "TestSolver.h"
#include "TestGrammarChecker.h"
#include "TestMultiplicationSimplifier.h"
#include "TestDivisionSimplifier.h"

void setUp() { }

void tearDown() { }

int main() {
    UNITY_BEGIN();
    testTokenizer_runTests();
    testSolver_runTests();
    testGrammarChecker_runTests();
    testMultiplicationSimplifier_runTests();
    testDivisionSimplifier_runTests();
    UNITY_END();
    return 0;
}