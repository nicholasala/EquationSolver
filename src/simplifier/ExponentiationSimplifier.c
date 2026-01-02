//
// Created by nicholas on 26/12/2025.
//
#include "ExponentiationSimplifier.h"
#include "SimplifierUtils.h"
#include "../model/Token.h"
#include "../model/TokenType.h"

Token solveExponentiation(Token *factor, Token *power) {
    Token result;
    int powerCount = (int) power->value;
    result.type = factor->type == X ? X : NUMBER;
    result.value = 1;

    while (powerCount > 0) {
        result.value *= factor->value;
        powerCount--;
    }

    return result;
}

/**
    * Solve all the exponentiations in the input equation in-place.
    * The input equation has first to be checked with the checkGrammar function in the GrammarChecker module.
    * @param {Equation} *equation - pointer to the equation to simplify
    * @return {void}
    */
void exponentiationSimplify(Equation *equation) {
    simplify(equation, EXPONENTIATION, solveExponentiation);
    equation->hasExponentiation = false;
}