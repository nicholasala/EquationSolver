//
// Created by nicholas on 12/09/2025.
//
#include "Solver.h"
#include <stdio.h>
#include <stdlib.h>
#include "Tokenizer.h"
#include "./model/Token.h"
#include "./model/Equation.h"

float solve(char* text) {
    struct Equation equation = tokenize(text);

    for (int i =0; i < equation.size; i++) {
        printf("{Type: %d, Value: %d}\n", equation.tokens[i].type, equation.tokens[i].value);
    }

    free(equation.tokens);
    return 0;
}