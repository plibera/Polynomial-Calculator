/** Piotr Libera
*/


#ifndef MONOMIAL_H
#define MONOMIAL_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>


class Monomial{
private:
    int exponent;
    int coefficient;

public:
    Monomial(int coeff=0, int exp=0);
    ~Monomial();

    int getCoefficient();
    void setCoefficient(int coeff);
    int getExponent();
    void setExponent(int exp);

    friend std::ostream & operator<< (std::ostream &output, const Monomial &m);
    Monomial operator+(Monomial const &m);
    Monomial operator-(Monomial const &m);
    Monomial operator*(Monomial const &m);
    bool operator==(Monomial const &m);
    bool operator!=(Monomial const &m);
    bool operator+=(Monomial const &m);
    bool operator-=(Monomial const &m);
    bool operator*=(Monomial const &m);
};

#endif
