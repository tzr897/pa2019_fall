#include "cpu/instr.h"

static void instr_execute_1op() 
{
    operand_read(&opr_src);
    opr_src.val=sign_ext(opr_src.val,opr_src.data_size);
    opr_src.val=alu_add(1,opr_src.val,data_size);
	operand_write(&opr_src);

}

make_instr_impl_1op(inc, rm, b)
make_instr_impl_1op(inc, rm, v)
make_instr_impl_1op(inc, rm, bv)
make_instr_impl_1op(inc, r, b)
make_instr_impl_1op(inc, r, v)
make_instr_impl_1op(inc, r, bv)

