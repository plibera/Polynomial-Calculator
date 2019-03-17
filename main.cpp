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

//bool createPolynomial(Polynomial* poly){

//}

int main(){
    testPrint();
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
                cin>>c;
                if(!isCapitalLetter(c)){
                    inputError();
                    break;
                }
                c -= A_ASCII;
                //if(createPolynomial(polyArray[(int)c]))
                  //  createdPolynomial[(int)c]
                break;

        }
    }

    return 0;
}


void printMenu(Polynomial** polyArray, bool* createdPolynomial){
    cout<<"n X - add new polynomial X, possibly overwriting if X contains data"<<endl;
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
    cout<<endl;
}

void testPrint(){
    Monomial *a = new Monomial(-12345678, 2);
    cout<<*a<<endl;
    delete a;
    int tab[] = {-12, 5, 0, -1};
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
