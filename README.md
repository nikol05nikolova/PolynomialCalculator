# Polynomial Calculator

## Overview

The Polynomial Calculator is a C++ project designed to perform various operations on polynomials with rational coefficients. The project includes fundamental arithmetic operations, polynomial transformations, and mathematical computations such as finding roots and applying Euclidean algorithms.

## Features  
The calculator supports the following functionalities:   

1. Addition of two polynomials: Computes P(x) + Q(x)  
2. Subtraction of two polynomials: Computes P(x) - Q(x)  
3. Multiplication of two polynomials: Computes P(x) * Q(x)  
4. Division of two polynomials: Computes P(x) / Q(x), where Q(x) ≠ 0 and deg(P) ≥ deg(Q). The program outputs both the quotient and remainder.  
5. Multiplication of a polynomial by a rational number  
6. Evaluation of a polynomial for a given rational number  
7. Finding the greatest common divisor (GCD) of two polynomials using the Euclidean algorithm  
8. Application of Vieta's formulas  
9. Representation of a polynomial in terms of powers of (x + a)  
10. Factorization of polynomials (if possible) and extraction of all rational roots
11. Finding the k-th derivative
12. Implementation Details  

## Technologies
The project is fully written in C++. The following functionalities, helper classes, and libraries were used:

+ Structures
+ std::iostream
+ std::vector
+ std::pair
+ std::cmath

## How to Run
1. Clone the repository and navigate to the project directory.
2. Open the .vcxproj file with Visual Studio to build and run the project.
3. Follow the on-screen instructions to play the game.

## Future Improvements
+ Graphical representation of polynomials.
+ Extended factorization for complex roots.
