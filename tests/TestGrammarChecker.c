//
// Created by nicholas on 28/11/2025.
//
#include "TestGrammarChecker.h"
#include "../Unity/src/unity.h"
#include "../src/Tokenizer.h"
#include "../src/GrammarChecker.h"
#include "../src/model/GrammarCheckResult.h"

void test_checkGrammarOkEquation() {
    Equation *equation = tokenize("x + 7 = 10 - 9");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_TRUE(result.ok);
}

void test_checkGrammarNoXFound() {
    Equation *equation = tokenize("8 =");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("No x found", result.error, 10);
}

void test_checkGrammarNoEqualFound() {
    Equation *equation = tokenize("18 + 9x");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation must have one equal", result.error, 28);
}

void test_checkGrammarTwoEqualsFound() {
    Equation *equation = tokenize("2x + 4 = 54 =");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation must have one equal", result.error, 28);
}

void test_checkGrammarWrongVariablesOrder() {
    Equation *equation = tokenize("2x 4 = 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Wrong order in between variables/numbers and operators", result.error, 54);
}

void test_checkGrammarWrongOperatorsOrder() {
    Equation *equation = tokenize("2x + - 1 = 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Wrong order in between variables/numbers and operators", result.error, 54);
}

void test_checkGrammarWrongOperatorsOrderWithTimes() {
    Equation *equation = tokenize("2x +* 1 = 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Wrong order in between variables/numbers and operators", result.error, 54);
}

void test_checkGrammarWrongOperatorsOrderWithDivide() {
    Equation *equation = tokenize("2x /- 1 = 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Wrong order in between variables/numbers and operators", result.error, 54);
}

void test_checkGrammarBeginWithTimes() {
    Equation *equation = tokenize("* 2x + 1 = 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't begin with times", result.error, 31);
}

void test_checkGrammarBeginWithDivide() {
    Equation *equation = tokenize("/ 2x + 1 = 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't begin with divide", result.error, 32);
}

void test_checkGrammarEndWithOperator() {
    Equation *equation = tokenize("2x + 1 = 9 + 3 *");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't end with operator", result.error, 32);
}

void test_checkGrammarOperatorBeforeEqualsPlus() {
    Equation *equation = tokenize("2x + 1 += 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't have an operator before equals", result.error, 45);
}

void test_checkGrammarOperatorBeforeEqualsMinus() {
    Equation *equation = tokenize("2x + 1 -= 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't have an operator before equals", result.error, 45);
}

void test_checkGrammarOperatorBeforeEqualsTimes() {
    Equation *equation = tokenize("2x + 1 *= 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't have an operator before equals", result.error, 45);
}

void test_checkGrammarOperatorBeforeEqualsDivide() {
    Equation *equation = tokenize("2x + 1 /= 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't have an operator before equals", result.error, 45);
}

void test_checkGrammarOperatorBeforeEqualsExponentiation() {
    Equation *equation = tokenize("2x + 1 -= 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't have an operator before equals", result.error, 45);
}

void test_checkGrammarTimesAfterEquals() {
    Equation *equation = tokenize("2x + 1 =* 9 + 3");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't have times after equals", result.error, 38);
}

void test_checkGrammarDivideAfterEquals() {
    Equation *equation = tokenize("2x + 1 =/ 9 + 3 ");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't have divide after equals", result.error, 39);
}

void test_checkGrammarExponentiationAfterEquals() {
    Equation *equation = tokenize("x =^ 3 ");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation can't have exponentiation after equals", result.error, 47);
}

void test_checkGrammarWrongFloatingNumberFormat() {
    Equation *equation = tokenize("2x.7 = 3 ");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Wrong order in between variables/numbers and operators", result.error, 54);
}

void test_checkGrammarWrongExponentiationFormat() {
    Equation *equation = tokenize("x ^ 2 + 5^4 = 7.5^3x");
    GrammarCheckResult result = checkGrammar(equation);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Exponentiation format not valid: the power can't be a variable", result.error, 47);
}

void testGrammarChecker_runTests() {
    RUN_TEST(test_checkGrammarOkEquation);
    RUN_TEST(test_checkGrammarNoXFound);
    RUN_TEST(test_checkGrammarNoEqualFound);
    RUN_TEST(test_checkGrammarTwoEqualsFound);
    RUN_TEST(test_checkGrammarWrongVariablesOrder);
    RUN_TEST(test_checkGrammarWrongOperatorsOrder);
    RUN_TEST(test_checkGrammarWrongOperatorsOrderWithTimes);
    RUN_TEST(test_checkGrammarWrongOperatorsOrderWithDivide);
    RUN_TEST(test_checkGrammarBeginWithTimes);
    RUN_TEST(test_checkGrammarBeginWithDivide);
    RUN_TEST(test_checkGrammarEndWithOperator);
    RUN_TEST(test_checkGrammarOperatorBeforeEqualsPlus);
    RUN_TEST(test_checkGrammarOperatorBeforeEqualsMinus);
    RUN_TEST(test_checkGrammarOperatorBeforeEqualsTimes);
    RUN_TEST(test_checkGrammarOperatorBeforeEqualsDivide);
    RUN_TEST(test_checkGrammarOperatorBeforeEqualsExponentiation);
    RUN_TEST(test_checkGrammarTimesAfterEquals);
    RUN_TEST(test_checkGrammarDivideAfterEquals);
    RUN_TEST(test_checkGrammarExponentiationAfterEquals);
    RUN_TEST(test_checkGrammarWrongFloatingNumberFormat);
    RUN_TEST(test_checkGrammarWrongExponentiationFormat);
}