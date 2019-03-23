/*Piotr Libera

*/
#include "polynomial.h"


Polynomial::Polynomial(std::vector<int> coefficients){
    degree = std::min((int)coefficients.size()-1, MAX_POLYNOMIAL_DEGREE);

    for(int i = 0; i <= degree; ++i){
        monomials[i] = new Monomial(coefficients[i], i);
    }
    for(int i = degree+1; i <= MAX_POLYNOMIAL_DEGREE; ++i){
        monomials[i] = new Monomial(0, i);
    }
    while(degree >= 0 && monomials[degree]->getCoefficient() == 0){
        degree--;
    }

    std::cout<<"Constructor of polynomial ";
    for(int i = degree; i > 0; --i){
        std::cout<<*monomials[i]<<" + ";
    }
    std::cout<<*monomials[0]<<" was called"<<std::endl;
}

Polynomial::~Polynomial(){
    std::cout<<"Destructor of polynomial ";
    for(int i = degree; i > 0; --i){
        std::cout<<*monomials[i]<<" + ";
    }
    std::cout<<*monomials[0]<<" was called"<<std::endl;
    for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
        delete monomials[i];
    }
}



int Polynomial::getDegree(){
    return degree;
}

void Polynomial::setMonomials(std::vector<int> coefficients){
    degree = std::min((int)coefficients.size()-1, MAX_POLYNOMIAL_DEGREE);

    for(int i = 0; i <= degree; ++i){
        monomials[i]->setCoefficient(coefficients[i]);
    }
    for(int i = degree+1; i <= MAX_POLYNOMIAL_DEGREE; ++i){
        monomials[i]->setCoefficient(0);
    }
    while(degree >= 0 && monomials[degree]->getCoefficient() == 0){
        degree--;
    }
}

Monomial Polynomial::getMonomial(int i){
    if(i <= MAX_POLYNOMIAL_DEGREE && i >= 0){
        Monomial x(monomials[i]->getCoefficient(), monomials[i]->getExponent());
        return x;
    }
    else{
        Monomial x;
        return x;
    }
}

void Polynomial::setMonomial(int i, int coefficient){
    if(i < 0 || i > MAX_POLYNOMIAL_DEGREE)
        return;
    monomials[i]->setCoefficient(coefficient);
    if(i > degree && coefficient != 0)
        degree = i;
    while(degree >= 0 && monomials[degree]->getCoefficient() == 0){
        degree--;
    }
}


std::ostream & operator<< (std::ostream &output, const Polynomial &p){
    if(p.degree == -1){
        output<<*p.monomials[0];
        return output;
    }
    output<<*p.monomials[p.degree];
    for(int i = p.degree-1; i >= 0; --i){
        if(p.monomials[i]->getCoefficient() == 0)
            continue;
        else if(p.monomials[i]->getCoefficient() > 0)
            output<<"+";
        output<<*p.monomials[i];
    }
    return output;
}

bool Polynomial::operator==(Polynomial const &p){
    if(degree != p.degree)
        return false;
    bool result = 1;
    for(int i = degree; i >= 0; --i){
        if(!(*monomials[i] == *p.monomials[i]))
            result = 0;
    }
    return result;
}

bool Polynomial::operator!=(Polynomial const &p){
    if(degree != p.degree)
        return true;
    bool result = 0;
    for(int i = degree; i >= 0; --i){
        if(!(*monomials[i] == *p.monomials[i]))
            result = 1;
    }
    return result;
}

Polynomial* Polynomial::operator+(Polynomial const &p){
    std::vector<int> newcoeffs;
    for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
        Monomial x = *monomials[i] + *p.monomials[i];
        newcoeffs.push_back(x.getCoefficient());
    }
    Polynomial* res = new Polynomial(newcoeffs);
    return res;
}

bool Polynomial::operator+=(Polynomial const &p){
    std::vector<int> newcoeffs;
    for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
        Monomial x = *monomials[i] + *p.monomials[i];
        newcoeffs.push_back(x.getCoefficient());
    }
    setMonomials(newcoeffs);
    return true;
}

Polynomial* Polynomial::operator-(Polynomial const &p){
    std::vector<int> newcoeffs;
    for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
        Monomial x = *monomials[i] - *p.monomials[i];
        newcoeffs.push_back(x.getCoefficient());
    }
    Polynomial* res = new Polynomial(newcoeffs);
    return res;
}

bool Polynomial::operator-=(Polynomial const &p){
    std::vector<int> newcoeffs;
    for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
        Monomial x = *monomials[i] - *p.monomials[i];
        newcoeffs.push_back(x.getCoefficient());
    }
    setMonomials(newcoeffs);
    return true;
}

Polynomial* Polynomial::operator*(Polynomial const &p){
    std::vector<int> newcoeffs;
    for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
        Monomial x(0, i);
        for(int j = 0; j <= i; ++j){
            x += *monomials[j] * *p.monomials[i-j];
        }
        newcoeffs.push_back(x.getCoefficient());
    }
    Polynomial* res = new Polynomial(newcoeffs);
    return res;
}

bool Polynomial::operator*=(Polynomial const &p){
    std::vector<int> newcoeffs;
    for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
        Monomial x(0, i);
        for(int j = 0; j <= i; ++j){
            x += *monomials[j] * *p.monomials[i-j];
        }
        newcoeffs.push_back(x.getCoefficient());
    }
    setMonomials(newcoeffs);
    return true;
}
