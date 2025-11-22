//
// Created by nicholas on 12/09/2025.
//
#include "Solver.h"
#include <stdio.h>
#include <stdlib.h>
#include "Tokenizer.h"
#include "model/Token.h"

//Calculate the value of a given type in the equation
float calculateValue(struct Token* tokens, enum TokenType evaluatedType) {
    float value = 0;
    short signMultiplier = 1;
    short equalMultiplier = 1;
    struct Token *cursor = tokens;

    while (cursor->type != END) {
        if (cursor->type == evaluatedType) value += (float) (cursor->value * signMultiplier * equalMultiplier);

        if (cursor->type == MINUS && (cursor + 1)->type == evaluatedType)
            signMultiplier = -1;
        else
            signMultiplier = 1;

        if (cursor->type == EQUALS) equalMultiplier = -1;

        cursor++;
    }

    return value;
}

float solve(char* text) {
    struct Token *tokens = tokenize(text);
    float xValue = calculateValue(tokens, X);

    if (xValue == 0) {
        fprintf(stderr, "%s\n", "Variable x not found");
        exit(1);
    }

    float result = (- calculateValue(tokens, NUMBER)) / xValue;

    free(tokens);
    return result;
}