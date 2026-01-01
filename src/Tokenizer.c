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

    Equation *generatedEquation = malloc(sizeof(Equation));
    generatedEquation->tokens = malloc((MAX_TOKENS + 1) * sizeof(Token));
    generatedEquation->hasMultiplication = false;
    generatedEquation->hasDivision = false;
    generatedEquation->hasExponentiation = false;
    int tokenCursor = 0;

    for (int i = 0; i < len; i++) {
        switch (equation[i]) {
            case EMPTY:
                break;
            case X:
                generatedEquation->tokens[tokenCursor] = (Token) { X, 1 };
                if (i < len - 1 && !isDigit(equation[i + 1])) tokenCursor++;
                if (i == len -1) tokenCursor++;
                break;
            case PLUS:
                generatedEquation->tokens[tokenCursor++] = (Token) { PLUS, 0 };
                break;
            case MINUS:
                generatedEquation->tokens[tokenCursor++] = (Token) { MINUS, 0 };
                break;
            case TIMES:
                generatedEquation->tokens[tokenCursor++] = (Token) { TIMES, 0 };
                generatedEquation->hasMultiplication = true;
                break;
            case DIVIDE:
                generatedEquation->tokens[tokenCursor++] = (Token) { DIVIDE, 0 };
                generatedEquation->hasDivision = true;
                break;
            case EXPONENTIATION:
                generatedEquation->tokens[tokenCursor++] = (Token) { EXPONENTIATION, 0 };
                generatedEquation->hasExponentiation = true;
                break;
            case EQUALS:
                generatedEquation->tokens[tokenCursor++] = (Token) { EQUALS, 0 };
                break;
            case DOT:
                float decimalValue = 0;
                float decimalDivider = 10;

                while (i < len - 1 && isDigit(equation[i + 1])) {
                    decimalValue += charToFloat(equation[++i]) / decimalDivider;
                    decimalDivider *= 10;
                }

                if (generatedEquation->tokens[tokenCursor].type != NUMBER) generatedEquation->tokens[tokenCursor] = (Token) { NUMBER, 0 };
                generatedEquation->tokens[tokenCursor].value += decimalValue;

                if (i < len - 1 && equation[i + 1] == X) {
                    generatedEquation->tokens[tokenCursor].type = X;
                    i++;
                }

                tokenCursor++;
                break;
            default:
                if(isDigit(equation[i])) {
                    float value = charToFloat(equation[i]);
                    int previousCharIndex = i - 1;

                    while(i < len - 1 && isDigit(equation[i + 1]))
                        value = value * 10 + charToFloat(equation[++i]);

                    if (i < len - 1 && equation[i + 1] == DOT) {
                        generatedEquation->tokens[tokenCursor] = (Token) { NUMBER, value };
                        break;
                    }

                    if (i < len - 1 && equation[i + 1] == X) {
                        generatedEquation->tokens[tokenCursor].type = X;
                        i++;
                    } else if (previousCharIndex >= 0 && equation[previousCharIndex] == X) {
                        generatedEquation->tokens[tokenCursor].type = X;
                    } else {
                        generatedEquation->tokens[tokenCursor].type = NUMBER;
                    }

                    generatedEquation->tokens[tokenCursor++].value = value;
                } else {
                    free(generatedEquation->tokens);
                    free(generatedEquation);
                    fprintf(stderr, "%s %c %s\n", "Character", equation[i], "not valid");
                    exit(1);
                }
        }
    }

    generatedEquation->tokens[tokenCursor] = (Token) { END, 0 };
    generatedEquation->len = tokenCursor;
    Token *reallocatedTokens = realloc(generatedEquation->tokens, (tokenCursor + 1) * sizeof(Token));
    if (reallocatedTokens != NULL) generatedEquation->tokens = reallocatedTokens;
    return generatedEquation;
}
