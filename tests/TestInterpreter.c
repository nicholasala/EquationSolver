//
// Created by nicholas on 15/11/2025.
//
#include "TestInterpreter.h"
#include "../src/Interpreter.h"
#include "../Unity/src/unity.h"
#include "../src/Tokenizer.h"
#include "../src/model/Equation.h"
#include "../src/model/Node.h"
#include "../src/model/TokenType.h"

void test_interpret() {
    struct Equation equation = tokenize("x + 4 = 8 - 7x");
    struct Node root = interpret(equation);
    TEST_ASSERT_EQUAL(EQUALS, root.token.type);

    TEST_ASSERT_EQUAL(PLUS, root.left->token.type);
    TEST_ASSERT_EQUAL(X, root.left->left->token.type);
    TEST_ASSERT_EQUAL(1, root.left->left->token.value);
    TEST_ASSERT_EQUAL(NUMBER, root.left->right->token.type);
    TEST_ASSERT_EQUAL(4, root.left->right->token.value);

    TEST_ASSERT_EQUAL(MINUS, root.right->token.type);
    TEST_ASSERT_EQUAL(NUMBER, root.right->left->token.type);
    TEST_ASSERT_EQUAL(8, root.right->left->token.value);
    TEST_ASSERT_EQUAL(X, root.right->right->token.type);
    TEST_ASSERT_EQUAL(7, root.right->right->token.type);
}

void testInterpreter_runTests() {
    RUN_TEST(test_interpret);
}