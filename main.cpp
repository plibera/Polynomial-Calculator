#include<iostream>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_POLYNOMIAL_DEGREE 3
#define MAX_NAME_SIZE 30
#define ZERO_IN_ASCII 48

using namespace std;

class Monomial{
private:
    int exponent;
    int coefficient;
    char* name;

public:
    Monomial(int coeff, int exp){
        name = new char[MAX_NAME_SIZE+4];
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
        for(int i = 1; i < MAX_NAME_SIZE && temp > 0; ++i){
            name[i] = (temp%10)+ZERO_IN_ASCII;
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
        name[digits+3] = exponent+ZERO_IN_ASCII;
        std::cout<<"Constructor of the Monomial "<<name<<" was called."<<std::endl;
    }

    ~Monomial(){
        std::cout<<"Destructor of the Monomial "<<name<<" was called"<<std::endl;
        delete[] name;
    }
};



int main(){
    Monomial *a = new Monomial(-12345678, 2);
    delete a;
    return 0;
}
