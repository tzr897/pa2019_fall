#ifndef __INSTR_MOV_H__
#define __INSTR_MOV_H__

make_instr_func(cmp_r2rm_b)
make_instr_func(cmp_r2rm_v)
make_instr_func(cmp_rm2r_b)
make_instr_func(cmp_rm2r_v)
make_instr_func(cmp_i2rm_b)
make_instr_func(cmp_i2rm_v)
make_instr_func(cmp_i2rm_bv)
make_instr_func(cmp_i2r_v)
make_instr_func(cmp_2rm_bv)





make_instr_impl_2op(cmp,r,rm,b)
make_instr_impl_2op(cmp,r,rm,v)
make_instr_impl_2op(cmp,rm,r,b)
make_instr_impl_2op(cmp,rm,r,v)
make_instr_impl_2op(cmp,i,rm,b)
make_instr_impl_2op(cmp,i,rm,v)
make_instr_impl_2op(cmp,i,rm,bv)

make_instr_impl_2op(cmp, i, a, b)
make_instr_impl_2op(cmp, i, a, v)

#endif