//
// Created by nicholas on 15/11/2025.
//

#ifndef EQUATION_SOLVER_NODE_H
#define EQUATION_SOLVER_NODE_H
#include "Token.h"

struct Node {
    struct Token token;
    struct Node *left;
    struct Node *right;
};

#endif //EQUATION_SOLVER_NODE_H