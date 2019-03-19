/* Piotr Libera
   Class Monomial
   The object monomial stores its exponent and coefficient
   Method createName() creates its string representation (name)

   Class Polynomial
   The object stores its degree and monomials it consists of.
   Method createName() creates its string representation, based on names it receives
   from Monomial objects.
   Certain operators are overloaded to properly work on polynomials.
*/
#ifndef POLYNOMIAL_CLASSES_H
#define POLYNOMIAL_CLASSES_H

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ios>
#include <limits>
#include <vector>

#define MAX_POLYNOMIAL_DEGREE 3

//For conversion to string:
#define MAX_POLY_NAME_LENGTH MAX_POLYNOMIAL_DEGREE*(MAX_NAME_SIZE+3)
#define MAX_COEFFICIENT_LENGTH 30
#define MAX_NAME_SIZE MAX_COEFFICIENT_LENGTH+4
#define ZERO_ASCII 48

class Monomial{
private:
    int exponent;
    int coefficient;
    ///string representation
    char* name;
    ///seperate address to share with the world:
    char* nameCopy;
    bool nameCreated;

    ///creates the name - a string representation of the monomial, for example 4x^2
    void createName();

public:
    Monomial(int coeff, int exp);
    ~Monomial();

    ///checks if name is updated, returns pointer to nameCopy
    char* getName();

    ///prints the name
    friend std::ostream & operator<< (std::ostream &output, const Monomial &m);

    int getCoefficient();
    //updates coefficient and the name
    void setCoefficient(int coeff);
};

class Polynomial{
private:
    ///Pointers to monomials that create the polynomial, *monomials[0] has exponent 0, *monomials[1] exponent 1 etc.
    Monomial** monomials;
    int degree;
    ///string representation
    char* name;

    /**Generates the string representation, using name variables of monomials.
       Makes the name look more natural by taking care for negative and zero coefficients,
       e.g. "2x^3 - 5x + 4"*/
    void createName();

public:
    Polynomial(int deg/**polynomial degree*/,
               std::vector<int> coefficients/**coefficients[i] is the coefficient of x^i*/);
    ~Polynomial();

    friend std::ostream & operator<< (std::ostream &output, const Polynomial &p);
    bool operator== (Polynomial &p);
    bool operator!= (Polynomial &p);
    bool operator+= (Polynomial &p);
    Polynomial* operator+ (Polynomial &p);
    bool operator-= (Polynomial &p);
    Polynomial* operator- (Polynomial &p);
    bool operator*= (Polynomial &p);
    Polynomial* operator* (Polynomial &p);

    ///returns pointer to monomial with exponent i
    Monomial* getMonomial(int i);

    int getDegree();
};

#endif
