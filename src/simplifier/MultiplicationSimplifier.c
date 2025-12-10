//
// Created by nicholas on 01/12/2025.
//

#include "MultiplicationSimplifier.h"
#include <stdlib.h>
#include "../model/Equation.h"
#include "../model/Token.h"
#include "../model/TokenType.h"

int countMultiplications(struct Token *tokens) {
    struct Token *cursor = tokens;
    int multiplications = 0;

    while (cursor->type != END) {
        if (cursor->type == TIMES) multiplications++;
        cursor++;
    }

    return multiplications;
}

struct Token solveMultiplication(struct Token firstFactor, struct Token secondFactor) {
    struct Token result;

    if (firstFactor.type == X || secondFactor.type == X)
        result.type = X;
    else
        result.type = NUMBER;

    result.value = firstFactor.value * secondFactor.value;

    return result;
}

struct Equation* multiplicationSimplify(struct Equation *equation) {
    struct Equation *result = malloc(sizeof(struct Equation));
    result->tokens = malloc((equation->len - (2 * countMultiplications(equation->tokens))) * sizeof(struct Token));
    int tokenCursor = 0;

    for (int i = 0; i < equation->len; i++) {
        if (i != equation->len - 1 && equation->tokens[i + 1].type == TIMES) {
            result->tokens[tokenCursor++] = solveMultiplication(equation->tokens[i], equation->tokens[i + 2]);
            i += 2;
        } else {
            result->tokens[tokenCursor++] = equation->tokens[i];
        }
    }

    result->tokens[tokenCursor] = (struct Token) { END, 0 };
    return result;
}