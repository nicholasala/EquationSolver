//
// Created by nicholas on 28/11/2025.
//
#include "GrammarChecker.h"
#include "./model/GrammarCheckResult.h"
#include "./model/Token.h"
#include "./model/TokenType.h"
#include "model/Equation.h"

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

bool endsWithOperator(struct Equation *equation) {
    return isOperator(equation->tokens[equation->len - 1].type);
}

bool hasOperatorBeforeEquals(struct Token *tokens) {
    struct Token *cursor = tokens;
    while (cursor->type != EQUALS) cursor++;
    return cursor != tokens && isOperator((cursor - 1)->type);
}

bool hasTimesAfterEquals(struct Token *tokens) {
    struct Token *cursor = tokens;
    while (cursor->type != EQUALS) cursor++;
    return (cursor + 1)->type == TIMES;
}

bool hasDivideAfterEquals(struct Token *tokens) {
    struct Token *cursor = tokens;
    while (cursor->type != EQUALS) cursor++;
    return (cursor + 1)->type == DIVIDE;
}

struct GrammarCheckResult checkGrammar(struct Equation *equation) {
    if (!xExists(equation->tokens))
        return (struct GrammarCheckResult) { false, "No x found" };

    if (!hasOneEqual(equation->tokens))
        return (struct GrammarCheckResult) { false, "Equation must have one equal" };

    if (!hasCorrectOrder(equation->tokens))
        return (struct GrammarCheckResult) { false, "Wrong order in between variables/numbers and operators" };

    if (equation->hasMultiplication && beginsWithTimes(equation->tokens))
        return (struct GrammarCheckResult) { false, "Equation can't begin with times" };

    if (equation->hasDivision && beginsWithDivide(equation->tokens))
        return (struct GrammarCheckResult) { false, "Equation can't begin with divide" };

    if (endsWithOperator(equation))
        return (struct GrammarCheckResult) { false, "Equation can't end with operator" };

    if (hasOperatorBeforeEquals(equation->tokens))
        return (struct GrammarCheckResult) { false, "Equation can't have an operator before equals" };

    if (equation->hasMultiplication && hasTimesAfterEquals(equation->tokens))
        return (struct GrammarCheckResult) { false, "Equation can't have times after equals" };

    if (equation->hasDivision && hasDivideAfterEquals(equation->tokens))
        return (struct GrammarCheckResult) { false, "Equation can't have divide after equals" };

    return (struct GrammarCheckResult) { true, "" };
}