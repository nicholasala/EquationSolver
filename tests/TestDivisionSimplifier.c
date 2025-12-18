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

void test_divisionSimplify() {
    struct Equation *equation = tokenize("x / 4 - 8 = 10 / 16x - 14 + 25 / 5");
    struct Token *tokens = equation->tokens;
    divisionSimplify(equation);
    TEST_ASSERT_EQUAL(9, equation->len);
    TEST_ASSERT_FALSE(equation->hasDivision);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(0.25, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(8, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(0.625, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(14, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(5, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 9;
    free(tokens);
    free(equation);
}

void test_divisionSimplify2() {
    struct Equation *equation = tokenize("x + x = 10 / 10");
    struct Token *tokens = equation->tokens;
    divisionSimplify(equation);
    TEST_ASSERT_EQUAL(5, equation->len);
    TEST_ASSERT_FALSE(equation->hasDivision);
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
    TEST_ASSERT_EQUAL(1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 5;
    free(tokens);
    free(equation);
}

void testDivisionSimplifier_runTests() {
    RUN_TEST(test_divisionSimplify);
    RUN_TEST(test_divisionSimplify2);
}