#include "polynomialClasses.h"


void Monomial::createName(){
    if(coefficient < 0)
        name[0] = '-';
    else
        name[0] = ' ';
    int temp = coefficient;
    temp = abs(coefficient);
    int digits=0;
    if(temp == 0){
        digits = 1;
        name[1] = '0';
    }
    else for(int i = 1; i < MAX_COEFFICIENT_LENGTH && temp > 0; ++i){
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
    nameCreated = 1;
}


Monomial::Monomial(int coeff, int exp){
    name = new char[MAX_NAME_SIZE];
    nameCopy = new char[MAX_NAME_SIZE];
    nameCreated = 0;
    coefficient = coeff;
    if(exp < 0 || exp > MAX_POLYNOMIAL_DEGREE){
        coefficient = 0;
        exponent = 0;
        return;
    }
    else{
        exponent = exp;
    }
    createName();
    std::cout<<"Constructor of the Monomial "<<name<<" was called."<<std::endl;
}

Monomial::~Monomial(){
    std::cout<<"Destructor of the Monomial "<<name<<" was called"<<std::endl;
    delete[] name;
    delete[] nameCopy;
}

char* Monomial::getName(){
    if(!nameCreated)
        createName();
    for(int i = 0; i < MAX_NAME_SIZE; ++i){
        nameCopy[i] = name[i];
    }
    return nameCopy;
}

std::ostream & operator<< (std::ostream &output, const Monomial &m){
        return output<<m.name;
    }

int Monomial::getCoefficient(){
    return coefficient;
}


void Polynomial::createName(){
    char* c;
    int counter = 0;
    int j;
    for(int i = degree; i >= 0; --i){
        if(monomials[i]->getCoefficient() == 0)
            continue;
        c = monomials[i]->getName();
        j = 0;
        while(c[j] != 0){
            name[counter] = c[j];
            if(i != degree && name[counter] == '-'){
                name[counter] = ' ';
            }
            j++;
            counter++;
        }
        if(i == 1){
            name[--counter] = 0;
            name[--counter] = 0;
        }
        if(i > 0){
            if(monomials[i-1]->getCoefficient() < 0){
                name[counter++] = ' ';
                name[counter++] = '-';
            }
            else{
                name[counter++] = ' ';
                name[counter++] = '+';
            }
        }
        else{
            name[--counter] = 0;
            name[--counter] = 0;
            name[--counter] = 0;
        }
    }
    while(counter > 0 && (name[counter] == 0 || name[counter] == ' ' ||
        name[counter] == '-' || name[counter] == '+')){
        name[counter] = 0;
        counter--;
    }
}



Polynomial::Polynomial(int deg, std::vector<int> coefficients){
    degree = std::min(MAX_POLYNOMIAL_DEGREE, std::max(0, deg));
    degree = std::min(degree, (int)(coefficients.size()-1));
    monomials = new Monomial*[MAX_POLYNOMIAL_DEGREE+1];
    name = new char[MAX_POLY_NAME_LENGTH];
    for(int i = 0; i <= degree; ++i){
        monomials[i] = new Monomial(coefficients[i], i);
    }
    createName();
    std::cout<<"Constructor of the Polynomial "<<name<<" was called"<<std::endl;;
}

Polynomial::~Polynomial(){
    std::cout<<"Destructor of the Polynomial "<<name<<" was called"<<std::endl;
    for(int i = 0; i <= degree; ++i){
        delete monomials[i];
    }
    delete monomials;
    delete[] name;
}

std::ostream & operator<< (std::ostream &output, const Polynomial &p){
    return output<<p.name;
}

Monomial* Polynomial::getMonomial(int i){
    if(i < 0 || i > degree){
        return NULL;
    }
    return monomials[i];
}

int Polynomial::getDegree(){
    return degree;
}

bool Polynomial::operator== (Polynomial &p){
    if(degree != p.getDegree())
        return false;
    bool result = 1;
    for(int i = 0; i <= p.getDegree(); ++i){
        if(monomials[i]->getCoefficient() != p.getMonomial(i)->getCoefficient())
            result = 0;
    }
    return result;
}

bool Polynomial::operator!= (Polynomial &p){
    if(degree != p.getDegree())
        return true;
    bool result = 0;
    for(int i = 0; i <= p.getDegree(); ++i){
        if(monomials[i]->getCoefficient() != p.getMonomial(i)->getCoefficient())
            result = 1;
    }
    return result;
}
