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

int charToInt(char c) {
    return c - '0';
}

struct Equation* tokenize(const char *equation) {
    const size_t len = strlen(equation);

    if (len > MAX_TOKENS) {
        fprintf(stderr, "%s %lu %s %d\n", "Too long equation. Inserted", len, "characters with maximum", MAX_TOKENS);
        exit(1);
    }

    struct Token *tokens = malloc((MAX_TOKENS + 1) * sizeof(struct Token));
    int tokenCursor = 0;

    for (int i = 0; i < len; i++) {
        switch (equation[i]) {
            case EMPTY:
                break;
            case X:
                tokens[tokenCursor] = (struct Token) { X, 1 };
                if (i < len - 1 && !isDigit(equation[i + 1])) tokenCursor++;
                if (i == len -1) tokenCursor++;
                break;
            case PLUS:
                tokens[tokenCursor++] = (struct Token) { PLUS, 0 };
                break;
            case MINUS:
                tokens[tokenCursor++] = (struct Token) { MINUS, 0 };
                break;
            case TIMES:
                tokens[tokenCursor++] = (struct Token) { TIMES, 0 };
                break;
            case DIVIDE:
                tokens[tokenCursor++] = (struct Token) { DIVIDE, 0 };
                break;
            case EQUALS:
                tokens[tokenCursor++] = (struct Token) { EQUALS, 0 };
                break;
            default:
                if(isDigit(equation[i])) {
                    int value = charToInt(equation[i]);

                    while(i < len - 1 && isDigit(equation[i + 1]))
                        value = value * 10 + charToInt(equation[++i]);

                    if (i < len - 1 && equation[i + 1] == X) {
                        tokens[tokenCursor].type = X;
                        i++;
                    } else if (tokens[tokenCursor].type != X) {
                        tokens[tokenCursor].type = NUMBER;
                    }

                    tokens[tokenCursor++].value = value;
                } else {
                    free(tokens);
                    fprintf(stderr, "%s %c %s\n", "Character", equation[i], "not valid");
                    exit(1);
                }
        }
    }

    tokens[tokenCursor] = (struct Token) { END, 0 };
    struct Token *reallocatedTokens = realloc(tokens, (tokenCursor + 1) * sizeof(struct Token));
    if (reallocatedTokens != NULL) tokens = reallocatedTokens;
    struct Equation *res = malloc(sizeof(struct Equation));
    res->tokens = tokens;
    res->len = tokenCursor;
    return res;
}
