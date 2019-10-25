#include "cpu/instr.h"

make_instr_func(leave)
{
    cpu.esp=cpu.ebp;

    OPERAND i;
    i.type=OPR_MEM;
    i.addr=cpu.esp;
    i.sreg=SREG_DS;//
    operand_read(&i);
    cpu.ebp=i.val;
    
    //operand_write(&opr_dest);
    cpu.esp+=data_size/8;

    return 1;
}

// opr_dest.type=OPR_MEM;
//     opr_dest.addr=cpu.esp;
//     opr_dest.sreg=SREG_DS;//
//     operand_read(&opr_dest);

//     opr_src.val=opr_dest.val;
    
//     operand_write(&opr_src);
//     cpu.esp+=data_size/8;