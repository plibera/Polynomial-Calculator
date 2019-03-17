/* Piotr Libera
  Polynomial calculator
  PROI Project 1
*/
#include "polynomialClasses.h"

using namespace std;

void printMenu(Polynomial** polyArray, bool* createdPolynomial);
void testPrint();
void inputError();
bool isCapitalLetter(char c);
void newPolynomial(Polynomial** polyArray, bool* createdPolynomial);
void deletePolynomial(Polynomial** polyArray, bool* createdPolynomial);
void testPolynomialsIfEqual(Polynomial** polyArray, bool* createdPolynomial);
void polynomialOperation(Polynomial** polyArray, bool* createdPolynomial,
                         int operation);

int main(){
    //testPrint();
    Polynomial** polyArray = new Polynomial*[MAX_NUMBER_OF_POLYNOMIALS];
    bool* createdPolynomial = new bool[MAX_NUMBER_OF_POLYNOMIALS];
    for(int i = 0; i < MAX_NUMBER_OF_POLYNOMIALS; ++i) createdPolynomial[i] = 0;

    cout<<"The polynomial calculator. There are currently no polynomials in memory."<<endl;
    cout<<"Choose an action:"<<endl;

    char c;
    while(c != 'q'){
        printMenu(polyArray, createdPolynomial);
        cin>>c;
        if(!cin){
            inputError();
            continue;
        }
        switch(c){
            case 'n':
                newPolynomial(polyArray, createdPolynomial);
                break;
            case 'd':
                deletePolynomial(polyArray, createdPolynomial);
                break;
            case 'e':
                testPolynomialsIfEqual(polyArray, createdPolynomial);
                break;
            case 'a':
                polynomialOperation(polyArray, createdPolynomial, 0);//add
                break;
            case 's':
                polynomialOperation(polyArray, createdPolynomial, 1);//subtract
                break;
            case 'm':
                polynomialOperation(polyArray, createdPolynomial, 2);//multiply
                break;
            default:
                if(c != 'q')inputError();
        }
    }

    return 0;
}

void newPolynomial(Polynomial** polyArray, bool* createdPolynomial){
    char c;
    cin>>c;
    if(!isCapitalLetter(c)){
        inputError();
        return;
    }
    int index = c-A_ASCII;
    int deg = 0;
    cout<<"Degree of "<<c<<": ";
    cin>>deg;
    if(deg < 0 || deg > MAX_POLYNOMIAL_DEGREE){
        inputError();
        return;
    }
    int temp;
    vector<int> coeffs;
    for(int i = deg; i >= 0; --i){
        cout<<"Coefficient of x^"<<i<<": ";
        cin>>temp;
        if(!cin){
            inputError();
            return;
        }
        coeffs.push_back(temp);
    }
    for(size_t i = 0; i < coeffs.size()/2; ++i){
        temp = coeffs[i];
        coeffs[i] = coeffs[coeffs.size()-i-1];
        coeffs[coeffs.size()-i-1] = temp;
    }
    if(createdPolynomial[index])
        delete polyArray[index];
    polyArray[index] = new Polynomial(deg, coeffs);
    createdPolynomial[index] = 1;
}


void deletePolynomial(Polynomial** polyArray, bool* createdPolynomial){
    char c;
    cin>>c;
    if(!isCapitalLetter(c)){
        inputError();
        return;
    }
    int index = c-A_ASCII;
    if(!createdPolynomial[index]){
        cout<<"There is no polynomial "<<c<<endl;
        return;
    }
    delete polyArray[index];
    createdPolynomial[index] = 0;
    cout<<"Polynomial "<<c<<" deleted"<<endl;
}


void testPolynomialsIfEqual(Polynomial** polyArray, bool* createdPolynomial){
    char a;
    cin>>a;
    if(!isCapitalLetter(a)){
        inputError();
        return;
    }
    char b;
    cin>>b;
    if(!isCapitalLetter(b)){
        inputError();
        return;
    }
    int indexa = a-A_ASCII;
    int indexb = b-A_ASCII;
    if(!createdPolynomial[indexa]){
        cout<<"There is no polynomial "<<a<<endl;
        return;
    }
    if(!createdPolynomial[indexb]){
        cout<<"There is no polynomial "<<b<<endl;
        return;
    }
    if(*polyArray[indexa] == *polyArray[indexb]){
        cout<<"Polynomials "<<a<<" and "<<b<<" are equal"<<endl;
    }
    else if(*polyArray[indexa] != *polyArray[indexb]){
        cout<<"Polynomials "<<a<<" and "<<b<<" are not equal"<<endl;
    }
    else{
        cout<<"Can't decide"<<endl;//shouldn't happen
    }
}

void polynomialOperation(Polynomial** polyArray, bool* createdPolynomial,
                         int operation){
    char a;
    cin>>a;
    if(!isCapitalLetter(a)){
        inputError();
        return;
    }
    char b;
    cin>>b;
    if(!isCapitalLetter(b)){
        inputError();
        return;
    }
    int indexa = a-A_ASCII;
    int indexb = b-A_ASCII;
    if(!createdPolynomial[indexa]){
        cout<<"There is no polynomial "<<a<<endl;
        return;
    }
    if(!createdPolynomial[indexb]){
        cout<<"There is no polynomial "<<b<<endl;
        return;
    }
    cout<<"Choose a polynomial to store the result in (enter a capital letter): ";
    char c;
    cin>>c;
    if(!isCapitalLetter(c)){
        inputError();
        return;
    }
    int indexc = c-A_ASCII;
    //vector<int> temp;
    //Polynomial p(0, temp);
    switch(operation){
        case 0:
            if(c==a){
                *polyArray[indexa] += *polyArray[indexb];
            }
            else if(c==b){
                *polyArray[indexb] += *polyArray[indexa];
            }
            else{
                if(createdPolynomial[indexc]){
                    delete polyArray[indexc];
                }
                polyArray[indexc] = *polyArray[indexa] + *polyArray[indexb];
                createdPolynomial[indexc] = 1;
            }
            break;
    }
}

void printMenu(Polynomial** polyArray, bool* createdPolynomial){
    cout<<endl<<endl;
    cout<<"n X - add new polynomial X, possibly overwriting if X contains data"<<endl;
    cout<<"d X - delete polynomial X"<<endl;
    //cout<<"p X - print polynomial X"<<endl;
    cout<<"e X Y - test if polynomials X and Y are equal"<<endl;
    cout<<"a X Y - add polynomials X and Y"<<endl;
    cout<<"s X Y - subtract Y from X"<<endl;
    cout<<"m X Y - multiply X by Y. To multiply by scalar add it as a 0 degree polynomial"<<endl;
    cout<<"q - quit"<<endl;
    bool noPolynomialIsStored = 1;
    for(int i = 0; i < MAX_NUMBER_OF_POLYNOMIALS; ++i){
        if(createdPolynomial[i])
            noPolynomialIsStored = 0;
    }
    if(noPolynomialIsStored)
        cout<<"There are currently no polynomials in memory"<<endl;
    else{
        cout<<"Polynomials in memory:"<<endl;
        for(int i = 0; i < MAX_NUMBER_OF_POLYNOMIALS; ++i){
            if(createdPolynomial[i]){
                cout<<(char)(i+A_ASCII)<<" "<<*polyArray[i]<<endl;
            }
        }
    }
}

void testPrint(){
    Monomial *a = new Monomial(-12345678, 2);
    cout<<*a<<endl;
    delete a;
    vector<int> tab;
    tab.push_back(-12);
    tab.push_back(5);
    //tab.push_back(0);
    //tab.push_back(-1);
    Polynomial *poly = new Polynomial(3, tab);
    cout<<*poly<<endl;
    delete poly;
}

void inputError(){
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<"Please try again"<<endl;
}

bool isCapitalLetter(char c){
    if(c >= A_ASCII && c <= A_ASCII+MAX_NUMBER_OF_POLYNOMIALS-1)
        return true;
    else
        return false;
}
