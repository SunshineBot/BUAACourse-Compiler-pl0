//Generator.cpp
#include "Generator.h"
//#include "definitions.h"
#include "TableMgr.h"

int paramCounter = 0;

extern void printMcode() {
    pc = McodeHead->next;
    Mcode * ppc;
    while (pc != null) {
        printf("%-10s%-1s,%-1s,%-1s\n", pc->cmd, pc->op1, pc->op2, pc->op3);
        ppc = pc;
        pc = pc->next;
    }
}

void g_gen(char cmd[], char op1[], char op2[], char op3[]) {
    //pc->next = (Mcode*)malloc(sizeof(Mcode));
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, cmd);
    sprintf_s(pc->op1, op1);
    sprintf_s(pc->op2, op2);
    sprintf_s(pc->op3, op3);

}
void g_label(char label[]) {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "label");
    sprintf_s(pc->op1, "%s:", label);
    sprintf_s(pc->op2, "");
    sprintf_s(pc->op3, "");
}
void g_label(char label[], int indexOfLabel) {
    char t[30];
    sprintf_s(t, "%s_%d:", label, indexOfLabel);
    g_gen("label", t, "", "");
    //pc->next = new Mcode();
    //pc = pc->next;
    //pc->next = null;
    //sprintf_s(pc->cmd, "label");
    //sprintf_s(pc->op1, t);
    //sprintf_s(pc->op2, "");
    //sprintf_s(pc->op3, "");
}
void g_save(char name[], char srcReg[]) {
    const identifier* tp = getReadTableItem(name);
    if (tp->identt != paramvartype) {
        if (level == tp->lv) {
            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "save");
            sprintf_s(pc->op1, srcReg);
            sprintf_s(pc->op2, "$sp");
            sprintf_s(pc->op3, "-%d", tp->offset);
        }
        else {
            //int display_offset = (level - tp->lv) * 4;
            int display_offset = tp->lv * 4;
            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "load");
            sprintf_s(pc->op1, "$t0");
            sprintf_s(pc->op2, "$fp");
            sprintf_s(pc->op3, "-%d", tp->lv * 4);

            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "save");
            sprintf_s(pc->op1, srcReg);
            sprintf_s(pc->op2, "$t0");
            sprintf_s(pc->op3, "-%d", tp->offset);
        }
    }
    else {
        pc->next = new Mcode();
        pc = pc->next;
        pc->next = null;
        sprintf_s(pc->cmd, "load");
        sprintf_s(pc->op1, "$t1");
        sprintf_s(pc->op2, "$sp");
        sprintf_s(pc->op3, "-%d", tp->offset);

        pc->next = new Mcode();
        pc = pc->next;
        pc->next = null;
        sprintf_s(pc->cmd, "save");
        sprintf_s(pc->op1, srcReg);
        sprintf_s(pc->op2, "$t1");
        sprintf_s(pc->op3, "-%d", 0);
    }
}
void g_save(char name[]) {
    g_save(name, "$t9");
}
void g_load(char name[], char targetReg[]) {
    const identifier* tp = getReadTableItem(name);
    if (tp->identt != paramvartype) {
        if (level == tp->lv) {
            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "load");
            sprintf_s(pc->op1, targetReg);
            sprintf_s(pc->op2, "$sp");
            sprintf_s(pc->op3, "-%d", tp->offset);
        }
        else {
            //int display_offset = (level - tp->lv) * 4;
            int display_offset = tp->lv * 4;
            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "load");
            sprintf_s(pc->op1, "$t0");  //variable in display
            sprintf_s(pc->op2, "$fp");
            sprintf_s(pc->op3, "-%d", tp->lv * 4);

            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "load");
            sprintf_s(pc->op1, targetReg);
            sprintf_s(pc->op2, "$t0");
            sprintf_s(pc->op3, "-%d", tp->offset);
        }
    }
    else {
        if (level == tp->lv) {
            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "load");
            sprintf_s(pc->op1, "$t1");  //parameter by Ref
            sprintf_s(pc->op2, "$sp");
            sprintf_s(pc->op3, "-%d", tp->offset);

            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "load");
            sprintf_s(pc->op1, targetReg);
            sprintf_s(pc->op2, "$t1");
            sprintf_s(pc->op3, "-%d", 0);
        }
        else {
            //int display_offset = (level - tp->lv) * 4;
            int display_offset = tp->lv * 4;
            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "load");
            sprintf_s(pc->op1, "$t0");  //variable in display
            sprintf_s(pc->op2, "$fp");
            sprintf_s(pc->op3, "-%d", display_offset);

            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "load");
            sprintf_s(pc->op1, "$t1");  //parameter by Ref
            sprintf_s(pc->op2, "$t0");
            sprintf_s(pc->op3, "-%d", tp->offset);

            pc->next = new Mcode();
            pc = pc->next;
            pc->next = null;
            sprintf_s(pc->cmd, "load");
            sprintf_s(pc->op1, targetReg);
            sprintf_s(pc->op2, "$t1");
            sprintf_s(pc->op3, "-%d", 0);
        }
    }
}
void g_load(char name[]) {
    g_load(name, "$t7");
}
void g_save_const(char name[]) {
    const identifier* tp = getReadTableItem(name);
    int data;
    switch (tp->datat) {
        case chartype:
            data = getChar(tp);
            break;
        case inttype:
            data = getInt(tp);
            break;
        default:
            break;
    }
    g_add("$0", data, "$t9");

    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, "$t9");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", tp->offset);
}
void g_saveExpReg() {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, "$t8");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);
    offset += 4;

    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, "$t9");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);
    offset += 4;
}
void g_unsaveExpReg() {
    offset -= 4;
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "load");
    sprintf_s(pc->op1, "$t9");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);

    offset -= 4;
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "load");
    sprintf_s(pc->op1, "$t8");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);
}
void g_saveConditionReg() {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, "$s0");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);
    offset += 4;

    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, "$s1");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);
    offset += 4;
}
void g_unsaveConditionReg() {
    offset -= 4;
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "load");
    sprintf_s(pc->op1, "$s1");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);

    offset -= 4;
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "load");
    sprintf_s(pc->op1, "$s0");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);
}
void g_saveForReg(char name[]) {
    const identifier* tp = getReadTableItem(name);
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, "$s0");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", tp->offset);

    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, "$s1");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);
    offset += 4;
}
void g_unsaveForReg(char name[]) {
    const identifier* tp = getReadTableItem(name);
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "load");
    sprintf_s(pc->op1, "$s0");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", tp->offset);

    offset -= 4;
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "load");
    sprintf_s(pc->op1, "$s1");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);
}
void g_saveReg(char reg[]) {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, reg);
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);
    offset += 4;
}
void g_unsaveReg(char reg[]) {
    static int offset_t = 0;
    if (offset_t == 56)
        offset_t = 0;
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "load");
    sprintf_s(pc->op1, reg);
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset_t);
    offset_t += 4;
}
void g_saveFP(int fp_offset) {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "load");
    sprintf_s(pc->op1, "$t0");
    sprintf_s(pc->op2, "$fp");
    sprintf_s(pc->op3, "-%d", fp_offset);

    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, "$t0");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset);
    offset+=4;
}
void g_saveCallReg(char name[]) {
    const identifier* tp;
    tp = getReadTableItem(name);
    //int lv = tp->lv;
    //$fp-Reg
    int fp_offset = offset;
    int i;
    for (i = 0; i <= tp->lv && i < level; i++) {
        g_saveFP(i * 4);
    }
    if (tp->lv == level) {
        g_saveReg("$sp");
    }
    int sp_offset = offset;
    //$sp-Reg
    g_saveReg("$v0");
    g_saveReg("$t8");
    g_saveReg("$t9");
    g_saveReg("$s0");
    g_saveReg("$s1");
    g_saveReg("$s2");
    g_saveReg("$s3");
    g_saveReg("$s4");
    g_saveReg("$s5");
    g_saveReg("$s6");
    g_saveReg("$s7");
    g_saveReg("$ra");
    g_saveReg("$fp");
    g_saveReg("$sp");

    //fresh $fp & $sp pointer.
    g_sub("$sp", fp_offset, "$fp");
    g_sub("$sp", sp_offset, "$sp");

    offset = 56;
}
void g_unsaveCallReg() {
    //14 * 4 = 56
    g_unsaveReg("$v0");
    g_unsaveReg("$t8");
    g_unsaveReg("$t9");
    g_unsaveReg("$s0");
    g_unsaveReg("$s1");
    g_unsaveReg("$s2");
    g_unsaveReg("$s3");
    g_unsaveReg("$s4");
    g_unsaveReg("$s5");
    g_unsaveReg("$s6");
    g_unsaveReg("$s7");
    g_unsaveReg("$ra");
    g_unsaveReg("$fp");
    g_unsaveReg("$sp");
}
void g_saveParam(int funcLevel, identtype it, expData data) {
    //paramCounter++;
    const identifier* tp = getReadTableItem(data.name);
    if (it == paramvartype) {
        if (data.type == expParamVar) {
            if (level == tp->lv) {      //本层变量作为传址参数
                pc->next = new Mcode();
                pc = pc->next;
                pc->next = null;
                sprintf_s(pc->cmd, "load");
                sprintf_s(pc->op1, "$t9");
                sprintf_s(pc->op2, "$sp");
                sprintf_s(pc->op3, "-%d", tp->offset);
            }
            else {                          //外层变量作为传址参数
                //int display_offset = (level - tp->lv) * 4;  //从不本层display区寻找变量基址
                int display_offset = tp->lv * 4;
                pc->next = new Mcode();
                pc = pc->next;
                pc->next = null;
                sprintf_s(pc->cmd, "load");
                sprintf_s(pc->op1, "$t0");  //variable in display
                sprintf_s(pc->op2, "$fp");
                sprintf_s(pc->op3, "-%d", display_offset);

                pc->next = new Mcode();
                pc = pc->next;
                pc->next = null;
                sprintf_s(pc->cmd, "load");
                sprintf_s(pc->op1, "$t9");
                sprintf_s(pc->op2, "$t0");
                sprintf_s(pc->op3, "-%d", tp->offset);

            }
        }
        else if(data.type == expArray) {
            g_add("$t2", "$0", "$t9");
        }
        else {
            //$sp/$fp+offset
            if (level == tp->lv) {
                g_sub("$sp", tp->offset, "$t9");
            }
            else {
                //int display_offset = (level - tp->lv) * 4;
                int display_offset = tp->lv * 4;
                pc->next = new Mcode();
                pc = pc->next;
                pc->next = null;
                sprintf_s(pc->cmd, "load");
                sprintf_s(pc->op1, "$t0");  //variable in display
                sprintf_s(pc->op2, "$fp");
                sprintf_s(pc->op3, "-%d", display_offset);

                g_sub("$t0", tp->offset, "$t9");
            }

            
        }
    }
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, "$t9");
    sprintf_s(pc->op2, "$sp");
    sprintf_s(pc->op3, "-%d", offset + 56 + (funcLevel + 1 + paramCounter) * 4);
    //offset += 4;
    paramCounter++;
}
void g_resetParamCounter() {
    paramCounter = 0;
}

void g_add(char op1[], char op2[], char op3[]) {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "add");
    sprintf_s(pc->op1, op1);
    sprintf_s(pc->op2, op2);
    sprintf_s(pc->op3, op3);
}

void g_add(char op1[], int op2, char op3[]) {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "addi");
    sprintf_s(pc->op1, op1);
    sprintf_s(pc->op2, "%d", op2);
    sprintf_s(pc->op3, op3);
}
void g_sub(char op1[], char op2[], char op3[]) {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "sub");
    sprintf_s(pc->op1, op1);
    sprintf_s(pc->op2, op2);
    sprintf_s(pc->op3, op3);
}
void g_sub(char op1[], int op2, char op3[]) {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "subi");
    sprintf_s(pc->op1, op1);
    sprintf_s(pc->op2, "%d", op2);
    sprintf_s(pc->op3, op3);
}

void g_rarray(char name[]) {
    //$op3 = $op1[$op2]
    const identifier* tp = getReadTableItem(name);
    
    g_add("$0", 4, "$t3");
    g_gen("mul", "$s7", "$t3", "$s7");  //数组内偏移量-$s7
    g_add("$s7", tp->offset, "$s7");    //实际偏移量 = 首地址偏移量 + 下标 * 元素长度（4）
    if (tp->lv == level) {
        g_sub("$sp", "$s7", "$t2");
    }
    else {
        pc->next = new Mcode();
        pc = pc->next;
        pc->next = null;
        sprintf_s(pc->cmd, "load");
        sprintf_s(pc->op1, "$t0");
        sprintf_s(pc->op2, "$fp");
        sprintf_s(pc->op3, "-%d", tp->lv * 4);

        g_sub("$t0", "$s7", "$t2");
    }
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "load");
    sprintf_s(pc->op1, "$t7");
    sprintf_s(pc->op2, "$t2");
    sprintf_s(pc->op3, "0");
}

void g_warray(char name[]) {
    const identifier* tp = getReadTableItem(name);
    g_add("$0", 4, "$t3");
    g_gen("mul", "$s6", "$t3", "$s6");
    g_add("$s6", tp->offset, "$s6");    //实际偏移量 = 首地址偏移量 + 下标 * 元素长度（4）
    if (tp->lv == level) {
        g_sub("$sp", "$s6", "$t2");
    }
    else {
        pc->next = new Mcode();
        pc = pc->next;
        pc->next = null;
        sprintf_s(pc->cmd, "load");
        sprintf_s(pc->op1, "$t0");
        sprintf_s(pc->op2, "$fp");
        sprintf_s(pc->op3, "-%d", tp->lv * 4);

        g_sub("$t0", "$s6", "$t2");
    }
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "save");
    sprintf_s(pc->op1, "$t9");
    sprintf_s(pc->op2, "$t2");
    sprintf_s(pc->op3, "0");
    
}

void g_cmp(char cmd[], char label[]) {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, cmd);
    sprintf_s(pc->op1, "$s0");
    sprintf_s(pc->op2, "$s1");
    sprintf_s(pc->op3, label);
}
void g_j(char label[]) {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "j");
    sprintf_s(pc->op1, label);
    sprintf_s(pc->op2, "");
    sprintf_s(pc->op3, "");
}
void g_jal(char label[]) {
    const identifier* tp = getReadTableItem(label);
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "jal");
    sprintf_s(pc->op1, "%s_%d", tp->name, tp->offset);
    sprintf_s(pc->op2, "");
    sprintf_s(pc->op3, "");

}
void g_jr() {
    pc->next = new Mcode();
    pc = pc->next;
    pc->next = null;
    sprintf_s(pc->cmd, "jr");
    sprintf_s(pc->op1, "$ra");
    sprintf_s(pc->op2, "");
    sprintf_s(pc->op3, "");
}

void g_read(char name[]) {
    const identifier* tp = getReadTableItem(name);
    if (tp->datat == inttype) {
        g_add("$0", 5, "$v0");
        g_gen("syscall", "", "", "");
        g_save(name, "$v0");
    }
    else if (tp->datat == chartype) {
        g_add("$0", 12, "$v0");
        g_gen("syscall", "", "", "");
        g_save(name, "$v0");
    }
}
void g_write(datatype dt) {
    if (dt == inttype) {
        g_add("$0", 1, "$v0");
    }
    else {
        g_add("$0", 11, "$v0");
    }
    g_add("$t9", 0, "$a0");
    g_gen("syscall", "", "", "");
}
void g_write(char name[]) {
    const identifier* tp = getReadTableItem(name);
    if (tp->datat == inttype ||tp->datat == intarrtype) {
        g_write(inttype);
    }
    else if (tp->datat == chartype || tp->datat == chararrtype) {
        g_write(chartype);
    }
}
void g_writeStr(char str[]) {
    g_add("$0", 11, "$v0");
    int c;
    for (int i = 0; str[i] != '\0'; i++) {
        c = str[i];
        g_add("$0", c, "$a0");
        g_gen("syscall", "", "", "");
    }
}