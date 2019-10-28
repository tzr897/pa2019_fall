#include "cpu/instr.h"

make_instr_func(ret_near)
{
    OPERAND i;
    i.data_size=data_size;
    i.type=OPR_MEM;
    i.addr=cpu.esp;
    i.sreg=SREG_DS;
    operand_read(&i);
    cpu.esp+=data_size/8;
    cpu.eip=i.val;

    return 0;
}


make_instr_func(ret_near_imm16)
{
    
    OPERAND i1,i2;
    i1.data_size=data_size;
    i1.type=OPR_MEM;
    i1.addr=cpu.esp;
    i1.sreg=SREG_DS;
    operand_read(&i1);
    cpu.esp+=data_size/8;
    cpu.eip=i1.val;

    i2.data_size=data_size;
    i2.type=OPR_IMM;
    i2.addr=cpu.eip+1;
    i2.sreg=SREG_CS;
    operand_read(&i2);
    cpu.esp+=data_size/8;
    cpu.eip=i2.val;

    // int offset;
    // OPERAND rel,i;
    // rel.data_size=data_size;
    // rel.type=OPR_IMM;
    // rel.addr=cpu.eip+1;
    // rel.sreg=SREG_CS;
    // operand_read(&rel);


    return 0;
}
