//Parser.h
#include "definitions.h"
extern int getSym();
extern void error(int, int);

void semiProgram();

void constDeclaration();
void constDefinition();
int constData(datatype* dtp);

void varDeclaration();
void varDefinition();

datatype type(char start[]);
datatype baseType();

void procedureDeclaration();
void procedureHead();
void functionDeclaration();
void functionHead();
int paramList();

void statement();
void assignStatement();
void ifStatement();
void whileStatement();
void forStatement();
void callProcStatement();
void callFuncStatement();
void complexStatement();
void readStatement();
void writeStatement();
void blankStatement();

bool actualParamList(char name[]);
symbol condition();

expData* expression();
expData* term();
expData* factor();


void assignIt(char name[]);
void assignIt(char name[], int index);
void assignIt(datatype dt);
void assignIt(datatype dt, int index);