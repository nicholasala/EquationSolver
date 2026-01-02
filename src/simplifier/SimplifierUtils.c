//
// Created by nicholas on 02/01/2026.
//
#include "SimplifierUtils.h"
#include <stdlib.h>
#include "../model/Equation.h"
#include "../model/Token.h"
#include "../model/TokenType.h"

/**
    * Simplify all the TokenType tokens in the input equation in-place, using the solve function passed.
    * The input equation has first to be checked with the checkGrammar function in the GrammarChecker module.
    * @param {Equation} *equation - pointer to the equation to simplify
    * @param {TokenType} target - the token type to simplify in the equation
    * @param {Token (*solve)(Token*, Token*)} *solve - pointer to the function which accepts two token and return the resulting simplified token
    * @return {void}
    */
void simplify(Equation *equation, TokenType target, Token (*solve)(Token*, Token*)) {
    Token *cursor = equation->tokens;
    int tokenCursor = 0;

    while (cursor->type != END) {
        if ((cursor + 1)->type == target) {
            Token result = *cursor;

            do {
                result = solve(&result, cursor + 2);
                cursor += 2;
            }while ((cursor + 1)->type == target);

            equation->tokens[tokenCursor++] = result;
            cursor++;
        } else {
            equation->tokens[tokenCursor++] = *cursor;
            cursor++;
        }
    }

    equation->tokens[tokenCursor] = (Token) { END, 0 };
    equation->len = tokenCursor;
    Token *reallocatedTokens = realloc(equation->tokens, (equation->len + 1) * sizeof(Token));
    if (reallocatedTokens != NULL) equation->tokens = reallocatedTokens;
}