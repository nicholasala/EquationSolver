//
// Created by nicholas on 28/11/2025.
//
#include "GrammarChecker.h"
#include "./model/GrammarCheckResult.h"
#include "./model/Token.h"
#include "./model/TokenType.h"

//Check that the variable x exists in the equation
bool xExists(struct Token *tokens) {
    struct Token *cursor = tokens;

    while (cursor->type != END) {
        if (cursor->type == X) return true;
        cursor++;
    }

    return false;
}

//Check that the equation has one and only one equal
bool hasOneEqual(struct Token *tokens) {
    struct Token *cursor = tokens;
    bool hasEquals = false;

    while (cursor->type != END) {
        if (cursor->type == EQUALS) {
            if (hasEquals) return false;
            hasEquals = true;
        }
        cursor++;
    }

    return hasEquals;
}

bool isVariableOrNumber(enum TokenType type) {
    return type == X || type == NUMBER;
}

bool isOperator(enum TokenType type) {
    return type == PLUS || type == MINUS;
}

//Check the order in between variables/numbers and operators
bool hasCorrectOrder(struct Token *tokens) {
    struct Token *cursor = tokens;

    while (cursor->type != END) {
        if (cursor->type != EQUALS && (cursor + 1)->type != EQUALS) {
            if (isVariableOrNumber(cursor->type) && isVariableOrNumber((cursor + 1)->type)) return false;
            if (isOperator(cursor->type) && isOperator((cursor + 1)->type)) return false;
        }

        cursor++;
    }

    return true;
}

struct GrammarCheckResult checkGrammar(struct Token *tokens) {
    if (!xExists(tokens))
        return (struct GrammarCheckResult) { false, "No x found" };

    if (!hasOneEqual(tokens))
        return (struct GrammarCheckResult) { false, "Equation must have one equal" };

    if (!hasCorrectOrder(tokens))
        return (struct GrammarCheckResult) { false, "Wrong order in between variables/numbers and operators" };

    return (struct GrammarCheckResult) { true, "" };
}