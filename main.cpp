#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_POLYNOMIAL_DEGREE 3
#define MAX_COEFFICIENT_LENGTH 30
#define MAX_NAME_SIZE MAX_COEFFICIENT_LENGTH+4
#define ZERO_ASCII 48

using namespace std;

class Monomial{
private:
    int exponent;
    int coefficient;
    char* name;
    char* nameCopy;

public:
    Monomial(int coeff, int exp){
        name = new char[MAX_NAME_SIZE];
        nameCopy = new char[MAX_NAME_SIZE];
        coefficient = coeff;
        if(exp < 0 || exp > MAX_POLYNOMIAL_DEGREE){
            coefficient = 0;
            exponent = 0;
            return;
        }
        else{
            exponent = exp;
        }
        if(coefficient < 0)
            name[0] = '-';
        else
            name[0] = ' ';
        int temp = coeff;
        temp = abs(coeff);
        int digits=0;
        for(int i = 1; i < MAX_COEFFICIENT_LENGTH && temp > 0; ++i){
            name[i] = (temp%10)+ZERO_ASCII;
            temp /= 10;
            digits++;
        }
        char c;
        for(int i = digits; i > digits/2; --i){
            c = name[i];
            name[i] = name[digits-i+1];
            name[digits-i+1] = c;
        }
        name[digits+1] = 'x';
        name[digits+2] = '^';
        name[digits+3] = exponent+ZERO_ASCII;
        std::cout<<"Constructor of the Monomial "<<name<<" was called."<<std::endl;
    }

    ~Monomial(){
        std::cout<<"Destructor of the Monomial "<<name<<" was called"<<std::endl;
        delete[] name;
        delete[] nameCopy;
    }

    char* getName(){
        for(int i = 0; i < MAX_NAME_SIZE; ++i){
            nameCopy[i] = name[i];
        }
        return nameCopy;
    }
};

class Polynomial{
private:
    Monomial** monomials;
    int degree;

public:
    Polynomial(int deg, int* coefficients){
        degree = min(MAX_POLYNOMIAL_DEGREE, max(0, deg));
        monomials = new Monomial*[MAX_POLYNOMIAL_DEGREE+1];
        for(int i = 0; i <= degree; ++i){
            monomials[i] = new Monomial(coefficients[i], i);
        }

        cout<<"Constructor of the Polynomial ";
        for(int i = 0; i <= degree; ++i){
            if(i != 0)
                cout<<" + ";
            cout<<monomials[i]->getName();
        }
        cout<<" was called."<<endl;
    }

    ~Polynomial(){
        cout<<"Destructor of the Polynomial ";
        for(int i = 0; i <= degree; ++i){
            if(i != 0)
                cout<<" + ";
            cout<<monomials[i]->getName();
        }
        cout<<" was called."<<endl;
        for(int i = 0; i <= degree; ++i){
            delete monomials[i];
        }
        delete monomials;
    }
};


int main(){
    Monomial *a = new Monomial(-12345678, 2);
    delete a;
    int tab[] = {123, -234, 345, -456};
    Polynomial *poly = new Polynomial(3, tab);
    delete poly;
    return 0;
}
