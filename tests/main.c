//
// Created by nicholas on 09/11/2025.
//
#include "../Unity/src/unity.h"
#include "TestTokenizer.h"
#include "TestInterpreter.h"

void setUp() { }

void tearDown() { }

int main() {
    UNITY_BEGIN();
    testTokenizer_runTests();
    testInterpreter_runTests();
    UNITY_END();
    return 0;
}