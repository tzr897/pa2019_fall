#include "cpu/instr.h"

static void instr_execute_2op() 
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    alu_and(opr_src,opr_dest,data_size);
    return 0;

}

make_instr_impl_2op(test, r, rm, b)
make_instr_impl_2op(test, r, rm, v)
make_instr_impl_2op(test, r, rm, bv)
make_instr_impl_2op(add, rm, r, b)
make_instr_impl_2op(add, rm, r, v)
make_instr_impl_2op(add, i, rm, b)
make_instr_impl_2op(add, i, rm, v)
make_instr_impl_2op(add, i, rm, bv)
make_instr_impl_2op(add, i, a, b)
make_instr_impl_2op(add, i, a, v)