//
// Created by nicholas on 28/11/2025.
//
#include "GrammarChecker.h"
#include "./model/GrammarCheckResult.h"
#include "./model/Token.h"
#include "./model/TokenType.h"
#include "model/Equation.h"

//Check that the variable x exists in the equation
bool xExists(Token *tokens) {
    Token *cursor = tokens;

    while (cursor->type != END) {
        if (cursor->type == X) return true;
        cursor++;
    }

    return false;
}

//Check that the equation has one and only one equal
bool hasOneEqual(Token *tokens) {
    Token *cursor = tokens;
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

bool isVariableOrNumber(TokenType type) {
    return type == X || type == NUMBER;
}

bool isOperator(TokenType type) {
    return type == PLUS || type == MINUS || type == TIMES || type == DIVIDE || type == EXPONENTIATION;
}

bool isEquals(TokenType type) {
    return type == EQUALS;
}

//Check the order in between variables/numbers and operators. Two variables/numbers or two operators can't be one after the other.
// Not valid examples:
//  1. + * 9 = 10
//  2. 4x 7 = 2
bool hasCorrectOrder(Token *tokens) {
    Token *cursor = tokens;

    while (cursor->type != END) {
        if (!isEquals(cursor->type) && !isEquals((cursor + 1)->type)) {
            if (isVariableOrNumber(cursor->type) && isVariableOrNumber((cursor + 1)->type)) return false;
            if (isOperator(cursor->type) && isOperator((cursor + 1)->type)) return false;
        }

        cursor++;
    }

    return true;
}

bool beginsWithTimes(Token *tokens) {
    return tokens->type == TIMES;
}

bool beginsWithDivide(Token *tokens) {
    return tokens->type == DIVIDE;
}

bool endsWithOperator(Equation *equation) {
    return isOperator(equation->tokens[equation->len - 1].type);
}

bool hasOperatorBeforeEquals(Token *tokens) {
    Token *cursor = tokens;
    while (cursor->type != EQUALS) cursor++;
    return cursor != tokens && isOperator((cursor - 1)->type);
}

bool hasTimesAfterEquals(Token *tokens) {
    Token *cursor = tokens;
    while (cursor->type != EQUALS) cursor++;
    return (cursor + 1)->type == TIMES;
}

bool hasDivideAfterEquals(Token *tokens) {
    Token *cursor = tokens;
    while (cursor->type != EQUALS) cursor++;
    return (cursor + 1)->type == DIVIDE;
}

bool hasExponentiationAfterEquals(Token *tokens) {
    Token *cursor = tokens;
    while (cursor->type != EQUALS) cursor++;
    return (cursor + 1)->type == EXPONENTIATION;
}

GrammarCheckResult checkGrammar(Equation *equation) {
    if (!xExists(equation->tokens))
        return (GrammarCheckResult) { false, "No x found" };

    if (!hasOneEqual(equation->tokens))
        return (GrammarCheckResult) { false, "Equation must have one equal" };

    if (!hasCorrectOrder(equation->tokens))
        return (GrammarCheckResult) { false, "Wrong order in between variables/numbers and operators" };

    if (equation->hasMultiplication && beginsWithTimes(equation->tokens))
        return (GrammarCheckResult) { false, "Equation can't begin with times" };

    if (equation->hasDivision && beginsWithDivide(equation->tokens))
        return (GrammarCheckResult) { false, "Equation can't begin with divide" };

    if (endsWithOperator(equation))
        return (GrammarCheckResult) { false, "Equation can't end with operator" };

    if (hasOperatorBeforeEquals(equation->tokens))
        return (GrammarCheckResult) { false, "Equation can't have an operator before equals" };

    if (equation->hasMultiplication && hasTimesAfterEquals(equation->tokens))
        return (GrammarCheckResult) { false, "Equation can't have times after equals" };

    if (equation->hasDivision && hasDivideAfterEquals(equation->tokens))
        return (GrammarCheckResult) { false, "Equation can't have divide after equals" };

    if (equation->hasExponentiation && hasExponentiationAfterEquals(equation->tokens))
        return (GrammarCheckResult) { false, "Equation can't have exponentiation after equals" };

    return (GrammarCheckResult) { true, "" };
}