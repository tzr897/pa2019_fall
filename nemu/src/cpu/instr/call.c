#include "cpu/instr.h"

make_instr_func(call_near)
{
    OPERAND i1,i2;
    i1.data_size=data_size;
    i1.type=OPR_IMM;
    i1.addr=eip+1;
    i1.sreg=SREG_CS;
    operand_read(&i1);

    i2.data_size=data_size;
    i2.type=OPR_MEM;
    cpu.esp-=4;
    i2.addr=cpu.esp;
    i2.sreg=SREG_SS;
    i2.val=(eip+1)+data_size/8;
    operand_write(&i2);

    cpu.eip+=sign_ext(i1.val,data_size)+1+data_size/8;
    return 0;

}