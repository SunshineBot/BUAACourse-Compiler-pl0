//Err.cpp
#include <iostream>
#include "definitions.h"

using namespace std;

extern int getSym();

void skipFor();

extern void error(int code, int lineNumber) {
    //cout << "error code : " << code << endl;
    if (code == -1) {
        if (complexLevel != 0) {
            cout << "An error has occured. Error code = " << code
                << " at line " << lineNumber << ". Reason : ";
            cout << "arrive at END OF FILE unexpectdly.";
            errorAmount++;
        }
        return;
    }
    errorAmount++;
    cout << "An error has occured. Error code = " << code
        << " at line " << lineNumber << ". Reason : ";
    switch (code) {
        case 0:
            cout << "unknown error.";
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
        case 8:
            cout << "\"const\" is needed.";
            while (sym != semicolon)
                getSym();
            getSym();
            break;
        case 9:
            cout << "an assign symbol is needed.";
            break;
        case 10:
            cout << "an identifier is needed.";
            break;
        case 11:
            cout << "a number or a char is needed.";
            break;
        case 12:
            cout << "\"var\" is needed.";
            break;
        case 13:
            cout << "a colon is needed.";
            break;
        case 14:
            cout << "the word \"of\" is needed.";
            break;
        case 15:
            cout << "a right bracket is needed.";
            break;
        case 16:
            cout << "a integer variable is needed.";
            break;
        case 17:
            cout << "a left bracket is needed.";
            break;
        case 18:
            cout << "type name is needed.";
            break;
        case 19:
            cout << "no this type.";
            break;
        case 20:
            cout << "a right parenthsis is needed.";
            break;
        case 21:
            cout << "a left parenthsis is needed.";
            break;
        case 22:
            cout << "\"procedure\"is needed.";
            break;
        case 23:
            cout << "\"function\"is needed.";
            break;
        case 24:
            cout << "unknown statement. Maybe a variable or a procedure is needed.";
            break;
        case 25:
            cout << "invalid statement.";
            break;
        case 26:
            cout << "the expression type should be integer.";
            break;
        case 27:
            cout << "type check failed.";
            break;
        case 28:
            cout << "the identifier should be a procedure.";
            break;
        case 29:
            cout << "\"then\" is needed.";
            break;
        case 30:
            cout << "invalid relational operator.";
            break;
        case 31:
            cout << "\"do\" is needed.";
            break;
        case 32:
            cout << "\"by\" is needed.";
            break;
        case 33:
            cout << "\"to\" is needed.";
            break;
        case 34:
            cout << "\"end\" is needed.";
            break;
        case 35:
            cout << "\"begin\" is needed.";
            break;
        case 36:
            cout << "step can't be zero.";
            break;
        case 37:
            cout << "identifier type is wrong, function or variable is needed.";
            break;
        case 38:
            cout << "out of index bound.";
            break;
        case 39:
            cout << "this variable can't be assigned.";
            break;
        case 40:
            cout << "can't find the function identifier.";
            break;
        case 41:
            cout << "can't find this identifier.";
            break;
        case 42:
            cout << "can't find the correct function name.";
            break;
        case 43:
            cout << "parameter list dispatches.";
            break;
        case 44:
            cout << "invalid expression.";
            break;
        case 45:
            cout << "an assign symbol is needed in a For Statement.";
            break;
        case 46:
            cout << "a number or a char is needed in For Statement.";
            break;
        case 47:
            cout << "a comma or a right parenthsis is needed.";
            break;
        default:
            break;
    }
    cout << endl;
}

void skipFor() {
    int beginFlag = 0;
    while (beginFlag > 0 || sym != semicolon) {
        if (sym == beginsym)
            beginFlag++;
        if (sym == endsym)
            beginFlag--;
        getSym();
    }
    getSym();
}