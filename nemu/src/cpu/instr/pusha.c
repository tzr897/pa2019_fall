#include "cpu/instr.h"

make_instr_func(pusha)
{
    //temp <- esp
    uint32_t temp=cpu.esp;

    cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=cpu.eax.val;
    operand_write(&opr_dest);
}