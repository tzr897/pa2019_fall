#include "cpu/instr.h"

make_instr_func(call_near)
{
    OPERAND i1,i2;
    i1.data_size=data_size;
    i1.type=OPR_IMM;
    i1.addr=eip+1;
    i1.sreg=SREG_CS;
    operand_read(&i1);

    i2.data_size=


}