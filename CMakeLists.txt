cmake_minimum_required(VERSION 4.0)
project(equation_solver C)

set(CMAKE_C_STANDARD 23)

add_executable(equation_solver main.c
        src/Tokenizer.h
        src/model/Token.h
        src/Tokenizer.c
        src/model/TokenType.h
        src/Solver.h
        src/Solver.c
)

add_subdirectory(tests)