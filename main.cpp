/* Piotr Libera
  Polynomial calculator
  PROI Project 1

  This code lets to interactively test every required feature of class Polynomial.

  Functions: newPolynomial, deletePolynomial, testPolynomialsIfEqual, polynomialOperation
  communicate with the user, asking for and receiving names of polynomials to perform
  the operation on. After receiving incorrect information they return immidiately
  calling inputError().
  All of these functions perform operations using operators from class Polynomial.
*/

#include "monomial.h"
#include "polynomial.h"

using namespace std;


int testMonomial(int maxn, int maxCoefficient=100, int maxExponent=MAX_POLYNOMIAL_DEGREE+5);
int testPolynomial(int maxn, int maxCoefficient=10);
int calculationTest(int maxn, int maxCoefficient=100);
void performTests();


int main(){
    performTests();
    return 0;
}


void performTests(){
    int monomialErrors = testMonomial(300);
    int polynomialErrors = testPolynomial(300);
    int calcErrors = calculationTest(200, 5);
    calcErrors += calculationTest(200, 10);
    calcErrors += calculationTest(200, 1000);
    cout<<"MONOMIAL ERRORS: "<<monomialErrors<<endl;
    cout<<"POLYNOMIAL ERRORS: "<<polynomialErrors<<endl;
    cout<<"CALCULATION ERRORS: "<<calcErrors<<endl;
}

int calculationTest(int maxn, int maxCoefficient){
    int errcount = 0;
    srand(time(NULL));
    for(int n = 0; n < maxn; ++n){
        int dega = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        int degb = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        vector <int> csa;
        vector <int> csb;
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
            cout<<"eOK "<<a<<" == "<<c<<endl;
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
            cout<<"eOK "<<a<<" != "<<b<<endl;
        if(a==b)
            errcount++;

    }
//cout<<errcount<<endl;

    for(int n = 0; n < maxn; ++n){
        int dega = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        int degb = rand()%(MAX_POLYNOMIAL_DEGREE+1);
        vector <int> csa;
        vector <int> csb;
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
                //cout<<"1"<<i<<endl;
            }
            if(c->getMonomial(i) != a->getMonomial(i) + b->getMonomial(i)){
                testok = 0;
                //cout<<"2  "<<c->getMonomial(i)<<" "<<a->getMonomial(i) + b->getMonomial(i)<<endl;
            }
        }
        if(!testok) errcount++;
        else cout<<"aOK "<<*c<<" = "<<*a<<" + "<<*b<<endl;
        testok = 1;
        *b += *a;
        for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
            if(b->getMonomial(i) != c->getMonomial(i)){
                testok = 0;
                //cout<<b->getMonomial(i)<<"!="<<c->getMonomial(i)<<endl;
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
        vector <int> csa;
        vector <int> csb;
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
                //cout<<"1"<<i<<endl;
            }
            if(c->getMonomial(i) != a->getMonomial(i) - b->getMonomial(i)){
                testok = 0;
                //cout<<"2  "<<c->getMonomial(i)<<" "<<a->getMonomial(i) + b->getMonomial(i)<<endl;
            }
        }
        if(!testok) errcount++;
        else cout<<"sOK "<<*c<<" = "<<*a<<" - "<<*b<<endl;
        testok = 1;
        *a -= *b;
        for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
            if(a->getMonomial(i) != c->getMonomial(i)){
                testok = 0;
                //cout<<a->getMonomial(i)<<"!="<<c->getMonomial(i)<<endl;
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
        vector <int> csa;
        vector <int> csb;
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
                //cout<<"1"<<i<<endl;
            }
        }
        if(!testok) errcount++;
        else cout<<"mOK "<<*c<<" = "<<*a<<" * "<<*b<<endl;
        testok = 1;
        *a *= *b;
        for(int i = 0; i <= MAX_POLYNOMIAL_DEGREE; ++i){
            if(a->getMonomial(i) != c->getMonomial(i)){
                testok = 0;
                //cout<<a->getMonomial(i)<<"!="<<c->getMonomial(i)<<endl;
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
        vector<int>c;
        for(int i = 0; i <= deg; ++i){
            c.push_back(rand()%maxCoefficient-maxCoefficient/2);
        }
        Polynomial a(c);
        cout<<a<<endl;
        int temp = a.getDegree();

        temp = rand()%(MAX_POLYNOMIAL_DEGREE+5);
        a.setMonomial(temp, rand()%maxCoefficient-maxCoefficient/2);
        temp = rand()%(MAX_POLYNOMIAL_DEGREE+5);
        vector<int>d;
        for(int i = 0; i <= temp; ++i){
            d.push_back(rand()%maxCoefficient-maxCoefficient/2);
        }
        a.setMonomials(d);
        int p = rand()%(MAX_POLYNOMIAL_DEGREE+5);
        Monomial m;
        m = a.getMonomial(p);
        p = m.getCoefficient();
        //cout<<a<<endl<<endl;
    }
    return errcount;
}

int testMonomial(int maxn, int maxCoefficient, int maxExponent){
    /*Monomial a(2, 3);
    Monomial b(3, 3);
    cout<<"a+b= "<<a+b<<endl;
    Monomial c;
    c = a+b;
    Monomial d(2, 2);
    cout<<"5x^3*2x^2= "<<c*d<<endl;
    cout<<"2x^3-3x^3= "<<a-b<<endl;*/

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
            cout<<"aOK "<<a<<" = "<<x+z<<" = "<<x<<" + "<<z<<endl;;
        }
        else{
            errcount++;
        }
        a = x-z;
        if(a.getCoefficient() == x.getCoefficient()-z.getCoefficient() && a == x-z){
            cout<<"sOK "<<a<<" = "<<x-z<<" = "<<x<<" - "<<z<<endl;;
        }
        else{
            errcount++;
        }
        a = x*y;
        if(a.getCoefficient() == x.getCoefficient()*y.getCoefficient() &&
           a.getExponent() == x.getExponent()+y.getExponent() && a == x*y){
            cout<<"mOK "<<a<<" = "<<x*y<<" = "<<x<<" * "<<y<<endl;
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
    cout<<"ERRORS: "<<errcount<<endl;
    return errcount;
}
