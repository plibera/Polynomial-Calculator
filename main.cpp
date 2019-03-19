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
#include "polynomialClasses.h"

#define A_ASCII 65
#define MAX_NUMBER_OF_POLYNOMIALS 26

using namespace std;


/**Prints main menu - commands and list of currently existing arrays*/
void printMenu(Polynomial** polyArray/**Main array of pointers to polynomials A to Z*/,
               bool* createdPolynomial/**array with value 1 for every currently existing polynomial from polyArray*/);

/**A simple print test, currently not used*/
void testPrint();

/**Informs about an error in input and clears the buffer*/
void inputError();

bool isCapitalLetter(char c);

/**Adds a pointer to a new polynomial to polyArray*/
void newPolynomial(Polynomial** polyArray, bool* createdPolynomial);

/**Deletes a polynomial from polyArray*/
void deletePolynomial(Polynomial** polyArray, bool* createdPolynomial);

/**Test if two polynomials from polyArray are equal*/
void testPolynomialsIfEqual(Polynomial** polyArray, bool* createdPolynomial);

/**This function performs adding, subtracting and multiplying of polynomials.
   It takes two names of polynomials from the user to perform the operation on, then asks the user
   for the name of polynomial to store the result in. If the third name is one of
   first two the operator += (-=, *=) is called, else operator + (-, *) is used.*/
void polynomialOperation(Polynomial** polyArray, bool* createdPolynomial,
                         int operation/**0 - addition, 1 - subtraction, 2 - multiplication*/);

int main(){
    //testPrint();
    Polynomial** polyArray = new Polynomial*[MAX_NUMBER_OF_POLYNOMIALS];
    bool* createdPolynomial = new bool[MAX_NUMBER_OF_POLYNOMIALS];
    for(int i = 0; i < MAX_NUMBER_OF_POLYNOMIALS; ++i) createdPolynomial[i] = 0;

    cout<<"The polynomial calculator. Allowed degree of a polynomial is 0 to 3"<<endl;
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
    cout<<"Polynomial "<<c<<" created"<<endl;
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
    if(c==a){
        switch(operation){
            case 0:
                cout<<*polyArray[indexa]<<" += "<<*polyArray[indexb]<<" = ";
                *polyArray[indexa] += *polyArray[indexb];
                cout<<*polyArray[indexa]<<endl;
                break;
            case 1:
                cout<<*polyArray[indexa]<<" -= "<<*polyArray[indexb]<<" = ";
                *polyArray[indexa] -= *polyArray[indexb];
                cout<<*polyArray[indexa]<<endl;
                break;
            case 2:
                cout<<*polyArray[indexa]<<" *= "<<*polyArray[indexb]<<" = ";
                *polyArray[indexa] *= *polyArray[indexb];
                cout<<*polyArray[indexa]<<endl;
                break;
        }
    }
    else if(c==b){
        switch(operation){
            case 0:
                cout<<*polyArray[indexb]<<" += "<<*polyArray[indexa]<<" = ";
                *polyArray[indexb] += *polyArray[indexa];
                cout<<*polyArray[indexb]<<endl;
                break;
            case 1:
                cout<<*polyArray[indexb]<<" -= "<<*polyArray[indexa]<<" = ";
                *polyArray[indexb] -= *polyArray[indexa];
                cout<<*polyArray[indexb]<<endl;
                break;
            case 2:
                cout<<*polyArray[indexb]<<" *= "<<*polyArray[indexa]<<" = ";
                *polyArray[indexb] *= *polyArray[indexa];
                cout<<*polyArray[indexb]<<endl;
                break;
        }
    }
    else{
        if(createdPolynomial[indexc]){
            delete polyArray[indexc];
        }
        switch(operation){
            case 0:
                polyArray[indexc] = *polyArray[indexa] + *polyArray[indexb];
                cout<<*polyArray[indexa]<<" + "<<*polyArray[indexb]<<" = "<<*polyArray[indexc]<<endl;
                break;
            case 1:
                polyArray[indexc] = *polyArray[indexa] - *polyArray[indexb];
                cout<<*polyArray[indexa]<<" - "<<*polyArray[indexb]<<" = "<<*polyArray[indexc]<<endl;
                break;
            case 2:
                polyArray[indexc] = *polyArray[indexa] * *polyArray[indexb];
                cout<<*polyArray[indexa]<<" * "<<*polyArray[indexb]<<" = "<<*polyArray[indexc]<<endl;
                break;
        }
        createdPolynomial[indexc] = 1;
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
