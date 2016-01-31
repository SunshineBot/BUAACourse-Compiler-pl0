//TableMgr.h

//operations of word table:
void printWordTable();
void printLevelWordTable();

identifier* getTableItem(char name[]);
const identifier* getReadTableItem(char name[]);
void addTable(char name[], identtype identt, datatype datat, int data, int lv);
void addTable(char name[], identtype identt, int lv);
void addTable(char name[], int lv, int length);
void setDataType(char name[], datatype datat);
void setFuncDataType(char name[], datatype datat);
void setDataType(char name[], datatype datat, int length);
//void setData(char name[], int data);
//void setData(char name[], char data);
//void setData(char name[], int index, int data);
//void setData(char name[], int index, char data);
void setParamLengthAndIndex(char name[], int paramLength, int indexOfLabel);

int getInt(char name[]);
int getInt(const identifier*);
char getChar(char name[]);
char getChar(const identifier*);
int getInt(char name[], int index);
int getInt(const identifier*, int);
char getChar(char name[], int index);
char getChar(const identifier*, int);
//int getLength(char name[]);
identtype getIdentType(char name[]);
datatype getDataType(char name[]);
int getDataLevel(char name[]);
//int getOffset(char name[]);

void deleteCurrentLvWord();