/*Piotr Libera
*/

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "monomial.h"

#define MAX_POLYNOMIAL_DEGREE 3


class Polynomial{
private:
    int degree;//equals -1 for an empty polynomial
    //every pointer is always allocated
    Monomial* monomials[MAX_POLYNOMIAL_DEGREE+1];

public:
    Polynomial(std::vector<int> coefficients);
    ~Polynomial();

    int getDegree();
    void setMonomials(std::vector<int>coefficients);
    Monomial getMonomial(int i);
    void setMonomial(int i, int coefficient);

    friend std::ostream &operator<< (std::ostream &output, const Polynomial &p);
    bool operator==(Polynomial const &p);
    bool operator!=(Polynomial const &p);
    Polynomial* operator+ (Polynomial const &p);
    bool operator+= (Polynomial const &p);
    Polynomial* operator- (Polynomial const &p);
    bool operator-= (Polynomial const &p);
    Polynomial* operator* (Polynomial const &p);
    bool operator*= (Polynomial const &p);
};

#endif
