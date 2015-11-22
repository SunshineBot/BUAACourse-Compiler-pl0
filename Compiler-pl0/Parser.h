//Parser.h

extern int getSym();
extern void error(int, int);

void semiProgram();

void constDeclaration();
void constDefinition();
void constData();

void varDeclaration();
void varDefinition();

void type();
void baseType();

void procedureDeclaration();
void procedureHead();
void functionDeclaration();
void functionHead();
void paramList();

void statement();
void assignStatement();
void ifStatement();
void whileStatement();
void callProcStatement();
void callFuncStatement();
void complexStatement();
void readStatement();
void writeStatement();
void forStatement();
void blankStatement();
void realParamList();

void expression();
void term();
void factor();
void condition();


void assignIt(datatype dt);
void assignIt(datatype dt, int index);