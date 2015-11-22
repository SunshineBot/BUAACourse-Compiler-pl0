#include <fstream>
using namespace std;

extern void error(int, int);

#define MaxRes 32
#define MaxNum 9
#define MaxStr 256

#define NumRes 44

#define null NULL
enum symbol {
    nil,                    //1
    ident, num, str, chr,    //4
    constsym, varsym, arraysym, ofsym, intsym, charsym, procsym, funcsym,  //8
    ifsym, thensym, elsesym, whilesym, dosym, forsym, tosym, bysym,     //8
    beginsym, endsym, readsym, writesym,    //4
    eql, neq, lss, leq, gtr, geq,   //6
    plussym, minussym, timessym, slashsym,  //4
    comma, colon, assign, semicolon, period,   //5
    lparen, rparen, lbracket, rbracket    //4
};

enum identtype {
    vartype, consttype, proctype, functype, errtype
};

enum datatype {
    nul, chartype, inttype, chararrtype, intarrtype
};

typedef union {
    int* intd;
    char* chard;
    int** intarr;
    char** chararr;
}identdata;

typedef struct identifierStruct {
    char name[MaxRes+1];
    identtype identt;
    datatype datat;
    int lv;
    int lengthOfArray;
    identdata* dataaddr;
    struct identifierStruct* next;
}identifier;
/*
&int : identifier->dataaddr->intd;
&char : identifier->dataaddr->chard;

&intarr : identifier->dataaddr->intarr;
&chararr : identifier->dataaddr->chararr;
length of arr : identifier->lengthOfArray;
*/
extern int lineNumber;
extern char ch;
extern char* symbolConst[NumRes];
extern int symbolTable[NumRes];
extern symbol sym;


extern int level;
extern int complexLevel;

extern char lsIdent[MaxRes + 1];
extern int lsNum;
extern char lsChar;
extern char lsStr[MaxStr + 1];

extern identifier *tableHead;
//extern identifier *tp;

void init(ifstream&);

bool isDigit(char);
bool isLetter(char ch);
bool isLetterOrDigit(char ch);

void transform(char* ch);

symbol adder(char c[]);
symbol adder(char ch);
void setSymbol(char c[]);
void setSymbol(char ch);

//operations of word table:
void addTable(char name[], identtype identt, datatype datat, int lv);
void addTable(char name[], identtype identt, datatype datat, int lv, int length);
void setData(char name[], int data);
void setData(char name[], char data);
void setData(char name[], int index, int data);
void setData(char name[], int index, char data);

int* getInt(identifier* identi);
char* getChar(identifier* identi);
int** getIntArray(identifier* identi);
char** getCharArray(identifier* identi);
int getLength(identifier* identi);
identtype getIdentType(char name[]);
datatype getDataType(char name[]);
int getDataLevel(char name[]);