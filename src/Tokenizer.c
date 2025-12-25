//
// Created by nicholas on 07/09/2025.
//
#include "Tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/TokenType.h"
#include "model/Equation.h"
#include "model/Token.h"

//The maximum number of tokens accepted in the equation, which is one token per character considering an equation written without empty spaces in between tokens
// strlen("x+3-6=2+4*x-1...") <= MAX_TOKENS
#define MAX_TOKENS 255

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

float charToFloat(char c) {
    return (float) (c - '0');
}

/**
    * Extract the tokens from the passed equation
    * @param {char} *equation - string containing the equation to tokenize
    * @return {Equation} *result - pointer to the created Equation struct
    */
Equation* tokenize(const char *equation) {
    const size_t len = strlen(equation);

    if (len > MAX_TOKENS) {
        fprintf(stderr, "%s %lu %s %d\n", "Too long equation. Inserted", len, "characters with maximum", MAX_TOKENS);
        exit(1);
    }

    Equation *result = malloc(sizeof(Equation));
    result->tokens = malloc((MAX_TOKENS + 1) * sizeof(Token));
    result->hasMultiplication = false;
    result->hasDivision = false;
    int tokenCursor = 0;

    for (int i = 0; i < len; i++) {
        switch (equation[i]) {
            case EMPTY:
                break;
            case X:
                result->tokens[tokenCursor] = (Token) { X, 1 };
                if (i < len - 1 && !isDigit(equation[i + 1])) tokenCursor++;
                if (i == len -1) tokenCursor++;
                break;
            case PLUS:
                result->tokens[tokenCursor++] = (Token) { PLUS, 0 };
                break;
            case MINUS:
                result->tokens[tokenCursor++] = (Token) { MINUS, 0 };
                break;
            case TIMES:
                result->tokens[tokenCursor++] = (Token) { TIMES, 0 };
                result->hasMultiplication = true;
                break;
            case DIVIDE:
                result->tokens[tokenCursor++] = (Token) { DIVIDE, 0 };
                result->hasDivision = true;
                break;
            case EQUALS:
                result->tokens[tokenCursor++] = (Token) { EQUALS, 0 };
                break;
            case DOT:
                float decimalValue = 0;
                float decimalDivider = 10;

                while (i < len - 1 && isDigit(equation[i + 1])) {
                    decimalValue += charToFloat(equation[++i]) / decimalDivider;
                    decimalDivider *= 10;
                }

                if (result->tokens[tokenCursor].type != NUMBER) result->tokens[tokenCursor] = (Token) { NUMBER, 0 };
                result->tokens[tokenCursor].value += decimalValue;

                if (i < len - 1 && equation[i + 1] == X) {
                    result->tokens[tokenCursor].type = X;
                    i++;
                }

                tokenCursor++;
                break;
            default:
                if(isDigit(equation[i])) {
                    float value = charToFloat(equation[i]);

                    while(i < len - 1 && isDigit(equation[i + 1]))
                        value = value * 10 + charToFloat(equation[++i]);

                    if (i < len - 1 && equation[i + 1] == DOT) {
                        result->tokens[tokenCursor] = (Token) { NUMBER, value };
                        break;
                    }

                    if (i < len - 1 && equation[i + 1] == X) {
                        result->tokens[tokenCursor].type = X;
                        i++;
                    } else if (result->tokens[tokenCursor].type != X) {
                        result->tokens[tokenCursor].type = NUMBER;
                    }

                    result->tokens[tokenCursor++].value = value;
                } else {
                    free(result->tokens);
                    fprintf(stderr, "%s %c %s\n", "Character", equation[i], "not valid");
                    exit(1);
                }
        }
    }

    result->tokens[tokenCursor] = (Token) { END, 0 };
    result->len = tokenCursor;
    Token *reallocatedTokens = realloc(result->tokens, (tokenCursor + 1) * sizeof(Token));
    if (reallocatedTokens != NULL) result->tokens = reallocatedTokens;
    return result;
}
