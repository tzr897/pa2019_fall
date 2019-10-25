#include "cpu/instr.h"

static void instr_execute_1op()
{
    
    /////////////////////////
    
    opr_src.type=OPR_MEM;

    //////////////////
    opr_src.addr=cpu.esp;
    operand_read(&opr_dest);   
    opr_src.sreg=SREG_DS;//
    opr_src.val=opr_dest.val;
    //////////////////////
    operand_write(&opr_src);
    cpu.esp+=data_size/8;

}

make_instr_impl_1op(pop, rm, v)
make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, i, v)
