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
    Equation *equation = tokenize("x * 4 - 8 = 10 * 16x - 14 + 5 * 5");
    Token *tokens = equation->tokens;
    multiplicationSimplify(equation);
    TEST_ASSERT_EQUAL(9, equation->len);
    TEST_ASSERT_FALSE(equation->hasMultiplication);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(4, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(8, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(160, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(14, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(25, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 9;
    free(tokens);
    free(equation);
}

void test_multiplicationSimplify2() {
    Equation *equation = tokenize("x + x = 10 * 10");
    Token *tokens = equation->tokens;
    multiplicationSimplify(equation);
    TEST_ASSERT_EQUAL(5, equation->len);
    TEST_ASSERT_FALSE(equation->hasMultiplication);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(100, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 5;
    free(tokens);
    free(equation);
}

void testMultiplicationSimplifier_runTests() {
    RUN_TEST(test_multiplicationSimplify);
    RUN_TEST(test_multiplicationSimplify2);
}