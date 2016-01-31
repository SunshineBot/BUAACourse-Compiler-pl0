//Generator.h
//#include "definitions.h"

void g_gen(char cmd[], char op1[], char op2[], char op3[]);

void g_label(char label[]);
void g_label(char label[], int indexOfLabel);
void g_save(char name[]);
void g_load(char name[]);
void g_save_const(char name[]);
void g_saveExpReg();
void g_unsaveExpReg();
void g_saveConditionReg();
void g_unsaveConditionReg();
void g_saveForReg(char name[]);
void g_unsaveForReg(char name[]);
void g_saveCallReg(char name[]);
void g_unsaveCallReg();
void g_saveParam(int funcLevel, identtype it, expData data);
void g_resetParamCounter();

void g_add(char op1[], char op2[], char op3[]);
void g_add(char op1[], int op2, char op3[]);
void g_sub(char op1[], char op2[], char op3[]);
void g_sub(char op1[], int op2, char op3[]);
void g_rarray(char name[]);
void g_warray(char name[]);
void g_cmp(char cmd[], char label[]);
void g_j(char label[]);
void g_jal(char label[]);
void g_jr();
void g_read(char op1[]);
void g_write(datatype dt);
void g_write(char name[]);
void g_writeStr(char str[]);

void g_generate();