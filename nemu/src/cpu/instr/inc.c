#include "cpu/instr.h"

static void instr_execute_2op() 
{
    operand_read(&opr_dest);
    opr_dest.val=sign_ext(opr_dest.val,opr_dest.data_size);
    opr_dest.val++;
	operand_write(&opr_dest);

}

make_instr_impl_2op(add, r, rm, b)
make_instr_impl_2op(add, r, rm, v)
make_instr_impl_2op(add, rm, r, b)
make_instr_impl_2op(add, rm, r, v)
make_instr_impl_2op(add, i, rm, b)
make_instr_impl_2op(add, i, rm, v)
make_instr_impl_2op(add, i, rm, bv)
make_instr_impl_2op(add, i, r, b)
make_instr_impl_2op(add, i, r, v)
make_instr_impl_2op(add, a, o, b)
make_instr_impl_2op(add, a, o, v)
make_instr_impl_2op(add, i, a, b)
make_instr_impl_2op(add, i, a, v)