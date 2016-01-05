//Compiler-pl0.cpp
#include <iostream>
#include "definitions.h"
#include "Interpreter.h"
#include "TableMgr.h"

//using namespace std;
extern int printLexerStatistics();
extern void initLexer();
extern int startParser();
extern void printMcode();
//extern void printLevelWordTable();
int main(int argc, char* argv[]) {
    if (argc == 2) {
        strcpy_s(filename, argv[1]);
    }
    else {
        //cin >> filename;
        cin.getline(filename, MaxStr);
        
    }
    initLexer();    //Initialize Lexer and other things.
    startParser();  //Start parsing.
    interpret();    //Interpret Mcode to MIPS code.
    //printMcode();
    //printWordTable();
    return 0;
}