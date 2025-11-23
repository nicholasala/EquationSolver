//
// Created by nicholas on 12/09/2025.
//
#include "Solver.h"
#include <stdio.h>
#include <stdlib.h>
#include "Tokenizer.h"
#include "model/Token.h"

/**
    * Calculate the value of a given type in the equation
    * @param {Token*} tokens - the tokens of the equation
    * @param {TokenType} type - the token type of the wanted value (X, NUMBER, ...)
    */
float calculateValue(struct Token *tokens, enum TokenType type) {
    float value = 0;
    short signMultiplier = 1;
    short equalMultiplier = 1;
    struct Token *cursor = tokens;

    while (cursor->type != END) {
        if (cursor->type == MINUS && (cursor + 1)->type == type) {
            signMultiplier = -1;
            cursor++;
        }

        if (cursor->type == type)
            value += (float) (cursor->value * signMultiplier * equalMultiplier);

        if (cursor->type == EQUALS) equalMultiplier = -1;
        signMultiplier = 1;
        cursor++;
    }

    return value;
}

//Calculate the value of a given type in the equation on the right of the equal
float calculateValueOnRight(struct Token *tokens, enum TokenType type) {
    return - calculateValue(tokens, type);
}

float solve(char *text) {
    struct Token *tokens = tokenize(text);
    float xValue = calculateValue(tokens, X);

    if (xValue == 0) {
        fprintf(stderr, "%s\n", "Variable x not found");
        exit(1);
    }

    float result = calculateValueOnRight(tokens, NUMBER) / xValue;

    free(tokens);
    return result;
}