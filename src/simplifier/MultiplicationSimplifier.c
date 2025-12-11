//
// Created by nicholas on 01/12/2025.
//

#include "MultiplicationSimplifier.h"
#include <stdlib.h>
#include "../model/Equation.h"
#include "../model/Token.h"
#include "../model/TokenType.h"

struct Token solveMultiplication(struct Token *firstFactor, struct Token *secondFactor) {
    struct Token result;

    if (firstFactor->type == X || secondFactor->type == X)
        result.type = X;
    else
        result.type = NUMBER;

    result.value = firstFactor->value * secondFactor->value;

    return result;
}

/**
    * Solve all the multiplications in the input equation in-place.
    * The input equation has first to be checked with the checkGrammar function in the GrammarChecker module.
    * @param {Equation} *equation - pointer to the equation to simplify
    * @return {void}
    */
void multiplicationSimplify(struct Equation *equation) {
    struct Token *cursor = equation->tokens;
    int tokenCursor = 0;

    while (cursor->type != END) {
        if ((cursor + 1)->type == TIMES) {
            equation->tokens[tokenCursor++] = solveMultiplication(cursor, cursor + 2);
            cursor += 3;
        } else {
            equation->tokens[tokenCursor++] = *cursor;
            cursor++;
        }
    }

    equation->tokens[tokenCursor] = (struct Token) { END, 0 };
    equation->len = tokenCursor;
    equation->hasMultiplication = false;
    struct Token *reallocatedTokens = realloc(equation->tokens, (tokenCursor + 1) * sizeof(struct Token));
    if (reallocatedTokens != NULL) equation->tokens = reallocatedTokens;
}