//
// Created by nicholas on 26/12/2025.
//
#include "TestExponentiationSimplifier.h"
#include <stdlib.h>
#include "../Unity/src/unity.h"
#include "../src/Tokenizer.h"
#include "../src/simplifier/ExponentiationSimplifier.h"
#include "../src/model/Equation.h"
#include "../src/model/Token.h"
#include "../src/model/TokenType.h"
#define FLOAT_DELTA 0.0001

void test_exponentiationSimplify() {
    Equation *equation = tokenize("x ^ 2 + 5^4 = 7.5^3");
    Token *tokens = equation->tokens;
    exponentiationSimplify(equation);
    TEST_ASSERT_EQUAL(5, equation->len);
    TEST_ASSERT_FALSE(equation->hasExponentiation);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(625, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 421.875, tokens->value);
    tokens -= 4;
    free(tokens);
    free(equation);
}

void test_exponentiationSimplify2() {
    Equation *equation = tokenize("4.5x^4 + 8^2^2 = 3.3x^2^2 - 2^0");
    Token *tokens = equation->tokens;
    exponentiationSimplify(equation);
    TEST_ASSERT_EQUAL(7, equation->len);
    TEST_ASSERT_FALSE(equation->hasExponentiation);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 410.0625, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(4096, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 118.5921, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 5;
    free(tokens);
    free(equation);
}

void testExponentiationSimplifier_runTests() {
    RUN_TEST(test_exponentiationSimplify);
    RUN_TEST(test_exponentiationSimplify2);
}