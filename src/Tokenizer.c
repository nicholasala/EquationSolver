//
// Created by nicholas on 07/09/2025.
//
#include "Tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/TokenType.h"
#include "model/Token.h"
#include "model/Equation.h"
#define MAX_LENGTH 255
#define MAX_TOKENS 50

int countTokens(const char *equation, const size_t len) {
    if (len > MAX_LENGTH) {
        fprintf(stderr, "%s %lu %s %d\n", "Too long equation. Inserted", len, "characters with maximum", MAX_LENGTH);
        exit(1);
    }

    int count = 0;

    for (int i = 0; i < len; i++) {
        switch (equation[i]) {
            case EMPTY:
                break;
            default:
                if (i > 0 && equation[i - 1] != EMPTY && equation[i] != EQUALS) break;
                count++;
        }
    }

    if (count > MAX_TOKENS) {
        fprintf(stderr, "%s %d %s %d\n", "Too many equation tokens. Inserted", count, "tokens with maximum", MAX_TOKENS);
        exit(1);
    }

    return count;
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

int charToInt(char c) {
    return c - '0';
}

struct Equation tokenize(const char *text) {
    const size_t len = strlen(text);
    struct Equation equation;
    equation.size = countTokens(text, len);
    equation.tokens = malloc(equation.size * sizeof(struct Token));
    int tokenCursor = 0;
    bool hasEquals = false;

    for (int i = 0; i < len; i++) {
        switch (text[i]) {
            case EMPTY:
                break;
            case X:
                if(i < len - 1 && isDigit(text[i + 1])) {
                    free(equation.tokens);
                    fprintf(stderr, "%s\n", "Format x(number) not accepted");
                    exit(1);
                }

                equation.tokens[tokenCursor].type = X;
                equation.tokens[tokenCursor].value = 1;
                tokenCursor++;
                break;
            case PLUS:
                equation.tokens[tokenCursor].type = PLUS;
                equation.tokens[tokenCursor].value = 0;
                tokenCursor++;
                break;
            case MINUS:
                equation.tokens[tokenCursor].type = MINUS;
                equation.tokens[tokenCursor].value = 0;
                tokenCursor++;
                break;
            case EQUALS:
                if(hasEquals) {
                    free(equation.tokens);
                    fprintf(stderr, "%s\n", "Two equals are not accepted");
                    exit(1);
                }

                equation.tokens[tokenCursor].type = EQUALS;
                equation.tokens[tokenCursor].value = 0;
                tokenCursor++;
                hasEquals = true;
                break;
            default:
                if(isDigit(text[i])) {
                    equation.tokens[tokenCursor].type = NUMBER;
                    int value = charToInt(text[i]);

                    while(i < len - 1 && isDigit(text[i + 1])) {
                        value *= 10;
                        value += charToInt(text[i + 1]);
                        i++;
                    }

                    if (i < len - 1 && text[i + 1] == X) {
                        equation.tokens[tokenCursor].type = X;
                        i++;
                    }

                    equation.tokens[tokenCursor].value = value;
                    tokenCursor++;
                } else {
                    free(equation.tokens);
                    fprintf(stderr, "%s %c %s\n", "Character", text[i], "not valid");
                    exit(1);
                }
        }
    }

    return equation;
}
