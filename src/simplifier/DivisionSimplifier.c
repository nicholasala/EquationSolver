//
// Created by nicholas on 19/12/2025.
//
#include "DivisionSimplifier.h"
#include "../model/Equation.h"
#include "../model/Token.h"
#include "../model/TokenType.h"

/**
    * Solve all the divisions in the input equation in-place transforming it into multiplications
    * The input equation has first to be checked with the checkGrammar function in the GrammarChecker module.
    * @param {Equation} *equation - pointer to the equation to simplify
    * @return {void}
    */
void divisionSimplify(Equation *equation) {
    Token *cursor = equation->tokens;
    equation->hasDivision = false;

    while (cursor->type != END) {
        if (cursor->type == DIVIDE && (cursor + 1)->type != END) {
            cursor->type = TIMES;
            (cursor + 1)->value = 1 / (cursor + 1)->value;
            cursor += 2;
            equation->hasMultiplication = true;
        } else {
            cursor++;
        }
    }
}