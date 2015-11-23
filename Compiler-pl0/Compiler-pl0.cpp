#include "definitions.h"
#include <iostream>
#include <iomanip>
using namespace std;
extern int start();
extern void initLexer();
extern int getSym();
extern int startParser();

int main() {
    //start();
    initLexer();
    getSym();
    /*while (getSym() != -1);
    cout << endl;
    cout << setw(4) << "num"
        << setw(12) << "type" << ' '
        << setw(6) << "amount" << endl;*/

    startParser();
    //return 0;
}