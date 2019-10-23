#include "cpu/instr.h"

make_instr_func(call_near)
{
    int offset;
    OPERAND rel,i;
    rel.data_size=data_size;
    rel.type=OPR_IMM;
    rel.addr=eip+1;
    rel.sreg=SREG_CS;
    operand_read(&rel);

    i.data_size=data_size;
    i.type=OPR_MEM;
    cpu.esp-=4;
    i.addr=cpu.esp;
    i.sreg=SREG_SS;
    i.val=(eip+1)+data_size/8;
    operand_write(&i);
    offset=sign_ext(rel.val,data_size);
    cpu.eip+=offset+1+data_size/8;
    return 0;

}