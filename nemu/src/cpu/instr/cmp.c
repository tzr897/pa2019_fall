#include "cpu/instr.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
    opr_src.val=sign_ext(opr_src.val,opr_src.data_size);
    operand_read(&opr_dest);
	opr_dest.val = sign_ext(opr_dest.val,opr_dest.data_size);
	alu_sub(opr_src.val,opr_dest.val,data_size);
}

make_instr_impl_2op(cmp, r, rm, b)
make_instr_impl_2op(cmp, r, rm, v)
make_instr_impl_2op(, rm, r, b)
make_instr_impl_2op(mov, rm, r, v)
make_instr_impl_2op(mov, i, rm, b)
make_instr_impl_2op(mov, i, rm, v)
make_instr_impl_2op(mov, i, r, b)
make_instr_impl_2op(mov, i, r, v)
make_instr_impl_2op(mov, a, o, b)
make_instr_impl_2op(mov, a, o, v)
make_instr_impl_2op(mov, o, a, b)
make_instr_impl_2op(mov, o, a, v)