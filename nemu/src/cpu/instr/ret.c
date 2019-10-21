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
    cpu.eip+=i.val;
}

