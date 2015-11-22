#include <iomanip>
#include <iostream>
#include "definitions.h"
#include "Parser.h"
using namespace std;

//最右端是终结负号的子程序需要getSym();

datatype expType;
int expData;

extern int startParser() {
    for (int i = 0; i < NumRes; i++) {
        cout << setw(4) << i + 1
            << setw(12) << symbolConst[i] << ' '
            << setw(6) << symbolTable[i] << endl;
    }
    cout << endl << "Amount of lines : " << lineNumber << endl;
    return 0;
}


void semiProgram() {
    if (sym == constsym) {
        constDeclaration();
    }
    if (sym == varsym) {
        varDeclaration();
    }
    if (sym == procsym) {
        procedureDeclaration();
    }
    if (sym == funcsym) {
        functionDeclaration();
    }
    complexStatement();
}

void constDeclaration() {
    if (sym != constsym) {
        error(0, lineNumber);   //error : "const" is needed.
    }
    getSym();
    constDefinition();
    while (sym == comma) {
        getSym();
        constDefinition();
    }
    if (sym != semicolon) {
        error(7, lineNumber);   //error : a semicolon is needed.
    }
    getSym();
}
void constDefinition() {
    if (sym == ident) {
        getSym();
        if (sym == assign) {
            getSym();
            constData();
        }
        else {
            error(0, lineNumber);   //error : an assign symbol is needed.
        }
    }
    else {
        error(0, lineNumber);   //error : an identifier is needed.
    }
}
void constData() {
    bool negative = false;
    
    if (sym == plussym || sym == minussym) {
        if (sym == minussym) {
            negative = true;
        }
        getSym();
    }
    if (sym == num) {
        int n;
        if (negative) {
            n = -lsNum;
        }
        else {
            n = lsNum;
        }
    }
    else if (sym == chr) {
        char n;
        if (negative) {
            n = -lsChar;
        }
        else {
            n = lsChar;
        }
    }
    else {
        error(0, lineNumber);   //error : a number or a char is needed.
    }
    getSym();
}

void varDeclaration() {
    if (sym != varsym) {
        error(0, lineNumber);   //error : "var" is needed.
    }
    getSym();
    varDefinition();
    if (sym != semicolon) {
        error(0, lineNumber);   //error : a semicolon is needed.
    }
    getSym();
    while (sym == ident) {
        getSym();
        varDefinition();
        if (sym != semicolon) {
            error(0, lineNumber);   //error : a semicolon is needed.
        }
        getSym();
    }
    procedureDeclaration();
}
void varDefinition() {
    if (sym == ident) {
        getSym();
        while (sym == comma) {
            getSym();
            if (sym == ident) {

            }
            else {
                error(0, lineNumber);   //error : an identifier is needed.
            }
        }
        if (sym == colon) {
            getSym();
            type();
        }
        else {
            error(0, lineNumber);   //error : a colon is needed.
        }
    }
}

void type() {
    if (sym == intsym || sym == charsym) {
        baseType();
    }
    else if(sym == arraysym) {
        getSym();
        if (sym == lbracket) {
            getSym();
            if (sym == num) {
                getSym();
                if (sym == rbracket) {
                    getSym();
                    if (sym == ofsym) {
                        getSym();
                        baseType();
                    }
                    else {
                        error(0, lineNumber);   //error : the word "of" is needed.
                    }
                }
                else {
                    error(0, lineNumber);   //error : a right bracket is needed.
                }
            }
            else {
                error(0, lineNumber);   //error : a integer variable is needed.
            }
        }
        else {
            error(0, lineNumber);   //error : a left bracket is needed.
        }
    }
    else {
        error(0, lineNumber);   //error : type name is needed.
    }

}
void baseType() {
    if (sym == intsym || sym == charsym) {
        getSym();
    }
    else {
        error(0, lineNumber);   //error : no this type.
    }
    getSym();
}

void procedureDeclaration() {
    procedureHead();
    semiProgram();
}
void procedureHead() {
    if (sym == procsym) {
        getSym();
        if (sym == ident) {
            getSym();
            if (sym == lparen) {
                getSym();
                if (sym == ident) {
                    paramList();
                }
                if (sym == rparen) {
                    getSym();
                    if (sym == semicolon) {
                        getSym();
                    }
                    else {
                        error(0, lineNumber);   //error : a semicolon is needed.
                    }
                }
                else {
                    error(0, lineNumber);   //error : a right parenthsis is needed.
                }
            }
            else {
                error(0, lineNumber);   //error : a left parenthsis is needed.
            }
        }
        else {
            error(0, lineNumber);   //error : an identifier is needed.
        }
    }
    else {
        error(0, lineNumber);   //error : "procedure"is needed.
    }
}

void functionDeclaration() {
    functionHead();
    semiProgram();
}
void functionHead() {
    if (sym == funcsym) {
        getSym();
        if (sym == ident) {
            getSym();
            if (sym == lparen) {
                getSym();
                if (sym == ident) {
                    paramList();
                }
                if (sym == rparen) {
                    getSym();
                    if (sym == colon) {
                        getSym();
                        baseType();
                        if (sym == semicolon) {
                            getSym();
                        }
                        else {
                            error(0, lineNumber);   //error : a semicolon is needed.
                        }
                    }
                    else {
                        error(0, lineNumber);   //error : a colon is needed.
                    }
                }
                else {
                    error(0, lineNumber);   //error : a right parenthsis is needed.
                }
            }
            else {
                error(0, lineNumber);   //error : a left parenthsis is needed.
            }
        }
        else {
            error(0, lineNumber);   //error : an identifier is needed.
        }
    }
    else {
        error(0, lineNumber);   //error : "function"is needed.
    }
}
void paramList() {
    bool varFlag = false;
    if (sym == varsym) {
        varFlag = true;
        getSym();
    }
    if (sym == ident) {
        getSym();
        while (sym == comma) {
            getSym();
            if (sym == ident) {
                ;
            }
            else {
                error(0, lineNumber);   //error : an identifier is needed.
            }
        }
        if (sym == colon) {
            getSym();
            baseType();
            while (sym == semicolon) {
                paramList();
            }
        }
        else {
            error(0, lineNumber);   //error : a colon is needed.
        }
    }
    else {
        error(0, lineNumber);   //error : an identifier is needed.
    }
}

void statement() {
    identtype t;
    switch (sym) {
        case ident:
            t = getIdentType(lsIdent);
            if (t == vartype) {
                assignStatement();
            }
            else if(t == proctype) {
                callProcStatement();
            }
            else {
                error(0, lineNumber);
                //error : unknown statement. Maybe a variable or a procedure is needed.
            }
            break;
        case ifsym:
            ifStatement();
            break;
        case whilesym:
            whileStatement();
            break;
        case forsym:
            forStatement();
            break;
        case beginsym:
            complexStatement();
            break;
        case readsym:
            readStatement();
            break;
        case writesym:
            writeStatement();
            break;
        default:
            error(0, lineNumber);   //error : invalid statement.
            break;
    }
}

void assignStatement() {
    identtype it;
    datatype dt;
    int tmpLv;
    //√<赋值语句>::=<标识符> := <表达式> | <标识符>'['<表达式>']':= <表达式>
    if (sym == ident) {
        it = getIdentType(lsIdent);
        dt = getDataType(lsIdent);
        tmpLv = getDataLevel(lsIdent);
        getSym();
        if (sym == assign) {
            getSym();
            if (it == vartype) {
                assignIt(dt);
            }
            else if (it == functype) {
                //todo : checkLevel
                if (true) {
                    assignIt(dt);
                }
                else {
                    error(0, lineNumber);   //error : can't find the function identifier.
                }
            }
            else {
                error(0, lineNumber);   //error : this variable can't be assigned.
            }
        }
        else if (sym == lbracket) {
            getSym();
            expression();
            int index = (int)expData;
            if (expType != inttype) {
                error(0, lineNumber);   //error : the expression type should be integer.
            }
            if (sym == rbracket) {
                getSym();
                if (sym == assign) {
                    getSym();
                    expression();
                    assignIt(dt, index);
                }
                else {
                    error(0, lineNumber);   //error : an assign symbol is needed.
                }
            }
            else {
                error(0, lineNumber);   //error : a right bracket is needed.
            }
        }
        else {
            error(0, lineNumber);   //error : assign symbol is needed.
        }
    }
    else {
        error(0, lineNumber);   //error : an identifier is needed.
    }
}
void assignIt(datatype dt) {
    switch (dt) {
        case nul:
            error(0, lineNumber);   //type check failed.
            break;
        case chartype:
            if (sym == chr) {
                setData(lsIdent, lsChar);
            }
            else {
                error(0, lineNumber);   //type check failed.
            }
            break;
        case inttype:
            if (sym == num) {
                setData(lsIdent, lsNum);
            }
            else if (sym == chr) {
                setData(lsIdent, (int)lsChar);
            }
            else {
                error(0, lineNumber);   //type check failed.
            }
            break;
        default:
            error(0, lineNumber);   //type check failed.
            break;
    }
}
void assignIt(datatype dt, int index) {
    switch (dt) {
        case nul:
            error(0, lineNumber);   //type check failed.
            break;
        case chartype:
            if (sym == chr) {
                setData(lsIdent, index, lsChar);
            }
            else {
                error(0, lineNumber);   //type check failed.
            }
            break;
        case inttype:
            if (sym == num) {
                setData(lsIdent, index, lsNum);
            }
            else if (sym == chr) {
                setData(lsIdent, (int)lsChar);
            }
            else {
                error(0, lineNumber);   //type check failed.
            }
            break;
        default:
            error(0, lineNumber);   //type check failed.
            break;
    }
}

void callProcStatement() {
    identtype it;
    if (sym == ident) {
        it = getIdentType(lsIdent);
        if (it == proctype) {
            getSym();
            if (sym == lparen) {
                getSym();
                if (sym == ident) {
                    realParamList();
                }
                if (sym == rparen) {
                    getSym();
                }
                else {
                    error(0, lineNumber);   //error : a right parenthsis is needed.
                }
            }
            else {
                error(0, lineNumber);   //error : a left parenthsis is needed.
            }
        }
        else {
            error(0, lineNumber);   //error : the identifier should be a procedure.
        }
    }
    else {
        error(0, lineNumber);   //error : an identifier is needed.
    }
}
void callFuncStatement() {
    identtype it;
    if (sym == ident) {
        it = getIdentType(lsIdent);
        if (it == functype) {
            getSym();
            if (sym == lparen) {
                getSym();
                if (sym == ident) {
                    realParamList();
                }
                if (sym == rparen) {
                    getSym();
                }
                else {
                    error(0, lineNumber);   //error : a right parenthsis is needed.
                }
            }
            else {
                error(0, lineNumber);   //error : a left parenthsis is needed.
            }
        }
        else {
            error(0, lineNumber);   //error : the identifier should be a procedure.
        }
    }
    else {
        error(0, lineNumber);   //error : an identifier is needed.
    }
}
void realParamList() {
    expression();
    while (sym == comma) {
        getSym();
        expression();
    }
}

void ifStatement() {
    getSym();
    condition();
    if (sym == thensym) {
        statement();
        if (sym == elsesym) {
            getSym();
            statement();
        }
    }
    else {
        error(0, lineNumber);   // error : "then" is needed.
    }
}