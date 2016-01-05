//TableMgr.cpp
#include "definitions.h"
#include "TableMgr.h"
//operations of word table:

void printWordTable() {
    identifier* tp = tableHead->next;
    printf("\n");
    while (tp != null) {
        printf("table->name : %s\n", tp->name);
        printf("table->identtype : %d\n", tp->identt);
        printf("table->datatype : %d\n", tp->datat);
        printf("table->level : %d\n", tp->lv);
        printf("table->offset : %d\n", tp->offset);
        printf("table->length : %d\n\n", tp->length);
        tp = tp->next;
    }
}
void printLevelWordTable() {
    identifier* tp = tableHead->next;
    printf("\n");
    printf("Word Table of level %d\n", level);
    while (tp != null) {
        if (tp->lv <= level) {
            printf("table->name : %s\n", tp->name);
            printf("table->identtype : %d\n", tp->identt);
            printf("table->datatype : %d\n", tp->datat);
            printf("table->level : %d\n", tp->lv);
            printf("table->offset : %d\n", tp->offset);
            printf("table->length : %d\n\n", tp->length);
        }

        tp = tp->next;
    }
}

//identifier* getTableItem(char name[]);
const identifier* getReadTableItem(char name[]) {
    return getTableItem(name);
}
identifier* getTableItem(char name[]) {
    identifier* p = tableHead->next;
    identifier* sp = null;
    while (p != null) {
        if (!strcmp(p->name, name))
            sp = p;
        p = p->next;
    }
    return sp;
}
void addTable(char name[], identtype identt, datatype datat, int data, int lv) {
    //add const.
    addTable(name, identt, lv);
    identifier *tp;
    tp = getTableItem(name);
    tp->datat = datat;
    tp->offset = offset;
    offset += 4;
    tp->dataaddr = (identdata*)malloc(sizeof(identdata));
    if (datat == inttype) {
        tp->dataaddr->intd = (int*)malloc(sizeof(int));
        *tp->dataaddr->intd = data;
    }
    else if (datat == chartype) {
        tp->dataaddr->chard = (char*)malloc(sizeof(char));
        *tp->dataaddr->chard = data;
    }
}
void addTable(char name[], identtype identt, int lv) {
    //add variable/proc/func/param
    identifier *tp;
    tp = tableHead;
    while (tp->next != null) {
        tp = tp->next;
    }
    tp->next = new identifier();
    tp = tp->next;
    if (identt == paramtype || identt == paramvartype) {
        tp->lv = lv + 1;
    }
    else {
        tp->lv = lv;
    }
    sprintf_s(tp->name, MaxRes, "%s", name);
    tp->identt = identt;
    tp->dataaddr = null;
    tp->next = null;
}
void addTable(char name[], int lv, int length) {
    //add array.
    identifier *tp;
    tp = tableHead;
    while (tp->next != null) {
        tp = tp->next;
    }
    tp->next = new identifier();
    tp = tp->next;
    tp->lv = lv;
    tp->length = length;
    sprintf_s(tp->name, MaxRes, name);
    tp->identt = vartype;
    tp->dataaddr = null;
    tp->next = null;
}
void setDataType(char name[], datatype datat) {
    identifier *tp;
    tp = getTableItem(name);
    while (tp != null) {
        tp->datat = datat;
        tp->offset = offset;
        if (tp->identt == proctype || tp->identt == functype) {
            offset += 0;
        }
        else if (tp->identt == vartype || tp->identt == paramtype || tp->identt == paramvartype) {
            switch (datat) {
                case chartype:
                    offset += 4;
                    break;
                case inttype:
                    offset += 4;
                    break;
                default:
                    break;
            }
        }
        tp = tp->next;
    }
}
void setFuncDataType(char name[], datatype datat) {
    identifier *tp;
    tp = getTableItem(name);
    
    if (tp != null) {
        tp->datat = datat;
        //if (tp->identt == proctype) {
        //    offset += 0;
        //}
        //else if (tp->identt == functype || tp->identt == vartype || tp->identt == paramtype) {
        //    switch (datat) {
        //        case chartype:
        //            offset += 1;
        //            break;
        //        case inttype:
        //            offset += 4;
        //            break;
        //            //case chararrtype:
        //            //    offset += tp->length;
        //            //    break;
        //            //case intarrtype:
        //            //    offset += tp->length * 4;
        //            //    break;
        //        default:
        //            break;
        //    }
        //}
    }
}
void setDataType(char name[], datatype datat, int length) {
    identifier *tp;
    tp = getTableItem(name);
    while (tp != null) {
        tp->datat = datat;
        tp->length = length;
        tp->offset = offset;
        if (tp->identt == proctype) {
            offset += 0;
        }
        else if (tp->identt == functype || tp->identt == vartype) {
            switch (datat) {
                    case chararrtype:
                        offset += tp->length * 4;
                        break;
                    case intarrtype:
                        offset += tp->length * 4;
                        break;
                default:
                    break;
            }
        }
        tp = tp->next;
    }
}
void setData(char name[], int data) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp == null) {
        error(10, lineNumber);   //identifier not found.
        return;
    }
    if (tp->identt == functype || tp->identt == vartype) {
        if (tp->datat == inttype) {
            if (tp->dataaddr == null) {
                tp->dataaddr = (identdata*)malloc(sizeof(identdata));
                tp->dataaddr->intd = (int*)malloc(sizeof(int));
            }
            tp->dataaddr->intd = &data;
        }
        else {
            error(16, lineNumber);   //变量数据类型不对, an integer is needed.
        }
    }
    else {
        error(37, lineNumber);   //identifier type is wrong, function or variable is needed.
    }
}
void setData(char name[], char data) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp == null) {
        error(10, lineNumber);   //identifier not found.
        return;
    }
    if (tp->identt == functype || tp->identt == vartype) {
        if (tp->datat == chartype) {
            if (tp->dataaddr == null) {
                tp->dataaddr = (identdata*)malloc(sizeof(identdata));
                tp->dataaddr->chard = (char*)malloc(sizeof(char));
            }
            tp->dataaddr->chard = &data;
        }
        else {
            error(16, lineNumber);   //变量数据类型不对, an integer is needed.
        }
    }
    else {
        error(37, lineNumber);   //identifier type is wrong, function or variable is needed.
    }
}
void setData(char name[], int index, int data) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp == null) {
        error(10, lineNumber);   //identifier not found.
        return;
    }
    if (index >= tp->length) {
        error(38, lineNumber);   //out of index bound.
        return;
    }
    if (tp->identt == functype || tp->identt == vartype) {
        if (tp->datat == intarrtype) {
            if (tp->dataaddr == null) {
                tp->dataaddr = (identdata*)malloc(sizeof(identdata));
                tp->dataaddr->intarr = (int*)malloc(tp->length * sizeof(int));
            }
            tp->dataaddr->intarr[index] = data;
        }
        else {
            error(16, lineNumber);   //变量数据类型不对, an integer is needed.
        }
    }
    else {
        error(37, lineNumber);   //identifier type is wrong, function or variable is needed.
    }
}
void setData(char name[], int index, char data) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp == null) {
        error(10, lineNumber);   //identifier not found.
        return;
    }
    if (index >= tp->length) {
        error(38, lineNumber);   //out of index bound.
        return;
    }
    if (tp->identt == functype || tp->identt == vartype) {
        if (tp->datat == chararrtype) {
            if (tp->dataaddr == null) {
                tp->dataaddr = (identdata*)malloc(tp->length * sizeof(identdata));
                tp->dataaddr->chararr = (char*)malloc(tp->length * sizeof(char));
            }
            tp->dataaddr->chararr[index] = data;
        }
        else {
            error(37, lineNumber);   //identifier type is wrong, function or variable is needed.
        }
    }
    else {
        error(0, lineNumber);   //identifier type is wrong, variable type is needed.
    }
}
void setParamLengthAndIndex(char name[], int paramLength, int indexOfLabel) {
    identifier* tp = getTableItem(name);
    if (tp != null && (tp->identt == functype || tp->identt == proctype)) {
        tp->length = paramLength;
        tp->offset = indexOfLabel;
    }
}


int getInt(char name[]) {
    identifier* identi = getTableItem(name);
    return getInt(identi);
}
int getInt(const identifier* tp) {
    if (tp == null) {
        return 0;
    }
    return *tp->dataaddr->intd;
}
char getChar(char name[]) {
    identifier* identi = getTableItem(name);
    return getChar(identi);
}
char getChar(const identifier* tp) {
    if (tp == null) {
        return 0;
    }
    return *tp->dataaddr->chard;
}
int getInt(char name[], int index) {
    identifier* identi = getTableItem(name);
    return getInt(identi, index);
}
int getInt(const identifier* tp, int index) {
    if (tp == null) {
        return 0;
    }
    return tp->dataaddr->intarr[index];
}
char getChar(char name[], int index) {
    identifier* identi = getTableItem(name);
    return getChar(identi, index);
}
char getChar(const identifier* tp, int index) {
    if (tp == null) {
        return 0;
    }
    return tp->dataaddr->chararr[index];
}
int getData(char name[]) {
    identifier* identi = getTableItem(name);
    if (identi == null || identi->dataaddr == null) {
        return 0;
    }
    switch (identi->datat) {
        case inttype:
            return (int)*identi->dataaddr->intd;
        case chartype:
            return (int)*identi->dataaddr->chard;
        default:
            return 0;
            break;
    }
}
int getData(char name[], int index) {
    identifier* identi = getTableItem(name);
    if (identi == null || identi->dataaddr == null) {
        return 0;
    }
    switch (identi->datat) {
        case intarrtype:
            return (int)identi->dataaddr->intarr[index];
        case chartype:
            return (int)identi->dataaddr->chararr[index];
        default:
            return 0;
            break;
    }
}
int getLength(const identifier* tp) {
    if (tp == null) {
        return 0;
    }
    return tp->length;
}
int getLength(char name[]) {
    identifier* identi = getTableItem(name);
    return getLength(identi);
}

identtype getIdentType(const identifier* tp) {
    if (tp != null) {
        return tp->identt;
    }
    else {
        return errtype;
    }
}
identtype getIdentType(char name[]) {
    identifier *tp;
    tp = getTableItem(name);
    return getIdentType(tp);
}

datatype getDataType(const identifier* tp) {
    if (tp != null) {
        return tp->datat;
    }
    else {
        return nul;
    }
}
datatype getDataType(char name[]) {
    identifier *tp;
    tp = getTableItem(name);
    return getDataType(tp);
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
int getOffset(char name[]) {
    identifier *tp;
    tp = getTableItem(name);
    if (tp != null) {
        return tp->offset;
    }
    else {
        return 0;
    }
}

void deleteCurrentLvWord() {
    identifier* p = tableHead;
    identifier* tp = null;
    while (p->next != null && (p->next->lv < level 
            || p->next->lv == level 
                && (p->next->identt == paramtype || p->next->identt == paramvartype))) {
        if (p->next->lv == level
            && (p->next->identt == paramtype || p->next->identt == paramvartype)) {
            sprintf_s(p->next->name, "_%s", p->next->name);
        }
        p = p->next;
    }
    if (p->next == null) {
        return;
    }
    tp = p->next;
    p->next = null;
    while (tp != null) {
        p = tp;
        tp = tp->next;
        delete p;
    }
}
