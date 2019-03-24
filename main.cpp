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
#include "tests.h"
#include <limits>
#include <algorithm>


using namespace std;


/**Prints main menu - commands and list of currently existing arrays*/
void printMenu(Polynomial** polyArray/**Main array of pointers to polynomials A to Z*/,
               bool* createdPolynomial/**array with value 1 for every currently existing polynomial from polyArray*/);

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

void userInterface();
char readCapitalLetter();
bool polynomialExists(int index, bool* createdPolynomial, bool print=1);

const bool generateFile = 0;
const bool runTests = 0;

int main(){
    if(runTests) performTests(300);
    if(generateFile) generateRandomInputToFile(100000, 20, 10);
    else userInterface();
    return 0;
}



void userInterface(){
    Polynomial** polyArray = new Polynomial*[MAX_NUMBER_OF_POLYNOMIALS];
    bool* createdPolynomial = new bool[MAX_NUMBER_OF_POLYNOMIALS];
    for(int i = 0; i < MAX_NUMBER_OF_POLYNOMIALS; ++i) createdPolynomial[i] = 0;

    cout<<"The polynomial calculator. Allowed degree of a polynomial is 0 to "<<MAX_POLYNOMIAL_DEGREE<<endl;
    cout<<"Choose an action:"<<endl;

    char c = 0;
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
    for(int i = 0; i < MAX_NUMBER_OF_POLYNOMIALS; ++i){
        if(createdPolynomial[i])
            delete polyArray[i];
    }
    delete[] polyArray;
    delete[] createdPolynomial;
}


void newPolynomial(Polynomial** polyArray, bool* createdPolynomial){
    char c = readCapitalLetter();
    if(c == -1) return;

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
    reverse(coeffs.begin(), coeffs.end());
    if(createdPolynomial[index])
        polyArray[index]->setMonomials(coeffs);
    else
        polyArray[index] = new Polynomial(coeffs);
    createdPolynomial[index] = 1;
    cout<<"Polynomial "<<c<<" created"<<endl;
}

void deletePolynomial(Polynomial** polyArray, bool* createdPolynomial){
    char c = readCapitalLetter();
    if(c == -1) return;

    int index = c-A_ASCII;
    if(!polynomialExists(index, createdPolynomial))
        return;

    delete polyArray[index];
    createdPolynomial[index] = 0;
    cout<<"Polynomial "<<c<<" deleted"<<endl;
}


void testPolynomialsIfEqual(Polynomial** polyArray, bool* createdPolynomial){
    char a = readCapitalLetter();
    if(a == -1) return;
    char b = readCapitalLetter();
    if(b == -1) return;

    int indexa = a-A_ASCII;
    int indexb = b-A_ASCII;
    if(!polynomialExists(indexa, createdPolynomial)) return;
    if(!polynomialExists(indexb, createdPolynomial)) return;

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
    char a = readCapitalLetter();
    if(a == -1) return;
    char b = readCapitalLetter();
    if(b == -1) return;

    int indexa = a-A_ASCII;
    int indexb = b-A_ASCII;
    if(!polynomialExists(indexa, createdPolynomial)) return;
    if(!polynomialExists(indexb, createdPolynomial)) return;

    cout<<"Choose a polynomial to store the result in (enter a capital letter";
    if(operation == 1)cout<<", not "<<b<<"): ";
    else cout<<"): ";
    char c = readCapitalLetter();
    if(c == -1) return;
    int indexc = c-A_ASCII;

    if(c==a){
        switch(operation){
            case 0:
                //cout<<*polyArray[indexa]<<" += "<<*polyArray[indexb]<<" = ";
                *polyArray[indexa] += *polyArray[indexb];
                cout<<"Result: "<<*polyArray[indexa]<<endl;
                break;
            case 1:
                //cout<<*polyArray[indexa]<<" -= "<<*polyArray[indexb]<<" = ";
                *polyArray[indexa] -= *polyArray[indexb];
                cout<<"Result: "<<*polyArray[indexa]<<endl;
                break;
            case 2:
                //cout<<*polyArray[indexa]<<" *= "<<*polyArray[indexb]<<" = ";
                *polyArray[indexa] *= *polyArray[indexb];
                cout<<"Result: "<<*polyArray[indexa]<<endl;
                break;
        }
    }
    else if(c==b){
        switch(operation){
            case 0:
                //cout<<*polyArray[indexb]<<" += "<<*polyArray[indexa]<<" = ";
                *polyArray[indexb] += *polyArray[indexa];
                cout<<"Result: "<<*polyArray[indexb]<<endl;
                break;
            case 1:
                //cout<<*polyArray[indexb]<<" -= "<<*polyArray[indexa]<<" = ";
                *polyArray[indexb] -= *polyArray[indexa];
                cout<<"Result: "<<*polyArray[indexb]<<endl;
                break;
            case 2:
                //cout<<*polyArray[indexb]<<" *= "<<*polyArray[indexa]<<" = ";
                *polyArray[indexb] *= *polyArray[indexa];
                cout<<"Result: "<<*polyArray[indexb]<<endl;
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

char readCapitalLetter(){
    char a;
    cin>>a;
    if(!isCapitalLetter(a)){
        inputError();
        return -1;
    }
    return a;
}

bool polynomialExists(int index, bool* createdPolynomial, bool print){
    if(!createdPolynomial[index]){
        if(print) cout<<"There is no polynomial "<<(char)(index+A_ASCII)<<endl;
        return 0;
    }
    return 1;
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
