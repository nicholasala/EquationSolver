//
// Created by nicholas on 15/04/2026.
//
#include "Printer.h"
#include <stdio.h>

void print(Equation *equation) {

    for (int i = 0; i < equation->len; i++) {
        switch (equation->tokens[i].type) {
            case X: equation->tokens[i].value == 1 ? printf("x ") : printf("%gx ", equation->tokens[i].value); break;
            case NUMBER: printf("%g ", equation->tokens[i].value); break;
            case PLUS: printf("+ "); break;
            case MINUS: printf("- "); break;
            case TIMES: printf("* "); break;
            case DIVIDE: printf("/ "); break;
            case EQUALS: printf("= "); break;
            case EXPONENTIATION: printf("^ "); break;
            default: break;
        }
    }

    printf("\n");
}