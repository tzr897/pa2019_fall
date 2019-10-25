#include "cpu/instr.h"

make_instr_func(leave)
{
    cpu.esp=cpu.ebp;
    
    OPERAND i;
    i.type=OPR_MEM;
    i.data_size=data_size;
    i.addr=cpu.esp;
    i.sreg=SREG_DS;//
    operand_read(&i);
    cpu.ebp=i.val;
    cpu.esp+=data_size/8;

    return 1;
}

/*
#include "cpu/instr.h"

static void instr_execute_1op()
{
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.data_size=data_size;
    opr_dest.sreg=SREG_DS;//
    operand_read(&opr_dest);

    opr_src.val=opr_dest.val;
    
    operand_write(&opr_src);
    cpu.esp+=data_size/8;
    
}

make_instr_impl_1op(pop, rm, v)
make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, i, v)

 */