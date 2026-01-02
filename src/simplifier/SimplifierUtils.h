//
// Created by nicholas on 02/01/2026.
//

#ifndef EQUATION_SOLVER_SIMPLIFIERUTILS_H
#define EQUATION_SOLVER_SIMPLIFIERUTILS_H
#include "../model/Equation.h"
#include "../model/Token.h"
#include "../model/TokenType.h"

void simplify(Equation *equation, TokenType target, Token (*solve)(Token*, Token*));

#endif //EQUATION_SOLVER_SIMPLIFIERUTILS_H