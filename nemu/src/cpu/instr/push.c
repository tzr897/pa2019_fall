#include "cpu/instr.h"

static void instr_execute_1op()
{
    operand_read(&opr_src);

    cpu.esp-=data_size/8;

    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=opr_src.val;
    operand_write(&opr_dest);
}

make_instr_func(push_i_b)
{
    int new_data_size=8;
    opr_src.data_size=new_data_size;
    opr_src.type=OPR_IMM;
    opr_src.addr=cpu.eip+1;
    opr_src.sreg=SREG_CS;////
    
    operand_read(&opr_src);

    opr_src.val=sign_ext(opr_src.val,new_data_size);
    cpu.esp-=data_size/8;

    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=opr_src.val;//
    operand_write(&opr_dest);

    return 1+new_data_size/8;
}


make_instr_impl_1op(push, rm, v)
make_instr_impl_1op(push, r, v)
make_instr_impl_1op(push, i, v)
//