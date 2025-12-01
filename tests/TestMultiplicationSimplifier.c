//
// Created by nicholas on 1/12/2025.
//
#include "TestMultiplicationSimplifier.h"

#include <stdlib.h>

#include "../Unity/src/unity.h"
#include "../src/Tokenizer.h"
#include "../src/simplifier/MultiplicationSimplifier.h"

void test_multiplicationSimplify() {
    struct Token *initialTokens = tokenize("x * 4 - 8 = 10 * 16x - 14 + 5 * 5");
    struct Token *simplifiedTokens = multiplicationSimplify(initialTokens);
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