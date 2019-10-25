#include "cpu/instr.h"

static void instr_execute_1op()
{
    operand_read(&opr_dest);
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_DS;//
    
    
    opr_src.val=opr_dest.val;
    operand_write(&opr_src);
    cpu.esp+=data_size/8;
    
}

make_instr_impl_1op(pop, rm, v)
make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, i, v)
