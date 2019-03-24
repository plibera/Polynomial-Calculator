#include "tests.h"


void performTests(int maxn){
    int monomialErrors = testMonomial(maxn);
    int polynomialErrors = testPolynomial(maxn);
    int calcErrors = calculationTest(maxn, 5);
    calcErrors += calculationTest(maxn, 10);
    calcErrors += calculationTest(maxn, 1000);
    std::cout<<"MONOMIAL ERRORS: "<<monomialErrors<<std::endl;
    std::cout<<"POLYNOMIAL ERRORS: "<<polynomialErrors<<std::endl;
    std::cout<<"CALCULATION ERRORS: "<<calcErrors<<std::endl;
}

int calculationTest(int maxn, int maxCoefficient){
    int errcount = 0;
    srand(time(NULL));
    for(int n = 0; n < maxn; ++n){
        int dega = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        int degb = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        std::vector <int> csa;
        std::vector <int> csb;
        for(int i = 0; i <= dega; ++i){
            csa.push_back(rand()%maxCoefficient - maxCoefficient/2);
        }
        for(int i = 0; i <= degb; ++i){
            csb.push_back(rand()%maxCoefficient-maxCoefficient/2);
        }

        Polynomial a(csa);
        csa.push_back(0);
        Polynomial c(csa);
        Polynomial b(csb);

        if(!(a==c))
            errcount++;
        else
            std::cout<<"eOK "<<a<<" == "<<c<<std::endl;
        if(a!=c)
            errcount++;
        if(a.getDegree() == b.getDegree()){
            bool different = 0;
            for(int i = 0; i <= a.getDegree(); ++i){
                if(a.getMonomial(i) != b.getMonomial(i))
                    different = 1;
            }
            if(!different){
                int temp = rand()%(MAX_POLYNOMIAL_DEGREE+1);
                Monomial x;
                x = b.getMonomial(temp);
                b.setMonomial(temp, x.getCoefficient()+1);
            }
        }
        if(!(a!=b))
            errcount++;
        else
            std::cout<<"eOK "<<a<<" != "<<b<<std::endl;
        if(a==b)
            errcount++;

    }
//std::cout<<errcount<<std::endl;

    for(int n = 0; n < maxn; ++n){
        int dega = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        int degb = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        std::vector <int> csa;
        std::vector <int> csb;
        for(int i = 0; i <= dega; ++i){
            csa.push_back(rand()%maxCoefficient - maxCoefficient/2);
        }
        for(int i = 0; i <= degb; ++i){
            csb.push_back(rand()%maxCoefficient-maxCoefficient/2);
        }
        Polynomial* a = new Polynomial(csa);
        Polynomial* b = new Polynomial(csb);
        Polynomial* c;
        c = *a + *b;

        bool testok = 1;
        for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
            if(c->getMonomial(i).getCoefficient() != a->getMonomial(i).getCoefficient() +
               b->getMonomial(i).getCoefficient()){
                testok = 0;
                //std::cout<<"1"<<i<<std::endl;
            }
            if(c->getMonomial(i) != a->getMonomial(i) + b->getMonomial(i)){
                testok = 0;
                //std::cout<<"2  "<<c->getMonomial(i)<<" "<<a->getMonomial(i) + b->getMonomial(i)<<std::endl;
            }
        }
        if(!testok) errcount++;
        else std::cout<<"aOK "<<*c<<" = "<<*a<<" + "<<*b<<std::endl;
        testok = 1;
        *b += *a;
        for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
            if(b->getMonomial(i) != c->getMonomial(i)){
                testok = 0;
                //std::cout<<b->getMonomial(i)<<"!="<<c->getMonomial(i)<<std::endl;
            }
        }
        if(!testok) errcount++;
        delete a;
        delete b;
        delete c;
    }

    for(int n = 0; n < maxn; ++n){
        int dega = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        int degb = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        std::vector <int> csa;
        std::vector <int> csb;
        for(int i = 0; i <= dega; ++i){
            csa.push_back(rand()%maxCoefficient - maxCoefficient/2);
        }
        for(int i = 0; i <= degb; ++i){
            csb.push_back(rand()%maxCoefficient-maxCoefficient/2);
        }
        Polynomial* a = new Polynomial(csa);
        Polynomial* b = new Polynomial(csb);
        Polynomial* c;
        c = *a - *b;

        bool testok = 1;
        for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
            if(c->getMonomial(i).getCoefficient() != a->getMonomial(i).getCoefficient() -
               b->getMonomial(i).getCoefficient()){
                testok = 0;
                //std::cout<<"1"<<i<<std::endl;
            }
            if(c->getMonomial(i) != a->getMonomial(i) - b->getMonomial(i)){
                testok = 0;
                //std::cout<<"2  "<<c->getMonomial(i)<<" "<<a->getMonomial(i) + b->getMonomial(i)<<std::endl;
            }
        }
        if(!testok) errcount++;
        else std::cout<<"sOK "<<*c<<" = "<<*a<<" - "<<*b<<std::endl;
        testok = 1;
        *a -= *b;
        for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
            if(a->getMonomial(i) != c->getMonomial(i)){
                testok = 0;
                //std::cout<<a->getMonomial(i)<<"!="<<c->getMonomial(i)<<std::endl;
            }
        }
        if(!testok) errcount++;
        delete a;
        delete b;
        delete c;
    }

    for(int n = 0; n < maxn; ++n){
        int dega = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        int degb = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        std::vector <int> csa;
        std::vector <int> csb;
        for(int i = 0; i <= dega; ++i){
            csa.push_back(rand()%maxCoefficient - maxCoefficient/2);
        }
        for(int i = 0; i <= degb; ++i){
            csb.push_back(rand()%maxCoefficient-maxCoefficient/2);
        }
        Polynomial* a = new Polynomial(csa);
        Polynomial* b = new Polynomial(csb);
        Polynomial* c;
        c = *a * *b;

        bool testok = 1;
        for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
            int sum = 0;
            for(int j = 0; j <= MAX_POLYNOMIAL_DEGREE; ++j){
                sum += a->getMonomial(j).getCoefficient() * b->getMonomial(i-j).getCoefficient();
            }
            if(c->getMonomial(i).getCoefficient() != sum){
                testok = 0;
                //std::cout<<"1"<<i<<std::endl;
            }
        }
        if(!testok) errcount++;
        else std::cout<<"mOK "<<*c<<" = "<<*a<<" * "<<*b<<std::endl;
        testok = 1;
        *a *= *b;
        for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
            if(a->getMonomial(i) != c->getMonomial(i)){
                testok = 0;
                //std::cout<<a->getMonomial(i)<<"!="<<c->getMonomial(i)<<std::endl;
            }
        }
        if(!testok || *a != *c) errcount++;
        delete a;
        delete b;
        delete c;
    }
    return errcount;
}


int testPolynomial(int maxn, int maxCoefficient){
    srand(time(NULL));
    int errcount = 0;
    for(int n = 0; n < maxn; ++n){
        int deg = rand()%(MAX_POLYNOMIAL_DEGREE+3);
        int deg2 = rand()%(MAX_POLYNOMIAL_DEGREE+3);
        std::vector<int>c;
        for(int i = 0; i <= deg; ++i){
            c.push_back(rand()%maxCoefficient-maxCoefficient/2);
        }
        Polynomial a(c);
        std::cout<<a<<std::endl;
        int temp = a.getDegree();

        temp = rand()%(MAX_POLYNOMIAL_DEGREE+5);
        a.setMonomial(temp, rand()%maxCoefficient-maxCoefficient/2);
        temp = rand()%(MAX_POLYNOMIAL_DEGREE+5);
        std::vector<int>d;
        for(int i = 0; i <= temp; ++i){
            d.push_back(rand()%maxCoefficient-maxCoefficient/2);
        }
        a.setMonomials(d);
        int p = rand()%(MAX_POLYNOMIAL_DEGREE+5);
        Monomial m;
        m = a.getMonomial(p);
        p = m.getCoefficient();
        //std::cout<<a<<std::endl<<std::endl;
    }
    return errcount;
}

int testMonomial(int maxn, int maxCoefficient, int maxExponent){
    /*Monomial a(2, 3);
    Monomial b(3, 3);
    std::cout<<"a+b= "<<a+b<<std::endl;
    Monomial c;
    c = a+b;
    Monomial d(2, 2);
    std::cout<<"5x^3*2x^2= "<<c*d<<std::endl;
    std::cout<<"2x^3-3x^3= "<<a-b<<std::endl;*/

    srand(time(NULL));
    int errcount = 0;

    for(int n = 0; n < maxn; ++n){
        int xc = rand()%maxCoefficient - maxCoefficient/2;
        int xe = rand()%maxExponent-2;
        int yc = rand()%maxCoefficient - maxCoefficient/2;
        int ye = rand()%maxExponent-2;
        int zc = rand()%maxCoefficient - maxCoefficient/2;
        Monomial x(xc, xe);
        Monomial y(yc, ye);
        Monomial z;
        z.setExponent(xe);
        z.setCoefficient(zc);
        Monomial a;
        a = x + z;
        if(a.getCoefficient() == x.getCoefficient()+z.getCoefficient() && a == x+z){
            std::cout<<"aOK "<<a<<" = "<<x+z<<" = "<<x<<" + "<<z<<std::endl;;
        }
        else{
            errcount++;
        }
        a = x-z;
        if(a.getCoefficient() == x.getCoefficient()-z.getCoefficient() && a == x-z){
            std::cout<<"sOK "<<a<<" = "<<x-z<<" = "<<x<<" - "<<z<<std::endl;;
        }
        else{
            errcount++;
        }
        a = x*y;
        if(a.getCoefficient() == x.getCoefficient()*y.getCoefficient() &&
           a.getExponent() == x.getExponent()+y.getExponent() && a == x*y){
            std::cout<<"mOK "<<a<<" = "<<x*y<<" = "<<x<<" * "<<y<<std::endl;
        }
        else{
            errcount++;
        }
    }
    for(int i = 0; i < maxn; ++i){
        int exp = rand()%maxExponent-2;
        Monomial a(rand()%maxCoefficient-maxCoefficient/2, exp);
        Monomial b(rand()%maxCoefficient-maxCoefficient/2, exp);
        int ac = a.getCoefficient();
        int bc = b.getCoefficient();
        a += b;
        if(a.getCoefficient() != ac+bc){
            errcount++;
        }
        Monomial c(rand()%maxCoefficient-maxCoefficient/2, rand()%maxExponent-2);
        c += b;
    }
    for(int i = 0; i < maxn; ++i){
        int exp = rand()%maxExponent-2;
        Monomial a(rand()%maxCoefficient-maxCoefficient/2, exp);
        Monomial b(rand()%maxCoefficient-maxCoefficient/2, exp);
        int ac = a.getCoefficient();
        int bc = b.getCoefficient();
        a -= b;
        if(a.getCoefficient() != ac-bc){
            errcount++;
        }
        Monomial c(rand()%maxCoefficient-maxCoefficient/2, rand()%maxExponent-2);
        c -= b;
    }
    for(int i = 0; i < maxn; ++i){
      Monomial a(rand()%maxCoefficient-maxCoefficient/2, rand()%maxExponent-2);
      Monomial b(rand()%maxCoefficient-maxCoefficient/2, rand()%maxExponent-2);
      int ac = a.getCoefficient();
      int bc = b.getCoefficient();
      int ae = a.getExponent();
      int be = b.getExponent();
      a *= b;
      if(a.getCoefficient() != ac*bc || a.getExponent() != ae+be){
          errcount++;
      }
    }
    std::cout<<"ERRORS: "<<errcount<<std::endl;
    return errcount;
}


void generateRandomInputToFile(int maxn, int maxCoefficient, int numberOfPolynomials){
    srand(time(NULL));
    int action = 0;
    int degree = 0;
    std::fstream file;
    file.open("testfile", std::fstream::out);
    for(int n = 0; n < maxn; ++n){
        action = rand()%6;
        if(n < 2*numberOfPolynomials) action = 0;
        switch(action){
            case 0:
                file<<'n'<<(char)(rand()%numberOfPolynomials+A_ASCII)<<std::endl;
                degree = rand()%(MAX_POLYNOMIAL_DEGREE+1);
                file<<degree<<std::endl;
                for(int i = 0; i <= degree; ++i){
                    file<<rand()%maxCoefficient-maxCoefficient/2<<std::endl;
                }
                break;
            case 1:
                file<<'d'<<(char)(rand()%numberOfPolynomials+A_ASCII)<<std::endl;
                break;
            case 2:
                file<<'e'<<(char)(rand()%numberOfPolynomials+A_ASCII)<<(char)(rand()%numberOfPolynomials+A_ASCII)<<std::endl;
                break;
            case 3:
                file<<'a'<<(char)(rand()%numberOfPolynomials+A_ASCII)<<(char)(rand()%numberOfPolynomials+A_ASCII)<<(char)(rand()%numberOfPolynomials+A_ASCII)<<std::endl;
                break;
            case 4:
                file<<'s'<<(char)(rand()%numberOfPolynomials+A_ASCII)<<(char)(rand()%numberOfPolynomials+A_ASCII)<<(char)(rand()%numberOfPolynomials+A_ASCII)<<std::endl;
                break;
            case 5:
                file<<'m'<<(char)(rand()%numberOfPolynomials+A_ASCII)<<(char)(rand()%numberOfPolynomials+A_ASCII)<<(char)(rand()%numberOfPolynomials+A_ASCII)<<std::endl;
                break;
        }
    }
    file<<'q'<<std::endl;
}
