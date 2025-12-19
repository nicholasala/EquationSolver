# Equation solver
Equation solver developed using Test Driven Development. The solver supports the following operations:

* Addition
* Subtraction
* Multiplication
* Division

### Usage
Compile using cmake:

```
cd equation-solver
mkdir build
cd build
cmake ..
cmake --build . --target equation_solver
```

Execute passing the equation to solve as argument:

```
./equation_solver "x = 10"
```

### Examples
Some examples of equations accepted by the solver:

* Basic example: "x = 10"
* Plus and minus: "12x + 45 = 90 - 18"
* Times: "4x * 2 - 12 = 8 * 7x + 54 * 2"
* Divide: "16 / 4 + 42x / 2 = 82 / 41"
* Floating point numbers: "45.2 * 3x = 0.8 + 56.32 - 3.4x"

### Order of operations
The operations are solved following this order:

1. Divisions (Transformed into multiplications)
2. Multiplications
3. Additions and subtractions

### Future developments

* Exponentiation
* Parentheses