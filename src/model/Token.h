//
// Created by nicholas on 07/09/2025.
//

#ifndef EQUATION_SOLVER_TOKEN_H
#define EQUATION_SOLVER_TOKEN_H
#include "TokenType.h"

struct Token {
    enum TokenType type;
    int value;
};

#endif //EQUATION_SOLVER_TOKEN_H