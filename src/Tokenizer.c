//
// Created by nicholas on 07/09/2025.
//
#include "Tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/TokenType.h"
#include "model/Token.h"
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

struct Token* tokenize(const char *equation) {
    const size_t len = strlen(equation);
    struct Token *tokens = malloc((countTokens(equation, len) + 1) * sizeof(struct Token));
    int tokenCursor = 0;

    for (int i = 0; i < len; i++) {
        switch (equation[i]) {
            case EMPTY:
                break;
            case X:
                if(i < len - 1 && isDigit(equation[i + 1])) {
                    free(tokens);
                    fprintf(stderr, "%s\n", "Format x(number) not accepted");
                    exit(1);
                }

                tokens[tokenCursor].type = X;
                tokens[tokenCursor].value = 1;
                tokenCursor++;
                break;
            case PLUS:
                tokens[tokenCursor].type = PLUS;
                tokens[tokenCursor].value = 0;
                tokenCursor++;
                break;
            case MINUS:
                tokens[tokenCursor].type = MINUS;
                tokens[tokenCursor].value = 0;
                tokenCursor++;
                break;
            case TIMES:
                tokens[tokenCursor].type = TIMES;
                tokens[tokenCursor].value = 0;
                tokenCursor++;
                break;
            case DIVIDE:
                tokens[tokenCursor].type = DIVIDE;
                tokens[tokenCursor].value = 0;
                tokenCursor++;
                break;
            case EQUALS:
                tokens[tokenCursor].type = EQUALS;
                tokens[tokenCursor].value = 0;
                tokenCursor++;
                break;
            default:
                if(isDigit(equation[i])) {
                    tokens[tokenCursor].type = NUMBER;
                    int value = charToInt(equation[i]);

                    while(i < len - 1 && isDigit(equation[i + 1])) {
                        value *= 10;
                        value += charToInt(equation[i + 1]);
                        i++;
                    }

                    if (i < len - 1 && equation[i + 1] == X) {
                        tokens[tokenCursor].type = X;
                        i++;
                    }

                    tokens[tokenCursor].value = value;
                    tokenCursor++;
                } else {
                    free(tokens);
                    fprintf(stderr, "%s %c %s\n", "Character", equation[i], "not valid");
                    exit(1);
                }
        }
    }

    tokens[tokenCursor].type = END;
    tokens[tokenCursor].value = 0;
    return tokens;
}
