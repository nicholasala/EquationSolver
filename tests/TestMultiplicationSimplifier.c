//
// Created by nicholas on 1/12/2025.
//
#include "TestMultiplicationSimplifier.h"
#include <stdlib.h>
#include "../Unity/src/unity.h"
#include "../src/Tokenizer.h"
#include "../src/simplifier/MultiplicationSimplifier.h"
#include "../src/model/Equation.h"
#include "../src/model/Token.h"

void test_multiplicationSimplify() {
    struct Equation *initialTokens = tokenize("x * 4 - 8 = 10 * 16x - 14 + 5 * 5");
    struct Equation *simplifiedEquation = multiplicationSimplify(initialTokens);
    struct Token *simplifiedTokens = simplifiedEquation->tokens;
    TEST_ASSERT_EQUAL(X, simplifiedTokens->type);
    TEST_ASSERT_EQUAL(4, simplifiedTokens->value);
    simplifiedTokens++;
    TEST_ASSERT_EQUAL(MINUS, simplifiedTokens->type);
    simplifiedTokens++;
    TEST_ASSERT_EQUAL(NUMBER, simplifiedTokens->type);
    TEST_ASSERT_EQUAL(8, simplifiedTokens->value);
    simplifiedTokens++;
    TEST_ASSERT_EQUAL(EQUALS, simplifiedTokens->type);
    simplifiedTokens++;
    TEST_ASSERT_EQUAL(X, simplifiedTokens->type);
    TEST_ASSERT_EQUAL(160, simplifiedTokens->value);
    simplifiedTokens++;
    TEST_ASSERT_EQUAL(MINUS, simplifiedTokens->type);
    simplifiedTokens++;
    TEST_ASSERT_EQUAL(NUMBER, simplifiedTokens->type);
    TEST_ASSERT_EQUAL(14, simplifiedTokens->value);
    simplifiedTokens++;
    TEST_ASSERT_EQUAL(PLUS, simplifiedTokens->type);
    simplifiedTokens++;
    TEST_ASSERT_EQUAL(NUMBER, simplifiedTokens->type);
    TEST_ASSERT_EQUAL(25, simplifiedTokens->value);
    simplifiedTokens++;
    TEST_ASSERT_EQUAL(END, simplifiedTokens->type);
    simplifiedTokens -= 9;
    free(simplifiedTokens);
    free(initialTokens);
}

void testMultiplicationSimplifier_runTests() {
    RUN_TEST(test_multiplicationSimplify);
}