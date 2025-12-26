//
// Created by nicholas on 01/11/2025.
//
#include "TestTokenizer.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../Unity/src/unity.h"
#include "../src/Tokenizer.h"
#include "../src/model/Token.h"
#include "../src/model/TokenType.h"
#define FLOAT_DELTA 0.0001

void test_tokenize() {
    Equation *equation = tokenize("x + 43 - 652 = 10 + 982x - 8x");
    Token *tokens = equation->tokens;
    TEST_ASSERT_EQUAL(11, equation->len);
    TEST_ASSERT_FALSE(equation->hasMultiplication);
    TEST_ASSERT_FALSE(equation->hasDivision);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(43, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(652, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(10, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(982, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(8, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 11;
    free(tokens);
}

void test_tokenizeWithdifferentVariableOrder() {
    Token *tokens = tokenize("x + x8= 62")->tokens;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(8, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(62, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 5;
    free(tokens);
}

void test_tokenizeWithTimes() {
    Equation *equation = tokenize("x * 4 - 8 = 10 * 16x - 5 * 5");
    Token *tokens = equation->tokens;
    TEST_ASSERT_EQUAL(13, equation->len);
    TEST_ASSERT_TRUE(equation->hasMultiplication);
    TEST_ASSERT_FALSE(equation->hasDivision);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(4, tokens->value);
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
    TEST_ASSERT_EQUAL(16, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(5, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(5, tokens->value);
    tokens -= 12;
    free(tokens);
}

void test_tokenizeWithDivide() {
    Equation *equation = tokenize("10x / 2 = 4 / 1 - 5 / 5");
    Token *tokens = equation->tokens;
    TEST_ASSERT_EQUAL(11, equation->len);
    TEST_ASSERT_FALSE(equation->hasMultiplication);
    TEST_ASSERT_TRUE(equation->hasDivision);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(10, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(DIVIDE, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(2, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(4, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(DIVIDE, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(1, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(5, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(DIVIDE, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(5, tokens->value);
    tokens -= 10;
    free(tokens);
}

void test_tokenizeWithExponentiation() {
    Equation *equation = tokenize("10x ^ 2 = 4^3^5");
    Token *tokens = equation->tokens;
    TEST_ASSERT_EQUAL(9, equation->len);
    TEST_ASSERT_TRUE(equation->hasExponentiation);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(10, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EXPONENTIATION, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(2, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(4, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EXPONENTIATION, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(3, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EXPONENTIATION, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(5, tokens->value);
    tokens -= 8;
    free(tokens);
}

void test_tokenizeWithoutSpaces() {
    Token *tokens = tokenize("6x+8*-=4+3x/3")->tokens;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(6, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(8, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(TIMES, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(4, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_EQUAL(3, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(DIVIDE, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_EQUAL(3, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 11;
    free(tokens);
}

void test_tokenizeWithFloatNumber() {
    Equation *equation = tokenize("0.8x + 43.456 - 652.54 = 10.2 + 982.237x - 8.8x");
    Token *tokens = equation->tokens;
    TEST_ASSERT_EQUAL(11, equation->len);
    TEST_ASSERT_FALSE(equation->hasMultiplication);
    TEST_ASSERT_FALSE(equation->hasDivision);
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.8, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 43.456, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 652.54, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 10.2, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(PLUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 982.237, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(MINUS, tokens->type);
    tokens++;
    TEST_ASSERT_EQUAL(X, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 8.8, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(END, tokens->type);
    tokens -= 11;
    free(tokens);
}

void test_tokenizeWithFloatNumber2() {
    Equation *equation = tokenize(".=");
    Token *tokens = equation->tokens;
    TEST_ASSERT_EQUAL(2, equation->len);
    TEST_ASSERT_FALSE(equation->hasMultiplication);
    TEST_ASSERT_FALSE(equation->hasDivision);
    TEST_ASSERT_EQUAL(NUMBER, tokens->type);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.0, tokens->value);
    tokens++;
    TEST_ASSERT_EQUAL(EQUALS, tokens->type);
    tokens -= 1;
    free(tokens);
}

//In order to test the exit with an error code called by the tokenize function, we need to create a separate process so the tests process is not stopped
void test_tokenizeTooLongEquation() {
    pid_t pid = fork();
    if (pid == 0) {
        tokenize("x + 8 + 789 + 435x + 2 + x - 7 - 5 + 76x - 43 = 62 + 5x + 87 + 654x + 43 - 456 + x - 3 - 56 + 7 + 89 + 45 - 3x + 678 - 55 + 8\\"
                 "x + 8 + 789 + 435x + 2 + x - 7 - 5 + 76x - 43 - 62 + 5x + 87 + 654x + 43 - 456 + x - 3 - 56 + 7 + 89 + 45 - 3x + 678 - 55 + 8\\"
                 "x + 8 + 789 + 435x + 2 + x - 7 - 5 + 76x - 43 - 62 + 5x + 87 + 654x + 43 - 456 + x - 3 - 56 + 7 + 89 + 45 - 3x + 678 - 55 + 8");
        exit(0);
    }

    int status;
    wait(&status);
    TEST_ASSERT_EQUAL(1, WEXITSTATUS(status));
}

void test_tokenizeUnexpectedCharacter() {
    pid_t pid = fork();
    if (pid == 0) {
        tokenize("x = 3a");
        exit(0);
    }

    int status;
    wait(&status);
    TEST_ASSERT_EQUAL(1, WEXITSTATUS(status));
}

void testTokenizer_runTests() {
    RUN_TEST(test_tokenize);
    RUN_TEST(test_tokenizeWithdifferentVariableOrder);
    RUN_TEST(test_tokenizeWithTimes);
    RUN_TEST(test_tokenizeWithDivide);
    RUN_TEST(test_tokenizeWithExponentiation);
    RUN_TEST(test_tokenizeWithoutSpaces);
    RUN_TEST(test_tokenizeWithFloatNumber);
    RUN_TEST(test_tokenizeWithFloatNumber2);
    RUN_TEST(test_tokenizeTooLongEquation);
    RUN_TEST(test_tokenizeUnexpectedCharacter);
}
