//
// Created by nicholas on 01/12/2025.
//
#include "MultiplicationSimplifier.h"
#include "SimplifierUtils.h"
#include "../model/Token.h"
#include "../model/TokenType.h"

Token solveMultiplication(Token *firstFactor, Token *secondFactor) {
    Token result;
    result.type = firstFactor->type == X || secondFactor->type == X ? X : NUMBER;
    result.value = firstFactor->value * secondFactor->value;
    return result;
}

/**
    * Solve all the multiplications in the input equation in-place.
    * The input equation has first to be checked with the checkGrammar function in the GrammarChecker module.
    * @param {Equation} *equation - pointer to the equation to simplify
    * @return {void}
    */
void multiplicationSimplify(Equation *equation) {
    simplify(equation, TIMES, solveMultiplication);
    equation->hasMultiplication = false;
}