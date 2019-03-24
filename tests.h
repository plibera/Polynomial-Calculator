/*Piotr Libera
  Functions in this file test classes Monomial and Polynomial by randomly
  using their methods. Number of tests performed in each category
  is specified by maxn
*/

#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "polynomial.h"
#include "monomial.h"

#define MAX_NUMBER_OF_POLYNOMIALS 26
#define A_ASCII 65


int testMonomial(int maxn, int maxCoefficient=100, int maxExponent=MAX_POLYNOMIAL_DEGREE+5);
int testPolynomial(int maxn, int maxCoefficient=10);
int calculationTest(int maxn, int maxCoefficient=100);
void performTests(int maxn = 200);
void generateRandomInputToFile(int maxn, int maxCoefficient, int maxNumberOfPolynomials);



#endif
