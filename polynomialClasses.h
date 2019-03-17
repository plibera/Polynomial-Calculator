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
    //string representation
    char* name;
    //seperate address to share with the world:
    char* nameCopy;
    bool nameCreated;

    void createName();

public:
    Monomial(int coeff, int exp);
    ~Monomial();

    //checks if name is updated, passes pointer to nameCopy
    char* getName();

    friend std::ostream & operator<< (std::ostream &output, const Monomial &m);

    int getCoefficient();
    //updates coefficient and the name
    void setCoefficient(int coeff);
};

class Polynomial{
private:
    Monomial** monomials;
    int degree;
    //string representation
    char* name;

    void createName();

public:
    Polynomial(int deg, std::vector<int> coefficients);
    ~Polynomial();

    //Overloaded operators
    friend std::ostream & operator<< (std::ostream &output, const Polynomial &p);
    bool operator== (Polynomial &p);
    bool operator!= (Polynomial &p);
    bool operator+= (Polynomial &p);
    Polynomial* operator+ (Polynomial &p);
    bool operator-= (Polynomial &p);
    Polynomial* operator- (Polynomial &p);
    bool operator*= (Polynomial &p);
    Polynomial* operator* (Polynomial &p);

    //passes pointer to monomial with exponent i
    Monomial* getMonomial(int i);
    
    int getDegree();
};

#endif
