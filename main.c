#include <stdio.h>
#include <stdlib.h>
#include "src/Solver.h"

int main(int argc, char *argv[]) {
    if(argc == 1) {
        fprintf(stderr, "%s\n", "Equation not found.\nUsage: ./executable \"equation\"");
        exit(1);
    }

    float result = solve(argv[1]);
    printf("Equation result: %f\n", result);
    return 0;
}