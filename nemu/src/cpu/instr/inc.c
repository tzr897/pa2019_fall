#include "cpu/instr.h"

static void instr_execute_1op() 
{
    operand_read(&opr_dest);
    opr_dest.val=sign_ext(opr_dest.val,opr_dest.data_size);
    opr_dest.val=alu_add(1,opr_dest.val,data_size);
	operand_write(&opr_dest);

}

make_instr_impl_1op(inc, rm, b)
make_instr_impl_1op(inc, rm, v)
make_instr_impl_1op(inc, rm, bv)
make_instr_impl_1op(inc, r, b)
make_instr_impl_1op(inc, r, v)
make_instr_impl_1op(inc, r, bv)

