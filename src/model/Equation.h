//
// Created by nicholas on 05/12/2025.
//

#ifndef EQUATION_SOLVER_EQUATION_H
#define EQUATION_SOLVER_EQUATION_H

struct Equation {
    struct Token *tokens;
    int len;
    bool hasMultiplication;
    bool hasDivision;
};

#endif //EQUATION_SOLVER_EQUATION_H