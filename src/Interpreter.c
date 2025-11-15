//
// Created by nicholas on 15/11/2025.
//
#include "Interpreter.h"
#include "model/Equation.h"
#include "model/Node.h"

struct Node interpret(struct Equation equation) {
    struct Node root = {*equation.tokens, nullptr, nullptr};
    return root;
}