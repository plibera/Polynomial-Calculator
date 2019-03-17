#ifndef POLYNOMIAL_CLASSES_H
#define POLYNOMIAL_CLASSES_H

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ios>
#include <limits>

#define MAX_POLYNOMIAL_DEGREE 3
#define MAX_COEFFICIENT_LENGTH 30
#define MAX_NAME_SIZE MAX_COEFFICIENT_LENGTH+4
#define ZERO_ASCII 48
#define A_ASCII 65
#define MAX_NUMBER_OF_POLYNOMIALS 26
#define MAX_POLY_NAME_LENGTH MAX_POLYNOMIAL_DEGREE*(MAX_NAME_SIZE+3)


class Monomial{
private:
    int exponent;
    int coefficient;
    char* name;
    char* nameCopy;
    bool nameCreated;

    void createName();

public:
    Monomial(int coeff, int exp);
    ~Monomial();
    char* getName();
    friend std::ostream & operator<< (std::ostream &output, const Monomial &m);
    int getCoefficient();
};

class Polynomial{
private:
    Monomial** monomials;
    int degree;
    char* name;

    void createName();

public:
    Polynomial(int deg, int* coefficients);
    ~Polynomial();
    friend std::ostream & operator<< (std::ostream &output, const Polynomial &p);
};

#endif
