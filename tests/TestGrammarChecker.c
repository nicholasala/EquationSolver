//
// Created by nicholas on 28/11/2025.
//
#include "TestGrammarChecker.h"
#include "../Unity/src/unity.h"
#include "../src/Tokenizer.h"
#include "../src/model/Token.h"
#include "../src/GrammarChecker.h"
#include "../src/model/GrammarCheckResult.h"

void test_checkGrammarOkEquation() {
    struct Token *tokens = tokenize("x + 7 = 10 - 9");
    struct GrammarCheckResult result = checkGrammar(tokens);
    TEST_ASSERT_TRUE(result.ok);
}

//No x found
void test_checkGrammarNoXFound() {
    struct Token *tokens = tokenize("8 =");
    struct GrammarCheckResult result = checkGrammar(tokens);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("No x found", result.error, 10);
}

//Equation must have an equal
void test_checkGrammarNoEqualFound() {
    struct Token *tokens = tokenize("18 + 9x");
    struct GrammarCheckResult result = checkGrammar(tokens);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation must have one equal", result.error, 28);
}

//Equation can't have two equals
void test_checkGrammarTwoEqualsFound() {
    struct Token *tokens = tokenize("2x + 4 = 54 =");
    struct GrammarCheckResult result = checkGrammar(tokens);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Equation must have one equal", result.error, 28);
}

//Equation should respect orders of operators and variables/numbers
void test_checkGrammarWrongVariablesOrder() {
    struct Token *tokens = tokenize("2x 4x = 9 + 3");
    struct GrammarCheckResult result = checkGrammar(tokens);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Wrong order in between variables/numbers and operators", result.error, 54);
}

//Equation should respect orders of operators and variables/numbers
void test_checkGrammarWrongOperatorsOrder() {
    struct Token *tokens = tokenize("2x + - 1 = 9 + 3");
    struct GrammarCheckResult result = checkGrammar(tokens);
    TEST_ASSERT_FALSE(result.ok);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Wrong order in between variables/numbers and operators", result.error, 54);
}

void testGrammarChecker_runTests() {
    RUN_TEST(test_checkGrammarOkEquation);
    RUN_TEST(test_checkGrammarNoXFound);
    RUN_TEST(test_checkGrammarNoEqualFound);
    RUN_TEST(test_checkGrammarTwoEqualsFound);
    RUN_TEST(test_checkGrammarWrongVariablesOrder);
    RUN_TEST(test_checkGrammarWrongOperatorsOrder);
}