//Lexer.cpp
/*Lexical analyzer 词法分析器*/
/*
what to do :
a.记录标识符及其相关属性（动态数组+结构体实现吧，try try）
（标识符类型，数值类型，level层级，复杂属性指针）
typedef struct {
enum type

b.复杂属性结构体（妈个鸡说的就是你 -> 数组）

*/


//#include <string>
#include <iostream>
#include <iomanip>
#include "definitions.h"
using namespace std;

extern char ch;
extern int lineNumber;
//extern char* resConst[NumRes];
//extern int symbolTable[NumRes];
ifstream fpin;

extern void error(int, int);
extern int printLexerStatistics();

int getSym();
char getch();


extern void initLexer() {
    init(fpin);
    ch = getch();
    ch = getch();
    getSym();
}

extern int printLexerStatistics() {
    init(fpin);
    ch = getch();
    while (getSym() != -1);
    cout << endl;
    cout << setw(4) << "num"
        << setw(12) << "type" << ' '
        << setw(6) << "amount" << endl;
    /*for (int i = 0; i < NumRes; i++) {
        cout << setw(4) << i + 1
            << setw(12) << resConst[i] << ' '
            << setw(6) << symbolTable[i] << endl;
    }
    cout << endl << "Amount of lines : " << lineNumber << endl;*/
    return 0;
}



extern int getSym() {
    //char ch;
    symbol r;
    //ch = getch();
    while (ch == ' ' || ch == '\t') {
        ch = getch();
    }
    //transform(&ch);
    if (isLetter(ch)) { //字母开头，标识符，保留字
        char wd[MaxRes],smallwd[MaxRes];
        int x = 0;
        wd[x] = ch;
        smallwd[x] = transform(ch);
        x++;
        while (x < MaxRes && isLetterOrDigit(ch = getch())) {
            wd[x] = ch;
            smallwd[x] = transform(ch);
            x++;
        }
        wd[x] = '\0';
        smallwd[x] = '\0';
        if (x >= MaxRes) {
            error(1, lineNumber);   //标识符超出长度限制（MaxRes个）
            while (!isLetterOrDigit(ch = getch()));
        }
        int rx;
        for (rx = 4; rx<NumRes && strcmp(smallwd, symbolConst[rx]); rx++);      //查找保留字表
        if (rx > NumRes - 1) {            //超出，为标识符
            symbolTable[ident]++;
            sym = ident;
            r = ident;
            sprintf_s(lsIdent, MaxRes, "%s", wd);
        }
        else {      //未超出，保留字
            symbolTable[rx]++;
            r = symbol(rx);
            sym = symbol(rx);
        }
    }
    else if (isDigit(ch)) { //数字开头，数值
        //MaxNum = 9
        char stc[MaxNum + 1];
        int x = 0;
        stc[x++] = ch;
        while (x < MaxNum && isDigit(ch = getch())) {
            stc[x++] = ch;
        }
        stc[x] = '\0';
        //ch = getch();
        if (isDigit(ch)) {
            error(2, lineNumber); //数值超出长度限制
            while (!isDigit(ch = getch()));
        }
        lsNum = atoi(stc);
        symbolTable[num]++;
        r = num;
        sym = num;
    }
    else {  //符号开头，标点符号，圆/方括号
        switch (ch) {
            case ':':
                ch = getch();
                if (ch == '=') {
                    char c[3] = ":=";
                    ch = getch();
                    adder(c);
                    setSymbol(c);
                }
                else {
                    adder(':');
                    setSymbol(':');
                }
                break;
            case '<':
                ch = getch();
                if (ch == '=') {
                    char c[3] = "<=";
                    ch = getch();
                    adder(c);
                    setSymbol(c);
                }
                else if (ch == '>') {
                    char c[3] = "<>";
                    ch = getch();
                    adder(c);
                    setSymbol(c);
                }
                else {
                    adder('<');
                    setSymbol('<');
                }
                break;
            case '>':
                ch = getch();
                if (ch == '=') {
                    char c[3] = ">=";
                    ch = getch();
                    adder(c);
                    setSymbol(c);
                }
                else {
                    adder('>');
                    setSymbol('>');
                }
                break;
            case '\"':
            {
                         //char str[MaxStr + 1];
                         //cout << lineNumber << ", ";
                         int x = 0;
                         while (x < MaxStr && (ch = getch()) != '\"') {
                             if (ch >= 32 && ch <= 126) {
                                 lsStr[x++] = ch;
                             }
                             else {
                                 error(6, lineNumber);       //字符串含有非法字符
                                 x = -1;
                                 break;
                             }
                         }
                         if (x < 0) {
                             lsStr[0] = '\0';
                             while (getch() != '\"');    //去掉字符串剩下的部分
                         }
                         else {
                             lsStr[x] = '\0';
                             if (x>MaxStr) {     //字符串超出长度
                                 while (getch() != '\"');    //去掉字符串剩下的部分
                             }
                         }
                         adder('\"');
                         setSymbol('\"');
                         ch = getch();
            }
                break;
            case '\'':
                ch = getch();
                if (isLetterOrDigit(ch)) {
                    lsChar = ch;
                }
                else {
                    error(4, lineNumber);   //必须是字母或者数字
                    lsChar = '\0';
                }
                if (ch != '\'') {
                    ch = getch();
                    if (ch != '\'') {
                        error(5, lineNumber);   //字符只能由一个数字或字母组成
                        while ((ch = getch()) != '\'');
                    }
                }
                adder('\'');
                setSymbol('\'');
                ch = getch();
                break;
            case '=':
            case '+':
            case '-':
            case '*':
            case '/':
            case ',':
            case ';':
            case '.':
            case '(':
            case ')':
            case '[':
            case ']':
                r = adder(ch);
                setSymbol(ch);
                ch = getch();
                break;
            case '\0':
            {
                ch = getch();
                int rt = getSym();
                lineNumber++;
                return rt;
            }
                break;
            case -1:
                return -1;
            default:
                symbolTable[nil]++;
                //cout << ch;
                ch = getch();
                break;
        }
    }
        return r;
}

char getch() {
    static char line[MaxStr + 1] = "";
    static int index = -1;
    ++index;
    if (line[index] == '\0') {
        //lineNumber++; 
        if (fpin.eof()) {
            error(-1, lineNumber);      //意外遇到文件尾。
            return -1;
        }
        fpin.getline(line, MaxStr);
        while (!fpin.eof() && line[0] == '\0') {
            lineNumber++;
            fpin.getline(line, MaxStr);
        }
        index = -1;
        return '\0';
    }
    //transform(&line[index]);
    return line[index];
}
