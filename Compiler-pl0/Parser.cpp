//Parser.cpp
#include <iomanip>
#include <iostream>
#include "definitions.h"
#include "Generator.h"
#include "TableMgr.h"
#include "Err.h"
#include "Parser.h"
using namespace std;

//最右端是终结符号的子程序需要getSym();

int numOfBlank = 0;

int indexOfLabel = 0;

extern int startParser() {
    semiProgram();
    return 0;
}


void semiProgram() {
    level++;
    indexOfLabel++;
    char programLabel[20];
    sprintf_s(programLabel, "semiProgLabel%d", indexOfLabel);
    //cout << setw(numOfBlank++*4) << "" << "Into a semi-Program: " << endl;
    if (sym == constsym) {
        constDeclaration();
    }
    if (sym == varsym) {
        varDeclaration();
    }
    int offset_t = offset;
    g_j(programLabel);
    while (sym == procsym || sym == funcsym) {
        offset = 56;
        if (sym == procsym) {
            procedureDeclaration();
        }
        else if (sym == funcsym) {
            functionDeclaration();
        }
    }
    offset = offset_t;
    g_label(programLabel);
    complexStatement();
    //cout << setw(--numOfBlank * 4) << "" << "Semi-Program finished." << endl;
    //printLevelWordTable();
    //cout << "----------------------------------------------------------------------" << endl;

    deleteCurrentLvWord();
    level--;
}

void constDeclaration() {
    //cout << setw(numOfBlank++*4) << "" << "Const Declaration started." << endl;
    if (sym != constsym) {
        error(8, lineNumber);   //error : "const" is needed.
        return;
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
    else {
        getSym();
    }
    //cout << setw(--numOfBlank * 4) << "" << "Const Declaration finished." << endl << endl;
}
void constDefinition() {
    //cout << setw(numOfBlank++ * 4) << "" << "Const Definition started." << endl;
    char name[MaxRes + 1];
    int data;
    datatype dtp;
    if (sym == ident) {
        strcpy_s(name, lsIdent);
        getSym();
        if (sym == eql) {
            getSym();
            data = constData(&dtp);
            addTable(name, consttype, dtp, data, level);
            g_save_const(name);
        }
        else {
            error(9, lineNumber, errconstDef);   //error : an assign symbol is needed.
        }
    }
    else {
        error(10, lineNumber, errconstDef);   //error : an identifier is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "Const Definition finished." << endl;
}
int constData(datatype* tp) {
    bool negative = false;
    int n;
    if (sym == plussym || sym == minussym) {
        if (sym == minussym) {
            negative = true;
        }
        getSym();
    }
    if (sym == num) {
        *tp = inttype;
        if (negative) {
            n = -lsNum;
        }
        else {
            n = lsNum;
        }
    }
    else if (sym == chr) {
        *tp = chartype;
        if (negative) {
            n = -lsChar;
        }
        else {
            n = lsChar;
        }
    }
    else {
        error(11, lineNumber, errconstDef);   //error : a number or a char is needed.
    }
    getSym();
    //cout << setw(numOfBlank * 4) << "" << "This is data of const type." << endl;
    return n;
}

void varDeclaration() {
    //cout << setw(numOfBlank++ * 4) << "" << "Variable Declaration started." << endl;
    if (sym != varsym) {
        error(12, lineNumber);   //error : "var" is needed.
    }
    getSym();
    varDefinition();
    if (sym != semicolon) {
        error(7, lineNumber, errvar);   //error : a semicolon is needed.
    }
    getSym();
    while (sym == ident) {
        varDefinition();
        if (sym != semicolon) {
            error(7, lineNumber);   //error : a semicolon is needed.
        }
        getSym();
    }
    //cout << setw(--numOfBlank * 4) << "" << "Variable Declaration finished." << endl << endl;
}
void varDefinition() {
    //cout << setw(numOfBlank++ * 4) << "" << "Variable Definition started." << endl;
    char start[MaxRes + 1];
    char name[MaxRes + 1];
    if (sym == ident) {
        strcpy_s(start, lsIdent);
        strcpy_s(name, lsIdent);
        addTable(name, vartype, level);
        getSym();
        while (sym == comma) {
            getSym();
            if (sym == ident) {
                strcpy_s(name, lsIdent);
                addTable(name, vartype, level);
                getSym();
            }
            else {
                error(10, lineNumber, errvar);   //error : an identifier is needed.
            }
        }
        if (sym == colon) {
            getSym();
            datatype dt = type(start);
        }
        else {
            error(13, lineNumber, errvar);   //error : a colon is needed.
        }
    }
    //cout << setw(--numOfBlank * 4) << "" << "Variable Definition finished." << endl;
    //free the memory allocated.
    
}

datatype type(char start[]) {
    datatype dt = nul;
    int length = 0;
    if (sym == intsym || sym == charsym) {
        dt = baseType();
        setDataType(start, dt);
    }
    else if(sym == arraysym) {
        getSym();
        if (sym == lbracket) {
            getSym();
            if (sym == num) {
                length = lsNum;
                getSym();
                if (sym == rbracket) {
                    getSym();
                    if (sym == ofsym) {
                        getSym();
                        dt = baseType();
                        if (dt == inttype) {
                            dt = intarrtype;
                        }
                        else if (dt == chartype) {
                            dt = chararrtype;
                        }
                        else {
                            dt = nul;
                        }
                        setDataType(start, dt, length);
                    }
                    else {
                        error(14, lineNumber, errvar);   //error : the word "of" is needed.
                    }
                }
                else {
                    error(15, lineNumber, errvar);   //error : a right bracket is needed.
                }
            }
            else {
                error(16, lineNumber, errvar);   //error : a integer variable is needed.
            }
        }
        else {
            error(17, lineNumber, errvar);   //error : a left bracket is needed.
        }
    }
    else {
        error(18, lineNumber, errvar);   //error : unknown variable type.
    }
    //cout << setw(numOfBlank * 4) << "" << "a type reserved word." << endl;
    return dt;
}
datatype baseType() {
    datatype dt;
    if (sym == intsym) {
        dt = inttype;
        getSym();
    }
    else if (sym == charsym) {
        dt = chartype;
        getSym();
    }
    else {
        error(19, lineNumber);   //error : no this type.
    }
    //cout << setw(numOfBlank * 4) << "" << "a base type reserved word." << endl;
    return dt;
}

void procedureDeclaration() {
    //cout << setw(numOfBlank++ * 4) << "" << "Procedure Declaration started." << endl;
    procedureHead();
    semiProgram();
    g_jr();
    if (sym == semicolon) {
        getSym();
    }
    else {
        error(7, lineNumber);   //error : a semicolon is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "Procedure Declaration finished." << endl;
}
void procedureHead() {
    //cout << setw(numOfBlank++ * 4) << "" << "Procedure Head started." << endl;
    int paramCounter = 0;
    indexOfLabel++;
    char procname[MaxRes + 1];
    if (sym == procsym) {
        getSym();
        if (sym == ident) {
            strcpy_s(procname, lsIdent);
            //sprintf_s(procname, "%s_%d", lsIdent, indexOfLabel);
            g_label(procname, indexOfLabel);
            addTable(procname, proctype, level);
            //cout << setw(numOfBlank * 4) << "" << "Procedure Name : " << lsIdent << endl;
            //level++;
            getSym();
            if (sym == lparen) {
                getSym();
                paramCounter = 0;
                if (sym == ident || sym == varsym) {
                    paramCounter = paramList();
                }
                setParamLengthAndIndex(procname, paramCounter, indexOfLabel);
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
                    error(20, lineNumber, errproc);   //error : a right parenthsis is needed.
                }
            }
            else {
                error(21, lineNumber, errproc);   //error : a left parenthsis is needed.
            }
        }
        else {
            error(10, lineNumber, errproc);   //error : an identifier is needed.
        }
    }
    else {
        error(22, lineNumber);   //error : "procedure"is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "Procedure Head finished." << endl;
}

void functionDeclaration() {
    //cout << setw(numOfBlank++ * 4) << "" << "Function Declaration started." << endl;
    functionHead();
    semiProgram();
    g_jr();
    if (sym == semicolon) {
        getSym();
    }
    else {
        error(7, lineNumber);   //error : a semicolon is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "Function Declaration finished." << endl;
}
void functionHead() {
    //cout << setw(numOfBlank++ * 4) << "" << "Function Head started." << endl;
    int paramCounter = 0;
    indexOfLabel++;
    char funcname[MaxRes + 1];
    if (sym == funcsym) {
        getSym();
        if (sym == ident) {
            strcpy_s(funcname, lsIdent);
            //sprintf_s(funcname, "%s_%d", lsIdent, indexOfLabel);
            g_label(funcname, indexOfLabel);
            addTable(funcname, functype, level);
            //cout << setw(numOfBlank * 4) << "" << "Function Name : " << lsIdent << endl;
            //level++;
            getSym();
            if (sym == lparen) {
                getSym();
                paramCounter = 0;
                if (sym == ident || sym == varsym) {
                    paramCounter = paramList();
                }
                setParamLengthAndIndex(funcname, paramCounter, indexOfLabel);
                if (sym == rparen) {
                    getSym();
                    if (sym == colon) {
                        getSym();
                        datatype dt = baseType();
                        setFuncDataType(funcname, dt);
                        if (sym == semicolon) {
                            getSym();
                        }
                        else {
                            error(7, lineNumber);   //error : a semicolon is needed.
                        }
                    }
                    else {
                        error(13, lineNumber, errfunc);   //error : a colon is needed.
                    }
                }
                else {
                    error(20, lineNumber, errfunc);   //error : a right parenthsis is needed.
                }
            }
            else {
                error(21, lineNumber, errfunc);   //error : a left parenthsis is needed.
            }
        }
        else {
            error(10, lineNumber, errfunc);   //error : an identifier is needed.
        }
    }
    else {
        error(23, lineNumber);   //error : "function"is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "Function Head finished." << endl;
}
int paramList() {
    //cout << setw(numOfBlank++ * 4) << "" << "Parameter List started." << endl;
    int paramCounter = 0;
    char name[MaxRes + 1];
    char start[MaxRes + 1];
    bool varFlag = false;
    if (sym == varsym) {
        varFlag = true;
        getSym();
    }
    if (sym == ident) {
        strcpy_s(name, lsIdent);
        strcpy_s(start, lsIdent);
        paramCounter++;
        if (varFlag) {
            addTable(name, paramvartype, level);
        }
        else {
            addTable(name, paramtype, level);
        }
        getSym();
        while (sym == comma) {
            getSym();
            if (sym == ident) {
                paramCounter++;
                strcpy_s(name, lsIdent);
                if (varFlag) {
                    addTable(name, paramvartype, level);
                }
                else {
                    addTable(name, paramtype, level);
                }
                getSym();
            }
            else {
                error(10, lineNumber, errparam);   //error : an identifier is needed.
            }
        }
        if (sym == colon) {
            getSym();
            datatype dt = baseType();
            setDataType(start, dt);
            while (sym == semicolon) {
                getSym();
                paramCounter += paramList();
            }
        }
        else {
            error(13, lineNumber, errparam);   //error : a colon is needed.
        }
    }
    else {
        error(10, lineNumber, errparam);   //error : an identifier is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "Parameter List finished." << endl;
    return paramCounter;
}

void statement() {
    //cout << setw(numOfBlank++ * 4) << "" << "A statement started. ";
    identtype t;
    switch (sym) {
        case ident:
            t = getIdentType(lsIdent);
            if (t == vartype || t == paramtype || t == paramvartype || t == functype) {
                assignStatement();
            }
            else if(t == proctype) {
                callProcStatement();
            }
            else if (t == consttype) {
                error(48, lineNumber, errassign);   // error : const data can't be assigned.
            }
            else {
                error(24, lineNumber);
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
            numOfBlank--;
            break;
        case readsym:
            readStatement();
            break;
        case writesym:
            writeStatement();
            break;
        default:
            break;
    }
    //cout << setw(numOfBlank * 4) << "" << "A statement finished." << endl;
}

void assignStatement() {
    //cout << "This is an Assign Statement." << endl;
    identtype it;
    datatype dt;
    int tmpLv;
    char name[MaxRes + 1];
    //√<赋值语句>::=<标识符> := <表达式> | <标识符>'['<表达式>']':= <表达式>
    if (sym == ident) {
        strcpy_s(name, lsIdent);
        it = getIdentType(lsIdent);
        dt = getDataType(lsIdent);
        tmpLv = getDataLevel(lsIdent);
        getSym();
        if (sym == assign) {
            getSym();
            if (it == vartype || it == paramtype || it == paramvartype) {
                expression();
                assignIt(name);
            }
            else if (it == functype) {
                //todo : checkLevel
                if (true) {
                    expression();
                    g_add("$t9", 0, "$v0");
                }
                else {
                    error(40, lineNumber);   //error : can't find the function identifier.
                }
            }
            else {
                error(39, lineNumber, errassign);   //error : this variable can't be assigned.
            }
        }
        else if (sym == lbracket) {
            getSym();
            expression();
            g_add("$t9", 0, "$s6");
            //if (expType != inttype) {
            //    error(26, lineNumber);   //error : the expression type should be integer.
            //}
            if (sym == rbracket) {
                getSym();
                if (sym == assign) {
                    getSym();
                    expression();
                    assignIt(name);
                }
                else {
                    error(9, lineNumber, errassign);   //error : an assign symbol is needed.
                }
            }
            else {
                error(15, lineNumber, errassign);   //error : a right bracket is needed.
            }
        }
        else {
            error(9, lineNumber, errassign);   //error : an assign symbol is needed.
        }
    }
    else {
        error(10, lineNumber, errassign);   //error : an identifier is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "The Assign Statement finished." << endl;
}
void assignIt(char name[]) {
    const identifier* tp = getReadTableItem(name);
    if (tp->identt == vartype || tp->identt == paramtype || tp->identt == paramvartype) {
        if (tp->datat == inttype || tp->datat == chartype) {
            g_save(name);
        }
        else if (tp->datat == intarrtype || tp->datat == chararrtype) {
            g_warray(name);
        }
    }
    else if (tp->identt == functype) {
        if (level == tp->lv + 1) {
            if (tp->datat == inttype || tp->datat == chartype) {
                g_save(name);
            }
            else {
                error(0, lineNumber);   //error : invalid function type.
            }
        }
        else {
            error(42, lineNumber);   //error : can't find the correct function name.
        }
    }
}
//void assignIt(datatype dt) {
//    switch (dt) {
//        case nul:
//            error(27, lineNumber);   //type check failed.
//            break;
//        case chartype:
//            if (sym == chr) {
//                setData(lsIdent, lsChar);
//            }
//            else {
//                error(27, lineNumber);   //type check failed.
//            }
//            break;
//        case inttype:
//            if (sym == num) {
//                setData(lsIdent, lsNum);
//            }
//            else if (sym == chr) {
//                setData(lsIdent, (int)lsChar);
//            }
//            else {
//                error(27, lineNumber);   //type check failed.
//            }
//            break;
//        default:
//            error(27, lineNumber);   //type check failed.
//            break;
//    }
//}
//void assignIt(datatype dt, int index) {
//    switch (dt) {
//        case nul:
//            error(27, lineNumber);   //type check failed.
//            break;
//        case chartype:
//            if (sym == chr) {
//                setData(lsIdent, index, lsChar);
//            }
//            else {
//                error(27, lineNumber);   //type check failed.
//            }
//            break;
//        case inttype:
//            if (sym == num) {
//                setData(lsIdent, index, lsNum);
//            }
//            else if (sym == chr) {
//                setData(lsIdent, (int)lsChar);
//            }
//            else {
//                error(27, lineNumber);   //type check failed.
//            }
//            break;
//        default:
//            error(27, lineNumber);   //type check failed.
//            break;
//    }
//}

void callProcStatement() {
    //cout << "This is a Procedure Call Statement." << endl;
    int offset_t;
    char procname[MaxRes + 1];
    identtype it;
    offset_t = offset;
    if (sym == ident) {
        strcpy_s(procname, lsIdent);
        it = getIdentType(lsIdent);
        if (it == proctype) {
            getSym();
            if (sym == lparen) {
                getSym();
                //if (sym != rparen) {
                if (actualParamList(procname)) {
                    if (sym == rparen) {
                        offset = offset_t;
                        g_saveCallReg(procname);
                        g_jal(procname);
                        g_unsaveCallReg();
                        getSym();
                    }
                    else {
                        error(20, lineNumber, errcall);   //error : a right parenthsis is needed.
                    }
                }
                else {
                    error(43, lineNumber, errcall);  //error : parameter list dispatches.
                }
            }
            else {
                error(21, lineNumber, errcall);   //error : a left parenthsis is needed.
            }
        }
        else {
            error(0, lineNumber, errcall);   //error : the identifier should be a procedure.
        }
    }
    else {
        error(10, lineNumber);   //error : an identifier is needed.
    }
    offset = offset_t;
    //cout << setw(--numOfBlank * 4) << "" << "The Procedure Call Statement finished." << endl;
}
void callFuncStatement() {
    //cout << setw(numOfBlank++ * 4) << "" << "This is a Function Call Statement." << endl;
    char funcname[MaxRes + 1];
    int offset_t;
    identtype it;
    offset_t = offset;
    if (sym == ident) {
        strcpy_s(funcname, lsIdent);
        it = getIdentType(lsIdent);
        if (it == functype) {
            getSym();
            if (sym == lparen) {
                getSym();
                //if (sym != rparen) {
                if (actualParamList(funcname)) {
                    if (sym == rparen) {
                        offset = offset_t;
                        g_saveCallReg(funcname);
                        g_jal(funcname);
                        g_add("$v0", 0, "$t7");
                        g_unsaveCallReg();
                        getSym();
                    }
                    else {
                        error(20, lineNumber, errcall);   //error : a right parenthsis is needed.
                    }
                }
                else {
                    error(43, lineNumber, errcall);  //error : parameter list dispatches.
                }
            }
            else {
                error(21, lineNumber, errcall);   //error : a left parenthsis is needed.
            }
        }
        else {
            error(28, lineNumber, errcall);   //error : the identifier should be a procedure.
        }
    }
    else {
        error(10, lineNumber, errcall);   //error : an identifier is needed.
    }
    offset = offset_t;
    //cout << setw(--numOfBlank * 4) << "" << "The Function Call Statement finished." << endl;
}
bool actualParamList(char name[]) {
    //cout << setw(numOfBlank++ * 4) << "" << "Actual Param List started." << endl;
    identifier* tp = getTableItem(name);
    int paramNum = tp->length;
    if (paramNum == 0)
        return true;
    int funcLevel = tp->lv;
    offset += 56 + (tp->lv + 1) * 4;
    expData* expdata;
    //todo : 
    paramNum--;
    expdata = expression();
    if (expdata == null) {
        g_resetParamCounter();
        return false;
    }
    tp = tp->next;
    g_saveParam(funcLevel, tp->identt, *expdata);
    while (sym == comma) {
        paramNum--;
        if (paramNum < 0) {
            error(43, lineNumber, errcall);  //error : parameter list dispatches.
            break;
        }
        getSym();
        expdata = expression();
        if (expdata == null) {
            g_resetParamCounter();
            return false;
        }
        tp = tp->next;
        g_saveParam(funcLevel, tp->identt, *expdata);
    }
    if (paramNum > 0) {
        error(43, lineNumber, errcall);  //error : parameter list dispatches.
        return false;
    }
    //cout << setw(--numOfBlank * 4) << "" << "Actual Param List finished." << endl;
    g_resetParamCounter();
    return true;
}

void ifStatement() {
    //cout << "This is a Condition Statement." << endl;
    indexOfLabel++;
    symbol op;
    char elseLabel[16];
    char endifLabel[16];
    sprintf_s(elseLabel, "elseLabel%d", indexOfLabel);
    sprintf_s(endifLabel, "endifLabel%d", indexOfLabel);
    getSym();
    op = condition();
    switch (op) {
        case eql:
            g_cmp("neq", elseLabel);
            break;
        case neq:
            g_cmp("eql", elseLabel);
            break;
        case lss:
            g_cmp("geq", elseLabel);
            break;
        case leq:
            g_cmp("gtr", elseLabel);
            break;
        case gtr:
            g_cmp("leq", elseLabel);
            break;
        case geq:
            g_cmp("lss", elseLabel);
            break;
        default:
            error(30, lineNumber, errifhead);   //error : invalid relational operator.
            break;
    }
    if (sym == thensym) {
        getSym();
        statement();
        g_j(endifLabel);
        g_label(elseLabel);
        if (sym == elsesym) {
            getSym();
            statement();
        }
    }
    else {
        error(29, lineNumber, errifhead);   // error : "then" is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "The Condition Statement finished." << endl;
    g_label(endifLabel);
}

symbol condition() {
    //cout << setw(numOfBlank++ * 4) << "" << "Condition started." << endl;
    expression();
    symbol op;
    g_add("$t9", 0, "$s0");
    op = sym;
    getSym();
    expression();
    g_add("$t9", 0, "$s1");
    //cout << setw(--numOfBlank * 4) << "" << "Condition finished." << endl;
    return op;
}

void whileStatement() {
    //cout << "This is a While Statement." << endl;
    indexOfLabel++;
    getSym();
    char whileLabel[16];
    char endWhileLabel[20];
    sprintf_s(whileLabel, "whileLabel%d", indexOfLabel);
    sprintf_s(endWhileLabel, "endWhileLabel%d", indexOfLabel);

    g_label(whileLabel);
    symbol op = condition();
    switch (op) {
        case eql:
            g_cmp("neq", endWhileLabel);
            break;
        case neq:
            g_cmp("eql", endWhileLabel);
            break;
        case lss:
            g_cmp("geq", endWhileLabel);
            break;
        case leq:
            g_cmp("gtr", endWhileLabel);
            break;
        case gtr:
            g_cmp("leq", endWhileLabel);
            break;
        case geq:
            g_cmp("lss", endWhileLabel);
            break;
        default:
            error(30, lineNumber, errwhile);   //error : invalid relational operator.
            break;
    }
    if (sym == dosym) {
        getSym();
    }
    else {
        error(31, lineNumber, errwhile);   // error : "do" is needed.
    }
    g_saveConditionReg();
    statement();
    g_unsaveConditionReg();
    g_j(whileLabel);
    g_label(endWhileLabel);
    //cout << setw(--numOfBlank * 4) << "" << "The While Statement finished." << endl;
}

void forStatement() {
    //cout << "This is a For Statement." << endl;
    char name[MaxRes + 1];
    indexOfLabel++;
    char forLabel[16];
    char endforLabel[20];
    sprintf_s(forLabel, "forLabel%d", indexOfLabel);
    sprintf_s(endforLabel, "endforLabel%d", indexOfLabel);
    getSym();
    bool negative = false;
    int b;
    if (sym == ident) {
        sprintf_s(name, MaxRes, "%s", lsIdent);
        getSym();
        if (sym == assign) {
            getSym();
            expression();
            g_add("$t9", 0, "$s0");
            if (sym == tosym) {
                getSym();
                expression();
                g_add("$t9", 0, "$s1");
                g_label(forLabel);
                switch (sym) {
                    case minussym:
                        negative = true;
                    case plussym:
                        getSym();
                        break;
                }
                if (sym == bysym) {
                    getSym();
                    negative = false;
                    if (sym == minussym || sym == plussym) {
                        if (sym == minussym) {
                            negative = true;
                        }
                        getSym();
                    }
                    if (sym == num) {
                        if (lsNum != 0) {
                            if (negative) {
                                b = 0 - lsNum;
                            }
                            else {
                                b = lsNum;
                            }
                            getSym();
                            if (sym == dosym) {
                                if (b < 0) {
                                    g_cmp("lss", endforLabel);
                                }
                                else {
                                    g_cmp("gtr", endforLabel);
                                }
                                getSym();
                                g_saveForReg(name);
                                statement();
                                g_unsaveForReg(name);
                                g_add("$s0", b, "$s0");
                                g_j(forLabel);
                                g_label(endforLabel);
                            }
                            //for i := a to b by 1 do
                            else {
                                error(31, lineNumber, errforheaddo);   // error : "do" is needed.
                            }
                        }
                        else {
                            error(36, lineNumber, errforhead);  //error : step can't be zero.
                        }
                    }
                    else {
                        error(11, lineNumber, errforhead);   //error : a number or a char is needed in For Statement.
                    }
                }
                else {
                    error(32, lineNumber, errforhead);   //error : "by" is needed.
                }
            }
            else {
                error(33, lineNumber, errforhead);   //error : "to" is needed.
            }
        }
        else {
            error(9, lineNumber, errforhead);   //error : an assign symbol is needed in For Statement.
        }
    }
    else {
        error(10, lineNumber, errforhead);   //error : an identifier is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "The For Statement finished." << endl;
}

void complexStatement() {
    //cout << setw(numOfBlank++ * 4) << "" << "This is a Complex Statement." << endl;
    complexLevel++;
    if (sym != beginsym) {
        error(35, lineNumber);   //error : unknown start of code block, "begin" is needed.
    }
    getSym();
    statement();
    while (sym == semicolon) {
        getSym();
        statement();
    }
    if (sym == endsym) {
        complexLevel--;
        getSym();
    }
    else {
        error(34, lineNumber);   //error : a semicolon or an "end" is needed.
    }

    //else {
    //    error(35, lineNumber);   //error : unknown start of code block, "begin" is needed.
    //    complexLevel--;
    //}
    //cout << setw(--numOfBlank * 4) << "" << "The Complex Statement finished." << endl;
}

void readStatement() {
    //cout << "This is a Read Statement." << endl;
    char name[MaxRes + 1];
    getSym();
    if (sym == lparen) {
        getSym();
        if (sym == ident) {
            sprintf_s(name, MaxRes, "%s", lsIdent);
            g_read(name);
            getSym();
            while (sym == comma) {
                getSym();
                if (sym == ident) {
                    sprintf_s(name, MaxRes, "%s", lsIdent);
                    g_read(name);
                    getSym();
                }
                else {
                    error(10, lineNumber, errread);   //error : an identifier is needed.
                }
            }
            if (sym == rparen) {
                getSym();
            }
            else {
                error(20, lineNumber, errread);   //error : a right parenthsis is needed.
            }
        }
        else {
            error(10, lineNumber, errread);   //error : an identifier is needed.
        }
    }
    else {
        error(21, lineNumber, errread);   //error : a left parenthsis is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "The Read Statement finished." << endl;
}

void writeStatement() {
    //cout << "This is a Write Statement." << endl;
    getSym();
    expData* expdata;
    if (sym == lparen) {
        getSym();
        if (sym == str) {
            g_writeStr(lsStr);
            getSym();
            if (sym == comma) {
                getSym();
                expdata = expression();
                if (expdata != null) {
                    if (expdata->type == expNum || expdata->type == expFormula) {
                        g_write(inttype);
                    }
                    else {
                        g_write(expdata->name);
                    }
                }
                else {
                    //error(44, lineNumber);  // error : invalid expression
                    while (sym != rparen && sym!=semicolon)
                        getSym();
                }
            }
            if(sym == rparen) {
                getSym();
            }
            else {
                error(47, lineNumber);   //error : a right parenthsis is needed.
            }
        }
        else {
            expdata = expression();
            if (expdata != null) {
                if (expdata->type == expNum || expdata->type == expFormula) {
                    g_write(inttype);
                }
                else {
                    g_write(expdata->name);
                }
            }
            else {
                //error(44, lineNumber);  // error : invalid expression
                while (sym != rparen && sym != semicolon)
                    getSym();
            }
            if (sym == rparen) {
                getSym();
            }
            else {
                error(20, lineNumber);  //error : a right parenthsis is needed.
            }
        }
    }
    else {
        error(21, lineNumber,errwrite);   //error : a left parenthsis is needed.
    }
    //cout << setw(--numOfBlank * 4) << "" << "The Write Statement finished." << endl;
}

expData* expression() {
    // save data into $t9. $t9 = $t9 + $t8.
    expData* data = new expData();
    //cout << setw(numOfBlank++ * 4) << "" << "Expression started." << endl;
    bool negative = false;
    switch (sym) {
        case minussym:
            negative = true;
            
        case plussym:
            getSym();
            break;
    }
    data = term();
    if (negative) {
        g_sub("$0", "$t8", "$t9");
        data->type = expFormula;
    }
    else {
        g_add("$t8", "$0", "$t9");
    }
    while (sym == plussym || sym == minussym) {
        data->type = expFormula;
        switch (sym) {
            case minussym:
                negative = true;
                break;
            case plussym:
                negative = false;
                break;
        }
        getSym();
        term();
        if (negative) {
            g_sub("$t9", "$t8", "$t9");
        }
        else {
            g_add("$t9", "$t8", "$t9");
        }
    }
    //cout << setw(--numOfBlank * 4) << "" << "Expression finished." << endl;
    return data;
}

expData* term() {
    //save data into $t8. $t8 = $t8 + $t7.
    expData* data = new expData();
    //cout << setw(numOfBlank++ * 4) << "" << "Term started." << endl;
    bool times;
    data = factor();
    g_add("$t7", "$0", "$t8");
    while (sym == timessym || sym == slashsym) {
        data->type = expFormula;
        switch (sym) {
            case timessym:
                times = true;
                break;
            case slashsym:
                times = false;
                break;
        }
        getSym();
        data = factor();
        if (times) {
            g_gen("mul", "$t8", "$t7", "$t8");
        }
        else {
            g_gen("div", "$t8", "$t7", "$t8");
        }
    }
    //cout << setw(--numOfBlank * 4) << "" << "Term finished." << endl;
    return data;
}

expData* factor() {
    //save data into $t7.
    //变量或常量/数组项/数字/函数调用/算式
    //全部char->char型
    //出现int->int型
    char name[MaxRes + 1];
    expData* data = new expData();
    //cout << setw(numOfBlank++ * 4) << "" << "Factor started." << endl;
    //int factor = -1;
    if (sym == num) {
        data->type = expNum;
        g_add("$0", lsNum, "$t7");
        getSym();
    }
    else if(sym == lparen) {
        getSym();
        g_saveExpReg();
        data = expression();
        //first save the result($t9) into $t7, then recover $t8 $t9
        g_add("$t9", "$0", "$t7");
        g_unsaveExpReg();
        if (sym == rparen) {
            getSym();
        }
        else {
            error(20, lineNumber);   //error : a right parenthsis is needed.
        }
    }
    else if (sym == ident) {
        sprintf_s(name, MaxRes, "%s", lsIdent);
        const identifier *tp = getReadTableItem(name);
        if (tp == null) {
            error(49, lineNumber);  //error : identifier undefined.
            return null;
        }
        strcpy_s(data->name, name);
        if (tp->identt == functype) {
            data->type = expFunc;
            g_saveExpReg();
            callFuncStatement();
            g_unsaveExpReg();
        }
        else if (tp->identt == vartype && (tp->datat == intarrtype || tp->datat == chararrtype)) {
            data->type = expArray;
            getSym();
            if (sym == lbracket) {
                getSym();
                g_saveExpReg();
                expression();
                g_add("$t9", "$0", "$s7");
                g_rarray(name);   //$t7 = name[$t9]
                g_unsaveExpReg();
                if (sym == rbracket) {
                    getSym();
                }
                else {
                    error(15, lineNumber);   //error : a right bracket is needed.
                }
            }
            else {
                error(17, lineNumber);   //error : a left bracket is needed.
            }
        }
        else if (tp->identt == consttype
                || (tp->identt == vartype || tp->identt == paramtype || tp->identt == paramvartype) 
                    && (tp->datat == inttype || tp->datat == chartype)) {
            if (tp->identt == consttype) {
                data->type = expConst;
            }
            else if (tp->identt == paramvartype) {
                data->type = expParamVar;
            }
            else {
                data->type = expVar;
            }
            g_load(name);
            getSym();
        }
        else {
            error(41, lineNumber);  //can't find this identifier.
        }
    }
    else {
        data = NULL;
        error(44, lineNumber, errexp);  // error : invalid expression.
    }
    //cout << setw(--numOfBlank * 4) << "" << "Factor finished." << endl;
    return data;
}