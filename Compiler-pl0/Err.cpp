#include <iostream>
using namespace std;

extern void error(int code, int lineNumber) {
    //cout << "error code : " << code << endl;
    cout << "An error has occured. Error code = " << code
        << " at line " << lineNumber << ". Reason : ";
    switch (code) {
        case -1:
            cout << "arrive at END OF FILE unexpectdly.";
            break;
        case 0:
            break;
        case 1:
            cout << "the identifier is too long.";
            break;
        case 2:
            cout << "the number is too large.";
            break;
        case 4:
            cout << "an char must consist of a number or a letter.";
            break;
        case 5:
            cout << "more than one characters in a char.";
            break;
        case 6:
            cout << "invalid string.";
            break;
        case 7:
            cout << "a semicolon is needed.";
            break;
        default:
            break;
    }
    cout << endl;
}
