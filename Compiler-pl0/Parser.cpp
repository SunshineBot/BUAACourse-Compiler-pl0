#include <iomanip>
#include <iostream>
#include "definitions.h"
#include "Parser.h"
using namespace std;

//最右端是终结负号的子程序需要getSym();

datatype expType;
int expData;
char name[MaxRes];

int numOfBlank = 0;

extern int startParser() {
    semiProgram();
    return 0;
}


void semiProgram() {
    cout << setw(numOfBlank++*4) << "" << "Into a semi-Program: " << endl;
    if (sym == constsym) {
        constDeclaration();
    }
    if (sym == varsym) {
        varDeclaration();
    }
    while (sym == procsym || sym == funcsym) {
        if (sym == procsym) {
            procedureDeclaration();
        }
        if (sym == funcsym) {
            functionDeclaration();
        }
    }
    /*cout << setw(numOfBlank++ * 4)<<"";*/
    complexStatement();
    cout << setw(--numOfBlank * 4) << "" << "Semi-Program finished." << endl;
}

void constDeclaration() {
    cout << setw(numOfBlank++*4) << "" << "Const Declaration started." << endl;
    if (sym != constsym) {
        error(8, lineNumber);   //error : "const" is needed.
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
    cout << setw(--numOfBlank * 4) << "" << "Const Declaration finished." << endl << endl;
}
void constDefinition() {
    cout << setw(numOfBlank++ * 4) << "" << "Const Definition started." << endl;
    if (sym == ident) {
        getSym();
        if (sym == eql) {
            getSym();
            constData();
        }
        else {
            error(9, lineNumber);   //error : an assign symbol is needed.
        }
    }
    else {
        error(10, lineNumber);   //error : an identifier is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "Const Definition finished." << endl;
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
        error(11, lineNumber);   //error : a number or a char is needed.
    }
    getSym();
    cout << setw(numOfBlank * 4) << "" << "This is data of const type." << endl;
}

void varDeclaration() {
    cout << setw(numOfBlank++ * 4) << "" << "Variable Declaration started." << endl;
    if (sym != varsym) {
        error(12, lineNumber);   //error : "var" is needed.
    }
    getSym();
    varDefinition();
    if (sym != semicolon) {
        error(7, lineNumber);   //error : a semicolon is needed.
    }
    getSym();
    while (sym == ident) {
        //getSym();
        varDefinition();
        if (sym != semicolon) {
            error(7, lineNumber);   //error : a semicolon is needed.
        }
        getSym();
    }
    //procedureDeclaration();
    cout << setw(--numOfBlank * 4) << "" << "Variable Declaration finished." << endl << endl;
}
void varDefinition() {
    cout << setw(numOfBlank++ * 4) << "" << "Variable Definition started." << endl;
    if (sym == ident) {
        getSym();
        while (sym == comma) {
            getSym();
            if (sym == ident) {

                getSym();
            }
            else {
                error(10, lineNumber);   //error : an identifier is needed.
            }
        }
        if (sym == colon) {
            getSym();
            type();
        }
        else {
            error(13, lineNumber);   //error : a colon is needed.
        }
    }
    cout << setw(--numOfBlank * 4) << "" << "Variable Definition finished." << endl;
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
                        error(14, lineNumber);   //error : the word "of" is needed.
                    }
                }
                else {
                    error(15, lineNumber);   //error : a right bracket is needed.
                }
            }
            else {
                error(16, lineNumber);   //error : a integer variable is needed.
            }
        }
        else {
            error(17, lineNumber);   //error : a left bracket is needed.
        }
    }
    else {
        error(18, lineNumber);   //error : type name is needed.
    }
    cout << setw(numOfBlank * 4) << "" << "a type reserved word." << endl;
}
void baseType() {
    if (sym == intsym || sym == charsym) {
        getSym();
    }
    else {
        error(19, lineNumber);   //error : no this type.
    }
    //getSym();
    cout << setw(numOfBlank * 4) << "" << "a base type reserved word." << endl;
}

void procedureDeclaration() {
    cout << setw(numOfBlank++ * 4) << "" << "Procedure Declaration started." << endl;
    procedureHead();
    semiProgram();
    if (sym == semicolon) {
        getSym();
    }
    else {
        error(7, lineNumber);   //error : a semicolon is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "Procedure Declaration finished." << endl;
}
void procedureHead() {
    cout << setw(numOfBlank++ * 4) << "" << "Procedure Head started." << endl;
    if (sym == procsym) {
        getSym();
        if (sym == ident) {
            cout << setw(numOfBlank * 4) << "" << "Procedure Name : " << lsIdent << endl;
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
                        error(7, lineNumber);   //error : a semicolon is needed.
                    }
                }
                else {
                    error(20, lineNumber);   //error : a right parenthsis is needed.
                }
            }
            else {
                error(21, lineNumber);   //error : a left parenthsis is needed.
            }
        }
        else {
            error(10, lineNumber);   //error : an identifier is needed.
        }
    }
    else {
        error(22, lineNumber);   //error : "procedure"is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "Procedure Head finished." << endl;
}

void functionDeclaration() {
    cout << setw(numOfBlank++ * 4) << "" << "Function Declaration started." << endl;
    functionHead();
    semiProgram();
    if (sym == semicolon) {
        getSym();
    }
    else {
        error(7, lineNumber);   //error : a semicolon is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "Function Declaration finished." << endl;
}
void functionHead() {
    cout << setw(numOfBlank++ * 4) << "" << "Function Head started." << endl;
    if (sym == funcsym) {
        getSym();
        if (sym == ident) {
            cout << setw(numOfBlank * 4) << "" << "Function Name : " << lsIdent << endl;
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
                            error(7, lineNumber);   //error : a semicolon is needed.
                        }
                    }
                    else {
                        error(13, lineNumber);   //error : a colon is needed.
                    }
                }
                else {
                    error(20, lineNumber);   //error : a right parenthsis is needed.
                }
            }
            else {
                error(21, lineNumber);   //error : a left parenthsis is needed.
            }
        }
        else {
            error(10, lineNumber);   //error : an identifier is needed.
        }
    }
    else {
        error(23, lineNumber);   //error : "function"is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "Function Head finished." << endl;
}
void paramList() {
    cout << setw(numOfBlank++ * 4) << "" << "Parameter List started." << endl;
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
                getSym();
                ;
            }
            else {
                error(10, lineNumber);   //error : an identifier is needed.
            }
        }
        if (sym == colon) {
            getSym();
            baseType();
            while (sym == semicolon) {
                getSym();
                paramList();
            }
        }
        else {
            error(13, lineNumber);   //error : a colon is needed.
        }
    }
    else {
        error(10, lineNumber);   //error : an identifier is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "Parameter List finished." << endl;
}

void statement() {
    cout << setw(numOfBlank++ * 4) << "" << "A statement started. ";
    identtype t;
    switch (sym) {
        case ident:
            getSym();
            if (sym == assign || sym == lbracket) {
                assignStatement();
            }
            else if(sym == lparen) {
                callProcStatement();
            }
            else {
                error(24, lineNumber);
                //error : unknown statement. Maybe a variable or a procedure is needed.
            }
            //t = getIdentType(lsIdent);
            //if (t == vartype) {
            //    assignStatement();
            //}
            //else if(t == proctype) {
            //    callProcStatement();
            //}
            //else {
            //    error(24, lineNumber);
            //    //error : unknown statement. Maybe a variable or a procedure is needed.
            //}
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
            numOfBlank--;
            break;
        case readsym:
            readStatement();
            break;
        case writesym:
            writeStatement();
            break;
        default:
            error(25, lineNumber);   //error : invalid statement.
            break;
    }
    cout << setw(numOfBlank * 4) << "" << "A statement finished." << endl;
}

void assignStatement() {
    cout << "This is an Assign Statement." << endl;
    identtype it;
    datatype dt;
    int tmpLv;
    //√<赋值语句>::=<标识符> := <表达式> | <标识符>'['<表达式>']':= <表达式>
    //if (sym == ident) {
        //it = getIdentType(lsIdent);
        //dt = getDataType(lsIdent);
        //tmpLv = getDataLevel(lsIdent);
        //getSym();
        if (sym == assign) {
            getSym();
            //if (it == vartype) {
                expression();
                assignIt();
            //}
            //else if (it == functype) {
                //todo : checkLevel
                //if (true) {
                    //assignIt(dt);
                //}
                //else {
                    //error(0, lineNumber);   //error : can't find the function identifier.
                //}
            //}
            //else {
            //    error(0, lineNumber);   //error : this variable can't be assigned.
            //}
        }
        else if (sym == lbracket) {
            getSym();
            expression();
            int index = (int)expData;
            //if (expType != inttype) {
            //    error(26, lineNumber);   //error : the expression type should be integer.
            //}
            if (sym == rbracket) {
                getSym();
                if (sym == assign) {
                    getSym();
                    expression();
                    //assignIt(dt, index);
                    assignIt();
                }
                else {
                    error(9, lineNumber);   //error : an assign symbol is needed.
                }
            }
            else {
                error(15, lineNumber);   //error : a right bracket is needed.
            }
        }
        else {
            error(9, lineNumber);   //error : an assign symbol is needed.
        }
    //}
    //else {
    //    error(10, lineNumber);   //error : an identifier is needed.
    //}
    cout << setw(--numOfBlank * 4) << "" << "The Assign Statement finished." << endl;
}
void assignIt() {

}
void assignIt(datatype dt) {
    switch (dt) {
        case nul:
            error(27, lineNumber);   //type check failed.
            break;
        case chartype:
            if (sym == chr) {
                setData(lsIdent, lsChar);
            }
            else {
                error(27, lineNumber);   //type check failed.
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
                error(27, lineNumber);   //type check failed.
            }
            break;
        default:
            error(27, lineNumber);   //type check failed.
            break;
    }
}
void assignIt(datatype dt, int index) {
    switch (dt) {
        case nul:
            error(27, lineNumber);   //type check failed.
            break;
        case chartype:
            if (sym == chr) {
                setData(lsIdent, index, lsChar);
            }
            else {
                error(27, lineNumber);   //type check failed.
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
                error(27, lineNumber);   //type check failed.
            }
            break;
        default:
            error(27, lineNumber);   //type check failed.
            break;
    }
}

void callProcStatement() {
    cout << "This is a Procedure Call Statement." << endl;
    identtype it;
    //if (sym == ident) {
        //it = getIdentType(lsIdent);
        //if (it == proctype) {
            //getSym();
            if (sym == lparen) {
                getSym();
                if (sym != rparen) {
                    actualParamList();
                }
                if (sym == rparen) {
                    getSym();
                }
                else {
                    error(20, lineNumber);   //error : a right parenthsis is needed.
                }
            }
            else {
                error(21, lineNumber);   //error : a left parenthsis is needed.
            }
    //    }
    //    else {
    //        error(0, lineNumber);   //error : the identifier should be a procedure.
    //    }
    //}
    //else {
    //    error(10, lineNumber);   //error : an identifier is needed.
    //}
    cout << setw(--numOfBlank * 4) << "" << "The Procedure Call Statement finished." << endl;
}
void callFuncStatement() {
    cout << setw(numOfBlank++ * 4) << "" << "This is a Function Call Statement." << endl;
    identtype it;
    //if (sym == ident) {
        it = getIdentType(lsIdent);
        //if (it == functype) {
            //getSym();
            if (sym == lparen) {
                getSym();
                if (sym != rparen) {
                    actualParamList();
                }
                if (sym == rparen) {
                    getSym();
                }
                else {
                    error(20, lineNumber);   //error : a right parenthsis is needed.
                }
            }
            else {
                error(21, lineNumber);   //error : a left parenthsis is needed.
            }
        //}
        //else {
        //    error(28, lineNumber);   //error : the identifier should be a procedure.
        //}
    //}
    //else {
    //    error(10, lineNumber);   //error : an identifier is needed.
    //}
        cout << setw(--numOfBlank * 4) << "" << "The Function Call Statement finished." << endl;
}
void actualParamList() {
    cout << setw(numOfBlank++ * 4) << "" << "Actual Param List started." << endl;
    expression();
    while (sym == comma) {
        getSym();
        expression();
    }
    cout << setw(--numOfBlank * 4) << "" << "Actual Param List finished." << endl;
}

void ifStatement() {
    cout << "This is a Condition Statement." << endl;
    getSym();
    condition();
    if (sym == thensym) {
        getSym();
        statement();
        if (sym == elsesym) {
            getSym();
            statement();
        }
    }
    else {
        error(29, lineNumber);   // error : "then" is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "The Condition Statement finished." << endl;
}

void condition() {
    cout << setw(numOfBlank++ * 4) << "" << "Condition started." << endl;
    expression();
    switch (sym) {
        case eql:
            break;
        case neq:
            break;
        case lss:
            break;
        case leq:
            break;
        case gtr:
            break;
        case geq:
            break;
        default:
            error(30, lineNumber);   //error : invalid relational operator.
            break;
    }
    getSym();
    expression();
    //todo : 
    cout << setw(--numOfBlank * 4) << "" << "Condition finished." << endl;
}

void whileStatement() {
    cout << "This is a While Statement." << endl;
    getSym();
    condition();
    if (sym == dosym) {
        getSym();
    }
    else {
        error(31, lineNumber);   // error : "do" is needed.
    }
    statement();
    cout << setw(--numOfBlank * 4) << "" << "The While Statement finished." << endl;
}

void forStatement() {
    cout << "This is a For Statement." << endl;
    getSym();
    bool negative = false;
    int f, t, b;
    if (sym == ident) {
        sprintf_s(name, MaxRes, "%s", lsIdent);
        getSym();
        if (sym == assign) {
            getSym();
            expression();
            f = expData;
            if (sym == tosym) {
                getSym();
                expression();
                t = expData;
                switch (sym) {
                    case minussym:
                        negative = true;
                    case plussym:
                        getSym();
                        break;
                }
                if (sym == bysym) {
                    getSym();
                    if (sym == num) {
                        if (negative) {
                            b = 0 - lsNum;
                        }
                        else {
                            b = lsNum;
                        }
                        getSym();
                        if (sym == dosym) {
                            getSym();
                            statement();
                        }
                        else {
                            error(31, lineNumber);   // error : "do" is needed.
                        }
                    }
                    else {
                        error(11, lineNumber);   //error : a number or a char is needed.
                    }
                }
                else {
                    error(32, lineNumber);   //error : "by" is needed.
                }
            }
            else {
                error(33, lineNumber);   //error : "to" is needed.
            }
        }
        else {
            error(9, lineNumber);   //error : an assign symbol is needed.
        }
    }
    else {
        error(10, lineNumber);   //error : an identifier is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "The For Statement finished." << endl;
}

void complexStatement() {
    cout << setw(numOfBlank++ * 4) << "" << "This is a Complex Statement." << endl;
    if (sym == beginsym) {
        complexLevel++;
        getSym();
        statement();
        while (sym == semicolon) {
            getSym();
            statement();
        }
        if (sym == endsym) {
            //todo : 
            complexLevel--;
            getSym();
        }
        else {
            error(34, lineNumber);   //error : "end" is needed.
        }
    }
    else {
        error(35, lineNumber);   //error : "begin" is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "The Complex Statement finished." << endl;
}

void readStatement() {
    cout << "This is a Read Statement." << endl;
    getSym();
    if (sym == lparen) {
        getSym();
        if (sym == ident) {
            sprintf_s(name, MaxRes, "%s", lsIdent);
            
            getSym();
            while (sym == comma) {
                getSym();
                if (sym == ident) {
                    sprintf_s(name, MaxRes, "%s", lsIdent);
                    getSym();
                }
                else {
                    error(10, lineNumber);   //error : an identifier is needed.
                }
            }
            if (sym == rparen) {
                getSym();
            }
            else {
                error(20, lineNumber);   //error : a right parenthsis is needed.
            }
        }
        else {
        error(10, lineNumber);   //error : an identifier is needed.
        }
    }
    else {
        error(21, lineNumber);   //error : a left parenthsis is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "The Read Statement finished." << endl;
}

void writeStatement() {
    cout << "This is a Write Statement." << endl;
    getSym();
    if (sym == lparen) {
        getSym();
        if (sym == str) {
            getSym();
            if (sym == comma) {
                getSym();
                expression();
            }
            if(sym == rparen) {
                getSym();
            }
            else {
                error(20, lineNumber);   //error : a right parenthsis is needed.
            }
        }
        else {
            expression();
            if (sym == rparen) {
                getSym();
            }
            else {
                error(20, lineNumber);   //error : a right parenthsis is needed.
            }
        }
    }
    else {
        error(21, lineNumber);   //error : a left parenthsis is needed.
    }
    cout << setw(--numOfBlank * 4) << "" << "The Write Statement finished." << endl;
}

void expression() {
    cout << setw(numOfBlank++ * 4) << "" << "Expression started." << endl;
    bool negative = false;
    int t;
    switch (sym) {
        case minussym:
            negative = true;
        case plussym:
            getSym();
            break;
    }
    t = term();
    if (negative) {
        expData = 0 - t;
    }
    else {
        expData = t;
    }
    while (sym == plussym || sym == minussym) {
        switch (sym) {
            case minussym:
                negative = true;
                getSym();
                break;
            case plussym:
                negative = false;
                getSym();
                break;
        }
        t = term();
        if (negative) {
            expData -= t;
        }
        else {
            expData += t;
        }
    }
    cout << setw(--numOfBlank * 4) << "" << "Expression finished." << endl;
}

int term() {
    cout << setw(numOfBlank++ * 4) << "" << "Term started." << endl;
    int term, t;
    bool times;
    term = factor();
    while (sym == timessym || sym == slashsym) {
        switch (sym) {
            case timessym:
                times = true;
                break;
            case slashsym:
                times = false;
                break;
        }
        getSym();
        t = factor();
        if (times) {
            term *= t;
        }
        else {
            term /= t;
        }
    }
    cout << setw(--numOfBlank * 4) << "" << "Term finished." << endl;
    return term;
}

int factor() {
    cout << setw(numOfBlank++ * 4) << "" << "Factor started." << endl;
    int factor = -1;
    if (sym == num) {
        factor = lsNum;
        getSym();
    }
    else if(sym == lparen) {
        getSym();
        expression();
        factor = expData;
        if (sym == rparen) {
            getSym();
        }
        else {
            error(20, lineNumber);   //error : a right parenthsis is needed.
        }
    }
    else if (sym == ident) {
        //char name[MaxRes + 1];
        sprintf_s(name, MaxRes, "%s", lsIdent);
        getSym();
        if (sym == lparen) {
            callFuncStatement();
            factor = -1;
        }
        else if (sym == lbracket) {
            getSym();
            expression();
            factor = expData;
            if (sym == rbracket) {
                getSym();
            }
            else {
                error(15, lineNumber);   //error : a right bracket is needed.
            }
            //if (sym == num) {
            //    factor = -1;     //todo : 
            //    getSym();
            //    if (sym == rbracket) {
            //        getSym();
            //    }
            //    else {
            //        error(15, lineNumber);   //error : a right bracket is needed.
            //    }
            //}
            //else {
            //    error(11, lineNumber);   //error : a number or a char is needed.
            //}
        }
        else {
            factor = -1;     //todo:
        }
    }
    cout << setw(--numOfBlank * 4) << "" << "Factor finished." << endl;
    return factor;
}