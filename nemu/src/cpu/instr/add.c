#include "cpu/instr.h"

static void instr_execute_2op() 
{
    operand_read(&opr_src);
    opr_src.val=sign_ext(opr_src.val,opr_src.data_size);

    operand_read(&opr_dest);
    opr_dest.val=sign_ext(opr_dest.val,opr_dest.data_size);

    opr_dest.val=alu_add(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);

}

make_instr_impl_2op(add)