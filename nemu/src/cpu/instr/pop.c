#include "cpu/instr.h"

static void instr_execute_1op()
{
    operand_read(&opr_dest);

    opr_src.type=OPR_MEM;
    opr_src.addr=cpu.esp;
    cpu.esp+=data_size/8;
    opr_src.sreg=SREG_DS;//
    opr_src.val=opr_dest.val;
    operand_write(&opr_src);

    
}

make_instr_impl_1op(pop, rm, v)
make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, i, v)
