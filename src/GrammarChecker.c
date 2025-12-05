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
    return type == PLUS || type == MINUS || type == TIMES || type == DIVIDE;
}

bool isEquals(enum TokenType type) {
    return type == EQUALS;
}

//Check the order in between variables/numbers and operators. Two variables/numbers or two operators can't be one after the other.
// Not valid examples:
//  1. + * 9 = 10
//  2. 4x 7 = 2
bool hasCorrectOrder(struct Token *tokens) {
    struct Token *cursor = tokens;

    while (cursor->type != END) {
        if (!isEquals(cursor->type) && !isEquals((cursor + 1)->type)) {
            if (isVariableOrNumber(cursor->type) && isVariableOrNumber((cursor + 1)->type)) return false;
            if (isOperator(cursor->type) && isOperator((cursor + 1)->type)) return false;
        }

        cursor++;
    }

    return true;
}

bool beginsWithTimes(struct Token *tokens) {
    return tokens->type == TIMES;
}

bool beginsWithDivide(struct Token *tokens) {
    return tokens->type == DIVIDE;
}

//TODO refactor: having a struct with tokens and a len field could help here in knowing how to increment the cursor in order to reach the last token
bool endsWithOperator(struct Token *tokens) {
    // struct Token *cursor = tokens;
    // while (cursor->type != END) cursor++;
    // return isOperator((cursor - 1)->type);
    return false;
}

struct GrammarCheckResult checkGrammar(struct Token *tokens) {
    if (!xExists(tokens))
        return (struct GrammarCheckResult) { false, "No x found" };

    if (!hasOneEqual(tokens))
        return (struct GrammarCheckResult) { false, "Equation must have one equal" };

    if (!hasCorrectOrder(tokens))
        return (struct GrammarCheckResult) { false, "Wrong order in between variables/numbers and operators" };

    if (beginsWithTimes(tokens))
        return (struct GrammarCheckResult) { false, "Equation can't begin with times" };

    if (beginsWithDivide(tokens))
        return (struct GrammarCheckResult) { false, "Equation can't begin with divide" };

    if (endsWithOperator(tokens))
        return (struct GrammarCheckResult) { false, "Equation can't end with operator" };

    return (struct GrammarCheckResult) { true, "" };
}