#include "cpu/instr.h"

make_instr_func(leave)
{
    cpu.esp=cpu.ebp;

    OPERAND i;
    i.type=OPR_MEM;
    i.addr=cpu.ebp;
    i.sreg=SREG_DS;//
    operand_read(&i);
    cpu.ebp=i.val;
    
    //operand_write(&opr_dest);
    cpu.esp+=data_size/8;

    return 1;
}

