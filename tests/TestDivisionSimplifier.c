//
// Created by nicholas on 19/12/2025.
//
#include "TestDivisionSimplifier.h"
#include <stdlib.h>
#include "../Unity/src/unity.h"
#include "../src/Tokenizer.h"
#include "../src/simplifier/DivisionSimplifier.h"
#include "../src/model/Equation.h"
#include "../src/model/Token.h"
#define FLOAT_DELTA 0.0001

void test_divisionSimplify() {
    Equation *equation = tokenize("x / 4 - 8 = 10 / 16x - 14 + 25 / 5");
    Token *tokens = equation->tokens;
    divisionSimplify(equation);
    TEST_ASSERT_EQUAL(15, equation->len);
    TEST_ASSERT_FALSE(equation->hasDivision);
    TEST_ASSERT_TRUE(equation->hasMultiplication);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.25, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(8, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(10, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.0625, tokens->value);
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
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.2, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 15;
    free(tokens);
    free(equation);
}

void test_divisionSimplify2() {
    Equation *equation = tokenize("x + x = 10 / 10");
    Token *tokens = equation->tokens;
    divisionSimplify(equation);
    TEST_ASSERT_EQUAL(7, equation->len);
    TEST_ASSERT_FALSE(equation->hasDivision);
    TEST_ASSERT_TRUE(equation->hasMultiplication);
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
    TEST_ASSERT_EQUAL(10, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 7;
    free(tokens);
    free(equation);
}

void test_divisionSimplify3() {
    Equation *equation = tokenize("8x / 2 / 2 = 24 / 1.6 / 0.2");
    Token *tokens = equation->tokens;
    divisionSimplify(equation);
    TEST_ASSERT_EQUAL(11, equation->len);
    TEST_ASSERT_FALSE(equation->hasDivision);
    TEST_ASSERT_TRUE(equation->hasMultiplication);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(8, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.5, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.5, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(24, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.625, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(5, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 3;
    free(tokens);
    free(equation);
}

void testDivisionSimplifier_runTests() {
    RUN_TEST(test_divisionSimplify);
    RUN_TEST(test_divisionSimplify2);
    RUN_TEST(test_divisionSimplify3);
}