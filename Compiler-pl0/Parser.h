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
void forStatement();
void callProcStatement();
void callFuncStatement();
void complexStatement();
void readStatement();
void writeStatement();
void blankStatement();

void actualParamList();
void condition();

void expression();
int term();
int factor();


void assignIt();
void assignIt(datatype dt);
void assignIt(datatype dt, int index);