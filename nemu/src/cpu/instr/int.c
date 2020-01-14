#include "cpu/instr.h"

make_instr_func(int_)
{
    OPERAND i;
    i.type=OPR_IMM;
    i.addr=eip+1;
    i.data_size=data_size;
    i.sreg=SREG_CS;
    operand_read(&i);
    raise_sw_intr(i.val);
};