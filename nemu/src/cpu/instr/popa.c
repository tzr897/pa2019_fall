#include "cpu/instr.h"

make_instr_func(popa)
{
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.data_size=data_size;
    opr_dest.sreg=SREG_DS;
    operand_read(&opr_dest);
    cpu.edi=opr_dest.val;  
    cpu.esp+=data_size/8;


}