//
// Created by nicholas on 26/12/2025.
//
#include "ExponentiationSimplifier.h"
#include <stdlib.h>

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
//TODO extract code in common with multiplicationSimplify
void exponentiationSimplify(Equation *equation) {
    Token *cursor = equation->tokens;
    int tokenCursor = 0;

    while (cursor->type != END) {
        if ((cursor + 1)->type == EXPONENTIATION) {
            Token result = *cursor;

            do {
                result = solveExponentiation(&result, cursor + 2);
                cursor += 2;
            }while ((cursor + 1)->type == EXPONENTIATION);

            equation->tokens[tokenCursor++] = result;
            cursor++;
        } else {
            equation->tokens[tokenCursor++] = *cursor;
            cursor++;
        }
    }

    equation->tokens[tokenCursor] = (Token) { END, 0 };
    equation->len = tokenCursor;
    equation->hasExponentiation = false;
    Token *reallocatedTokens = realloc(equation->tokens, (tokenCursor + 1) * sizeof(Token));
    if (reallocatedTokens != NULL) equation->tokens = reallocatedTokens;
}