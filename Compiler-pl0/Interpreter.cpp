//Interperter.cpp

#include <iostream>
#include <iomanip>
#include "definitions.h"

void interpret() {
    if (errorAmount > 0) {
        cout << "Amount of Error is " << errorAmount << endl;
        return;
    }

    //ostream& fp = cout;
    ofstream fp;
    fp.open("result.txt");
    Mcode* pc;
    fp << left;
    fp << setw(10) << "add" << "$fp, $sp, $0" << endl;
    for (pc = McodeHead->next; pc != null; pc = pc->next) {
        if (!strcmp(pc->cmd, "label")) {
            fp << pc->op1 << endl;
        }
        else if (!strcmp(pc->cmd, "save")) {
            fp << setw(10) << "sw"
                << pc->op1 << ", "
                << pc->op3 << "("
                << pc->op2 << ")" << endl;
        }
        else if (!strcmp(pc->cmd, "load")) {
            fp << setw(10) << "lw"
                << pc->op1 << ", "
                << pc->op3 << "("
                << pc->op2 << ")" << endl;
        }
        else if (!strcmp(pc->cmd, "add") 
                || !strcmp(pc->cmd, "addi")
                || !strcmp(pc->cmd, "sub")
                || !strcmp(pc->cmd, "subi")
                || !strcmp(pc->cmd, "mul")
                || !strcmp(pc->cmd, "div")
                ) {
            fp << setw(10) << pc->cmd
                << pc->op3 << ", "
                << pc->op1 << ", "
                << pc->op2 << endl;
        }
        else if (!strcmp(pc->cmd, "neq")) {
            fp << setw(10) << "bne"
                << pc->op1 << ", "
                << pc->op2 << ", "
                << pc->op3 << endl;
        }
        else if (!strcmp(pc->cmd, "eql")) {
            fp << setw(10) << "beq"
                << pc->op1 << ", "
                << pc->op2 << ", "
                << pc->op3 << endl;
        }
        else if (!strcmp(pc->cmd, "geq")) {
            fp << setw(10) << "sub"
                << "$t4, $s0, $s1" << endl;
            fp << setw(10) << "bgez"
                << "$t4, "
                << pc->op3 << endl;
        }
        else if (!strcmp(pc->cmd, "gtr")) {
            fp << setw(10) << "sub"
                << "$t4, $s0, $s1" << endl;
            fp << setw(10) << "bgtz"
                << "$t4, "
                << pc->op3 << endl;
        }
        else if (!strcmp(pc->cmd, "leq")) {
            fp << setw(10) << "sub"
                << "$t4, $s0, $s1" << endl;
            fp << setw(10) << "blez"
                << "$t4, "
                << pc->op3 << endl;
        }
        else if (!strcmp(pc->cmd, "lss")) {
            fp << setw(10) << "sub"
                << "$t4, $s0, $s1" << endl;
            fp << setw(10) << "bltz"
                << "$t4, "
                << pc->op3 << endl;
        }
        else if (!strcmp(pc->cmd, "j")
                || !strcmp(pc->cmd, "jal")
                || !strcmp(pc->cmd, "jr")) {
            fp << setw(10) << pc->cmd
                << pc->op1 << endl;
        }
        else if (!strcmp(pc->cmd,"syscall")) {
            fp << setw(10) << pc->cmd << endl;
        }
    }
    fp.close();
}