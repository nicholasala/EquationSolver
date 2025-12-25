//
// Created by nicholas on 10/09/2025.
//

#ifndef EQUATION_SOLVER_TOKENTYPE_H
#define EQUATION_SOLVER_TOKENTYPE_H

typedef enum {
  X = 'x',
  NUMBER = '0',
  PLUS = '+',
  MINUS = '-',
  TIMES = '*',
  DIVIDE = '/',
  EQUALS = '=',
  EMPTY = ' ',
  DOT = '.',
  END = '\n'
} TokenType;

#endif //EQUATION_SOLVER_TOKENTYPE_H