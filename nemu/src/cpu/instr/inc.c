#include "cpu/instr.h"

static void instr_execute_2op() 
{
    operand_read(&opr_dest);
    opr_dest.val=sign_ext(opr_dest.val,opr_dest.data_size);
    opr_dest.val++;
	operand_write(&opr_dest);

}

make_instr_impl_2op(inc, rm, b)
make_instr_impl_2op(inc, rm, v)
make_instr_impl_2op(inc, rm, bv)
make_instr_impl_2op(inc, r, b)
make_instr_impl_2op(inc, r, v)
make_instr_impl_2op(inc, r, bv)

