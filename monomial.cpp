//Piotr Libera
#include "monomial.h"


Monomial::Monomial(int coeff, int exp){
    coefficient = coeff;
    exponent = std::max(exp, 0);
    std::cout<<"Constructor of the Monomial "<<coefficient<<"x^"<<exponent<<" was called."<<std::endl;
}


Monomial::~Monomial(){
    std::cout<<"Destructor of the Monomial "<<coefficient<<"x^"<<exponent<<" was called"<<std::endl;
}



int Monomial::getCoefficient(){
    return coefficient;
}

void Monomial::setCoefficient(int coeff){
    coefficient = coeff;
}

int Monomial::getExponent(){
    return exponent;
}

void Monomial::setExponent(int exp){
    exponent = std::max(exp, 0);
}



std::ostream & operator<< (std::ostream &output, const Monomial &m){
        if(m.exponent == 0) return output<<m.coefficient;
        else if(m.exponent == 1) return output<<m.coefficient<<"x";
        else return output<<m.coefficient<<"x^"<<m.exponent;
}

Monomial Monomial::operator+(Monomial const &m){
    Monomial res;
    if(exponent != m.exponent)
        return res;
    res.exponent = exponent;
    res.coefficient = coefficient+m.coefficient;
    return res;
}


Monomial Monomial::operator-(Monomial const &m){
    Monomial res;
    if(exponent != m.exponent)
        return res;
    res.exponent = exponent;
    res.coefficient = coefficient-m.coefficient;
    return res;
}

Monomial Monomial::operator*(Monomial const &m){
    Monomial res;
    res.exponent = exponent+m.exponent;
    res.coefficient = coefficient*m.coefficient;
    return res;
}

bool Monomial::operator==(Monomial const &m){
    return m.coefficient == coefficient && m.exponent == exponent;
}

bool Monomial::operator!=(Monomial const &m){
    return !(m.coefficient == coefficient && m.exponent == exponent);
}

bool Monomial::operator+=(Monomial const &m){
    if(exponent != m.exponent)
        return false;
    coefficient += m.coefficient;
    return true;
}

bool Monomial::operator-=(Monomial const &m){
    if(exponent != m.exponent)
        return false;
    coefficient -= m.coefficient;
    return true;
}

bool Monomial::operator*=(Monomial const &m){
    exponent += m.exponent;
    coefficient *= m.coefficient;
    return true;
}
