//
// Created by nicholas on 05/12/2025.
//

#ifndef EQUATION_SOLVER_EQUATION_H
#define EQUATION_SOLVER_EQUATION_H

/**
    * Equation struct
    * @property {Token} *tokens - the tokens of the equation (with terminator token "END" at the end)
    * @property {int} len - the length of the equation (without considering the terminator token "END")
    * @property {bool} hasMultiplication - equation has contains or not a multiplication
    * @property {bool} hasDivision - equation contains or not a division
    */
struct Equation {
    struct Token *tokens;
    int len;
    bool hasMultiplication;
    bool hasDivision;
};

#endif //EQUATION_SOLVER_EQUATION_H