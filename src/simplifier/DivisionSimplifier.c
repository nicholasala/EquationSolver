//
// Created by nicholas on 19/12/2025.
//
#include "DivisionSimplifier.h"
#include <stdlib.h>
#include "../model/Equation.h"
#include "../model/Token.h"
#include "../model/TokenType.h"

struct Token solveDivision(struct Token *firstFactor, struct Token *secondFactor) {
    struct Token result;

    if (firstFactor->type == X || secondFactor->type == X)
        result.type = X;
    else
        result.type = NUMBER;

    result.value = firstFactor->value / secondFactor->value;

    return result;
}

//TODO: find a way to share the duplicate code with MultiplicationSimplifier
/**
    * Solve all the divisions in the input equation in-place.
    * The input equation has first to be checked with the checkGrammar function in the GrammarChecker module.
    * @param {Equation} *equation - pointer to the equation to simplify
    * @return {void}
    */
void divisionSimplify(struct Equation *equation) {
    struct Token *cursor = equation->tokens;
    int tokenCursor = 0;

    while (cursor->type != END) {
        if ((cursor + 1)->type == DIVIDE) {
            equation->tokens[tokenCursor++] = solveDivision(cursor, cursor + 2);
            cursor += 3;
        } else {
            equation->tokens[tokenCursor++] = *cursor;
            cursor++;
        }
    }

    equation->tokens[tokenCursor] = (struct Token) { END, 0 };
    equation->len = tokenCursor;
    equation->hasDivision = false;
    struct Token *reallocatedTokens = realloc(equation->tokens, (tokenCursor + 1) * sizeof(struct Token));
    if (reallocatedTokens != NULL) equation->tokens = reallocatedTokens;
}