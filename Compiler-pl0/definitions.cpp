#include <iostream>
#include <fstream>
#include "definitions.h"

using namespace std;


const char filename[] = "13061170_test.txt";

int lineNumber = 0;
char ch = ' ';
symbol sym;

int level = 0;
int complexLevel = 0;

char lsIdent[MaxRes + 1];
int lsNum;
char lsChar;
char lsStr[MaxStr + 1];

extern int symbolTable[NumRes] = { 0 };
extern char* symbolConst[NumRes] = {
    "null",     //1
    "ident", "num", "\"", "\'",     //4
    "const", "var", "array", "of", "integer", "char", "procedure", "function",  //8
    "if", "then", "else", "while", "do", "for", "to", "by",     //8
    "begin", "end", "read", "write",    //4
    "=", "<>", "<", "<=", ">", ">=",    //6
    "+", "-", "*", "/",     //4
    ",", ";", ":=", ":", ".",       //5
    "(", ")", "[", "]"      //4
};


int identTable[4] = { 0 };
int dataTable[4] = { 0 };

identifier *tableHead;
//identifier *tp;

//extern ifstream fpin;
void init(ifstream& fp) {
    fp.open(filename);
    tableHead = (identifier*)malloc(sizeof(identifier));
    tableHead->dataaddr = null;
    tableHead->next = null;
    //tp = tableHead;
    //identifier* table;
    
}

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'A');
}

bool isLetterOrDigit(char ch) {
    return isLetter(ch) || isDigit(ch);
}

void transform(char* ch) {
    if (*ch >= 'A' && *ch <= 'Z') {
        *ch = *ch + ('a' - 'A');
    }
}

symbol adder(char c[]) {
    int rx = 3;
    while (rx < NumRes && strcmp(c, symbolConst[rx++]));
    if (rx >= NumRes) {
        symbolTable[0]++;
        return nil;
    }
    else {
        rx--;
        symbolTable[rx]++;
        return symbol(rx);
    }
}

symbol adder(char ch) {
    char c[2];
    c[0] = ch;
    c[1] = '\0';
    return adder(c);
}

void setSymbol(char c[]) {
    int rx = 3;
    while (rx < NumRes && strcmp(c, symbolConst[rx++]));
    if (rx > NumRes) {
        sym = nil;
    }
    else {
        rx--;
        sym = symbol(rx);
    }
}

void setSymbol(char ch) {
    char c[2];
    c[0] = ch;
    c[1] = '\0';
    setSymbol(c);
}


//operations of word table:
identifier* getTableItem(char name[]) {
    identifier* p = tableHead->next;
    while (p != null) {
        if (strcmp(p->name, name))
            break;
        p = p->next;
    }
    return p;
}
void addTable(char name[], identtype identt, datatype datat, int lv) {
    identifier *tp;
    tp = tableHead;
    while (tp->next != null) {
        tp = tp->next;
    }
    tp->next = (identifier*)malloc(sizeof(identifier));
    tp = tp->next;
    tp->lv = lv;
    sprintf_s(tp->name, MaxRes, "%s", name);
    tp->dataaddr = null;
    tp->next = null;
}
void addTable(char name[], identtype identt, datatype datat, int lv, int length) {
    identifier *tp;
    tp = tableHead;
    while (tp->next != null) {
        tp = tp->next;
    }
    tp->next = (identifier*)malloc(sizeof(identifier));
    tp = tp->next;
    tp->lv = lv;
    tp->lengthOfArray = length;
    sprintf_s(tp->name, MaxRes, "%s", name);
    tp->dataaddr = null;
    tp->next = null;
}
void setData(char name[], int data) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp == null) {
        error(0, lineNumber);   //identifier not found.
        return;
    }
    if (tp->identt == functype || tp->identt == vartype) {
        if (tp->datat == inttype) {
            tp->dataaddr->intd = &data;
        }
        else {
            error(0, lineNumber);   //变量数据类型不对, an integer is needed.
        }
    }
    else {
        error(0, lineNumber);   //identifier type is wrong, function or variable is needed.
    }
}
void setData(char name[], char data) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp == null) {
        error(0, lineNumber);   //identifier not found.
        return;
    }
    if (tp->identt == functype || tp->identt == vartype) {
        if (tp->datat == chartype) {
            tp->dataaddr->chard = &data;
        }
        else {
            error(0, lineNumber);   //变量数据类型不对, a char is needed.
        }
    }
    else {
        error(0, lineNumber);   //identifier type is wrong, function or variable is needed.
    }
}
void setData(char name[], int index, int data) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp == null) {
        error(0, lineNumber);   //identifier not found.
        return;
    }
    if (index >= tp->lengthOfArray) {
        error(0, lineNumber);   //out of index bound.
        return;
    }
    if (tp->identt == functype || tp->identt == vartype) {
        if (tp->datat == intarrtype) {
            tp->dataaddr->intarr[index] = data;
        }
        else {
            error(0, lineNumber);   //变量数据类型不对, a integer array is needed.
        }
    }
    else {
        error(0, lineNumber);   //identifier type is wrong, variable type is needed.
    }
}
void setData(char name[], int index, char data) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp == null) {
        error(0, lineNumber);   //identifier not found.
        return;
    }
    if (index >= tp->lengthOfArray) {
        error(0, lineNumber);   //out of index bound.
        return;
    }
    if (tp->identt == functype || tp->identt == vartype) {
        if (tp->datat == chararrtype) {
            tp->dataaddr->chararr[index] = data;
        }
        else {
            error(0, lineNumber);   //变量数据类型不对, a char array is needed.
        }
    }
    else {
        error(0, lineNumber);   //identifier type is wrong, variable type is needed.
    }
}

int* getInt(char name[]) {
    identifier* identi = getTableItem(name);
    if (identi==null) {
        return 0;
    }
    return identi->dataaddr->intd;
}
char* getChar(char name[]) {
    identifier* identi = getTableItem(name);
    if (identi == null) {
        return 0;
    }
    return identi->dataaddr->chard;
}
int* getIntArray(char name[]) {
    identifier* identi = getTableItem(name);
    if (identi == null) {
        return 0;
    }
    return identi->dataaddr->intarr;
}
char* getCharArray(char name[]) {
    identifier* identi = getTableItem(name);
    if (identi == null) {
        return 0;
    }
    return identi->dataaddr->chararr;
}
int getLength(char name[]) {
    identifier* identi = getTableItem(name);
    if (identi == null) {
        return 0;
    }
    return identi->lengthOfArray;
}

identtype getIdentType(char name[]) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp != null) {
        return tp->identt;
    }
    else {
        return errtype;
    }
}
datatype getDataType(char name[]) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp != null) {
        return tp->datat;
    }
    else {
        return nul;
    }
}
int getDataLevel(char name[]) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp != null) {
        return tp->lv;
    }
    else {
        return -1;
    }
}