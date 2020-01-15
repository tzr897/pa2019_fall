#include "cpu/instr.h"

make_instr_func(popa)
{

    //edi
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.data_size=data_size;
    opr_dest.sreg=SREG_DS;
    operand_read(&opr_dest);
    cpu.edi=opr_dest.val;  
    cpu.esp+=data_size/8;
    //esi
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.data_size=data_size;
    opr_dest.sreg=SREG_DS;
    operand_read(&opr_dest);
    cpu.esi=opr_dest.val;  
    cpu.esp+=data_size/8;
    //ebp
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.data_size=data_size;
    opr_dest.sreg=SREG_DS;
    operand_read(&opr_dest);
    cpu.ebp=opr_dest.val;  
    cpu.esp+=data_size/8;
    //skip esp
    cpu.esp+=data_size/8;
    //ebx
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.data_size=data_size;
    opr_dest.sreg=SREG_DS;
    operand_read(&opr_dest);
    cpu.ebx=opr_dest.val;  
    cpu.esp+=data_size/8;
    //edx
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.data_size=data_size;
    opr_dest.sreg=SREG_DS;
    operand_read(&opr_dest);
    cpu.edx=opr_dest.val;  
    cpu.esp+=data_size/8;
    //ecx
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.data_size=data_size;
    opr_dest.sreg=SREG_DS;
    operand_read(&opr_dest);
    cpu.ecx=opr_dest.val;  
    cpu.esp+=data_size/8;
    //eax
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.data_size=data_size;
    opr_dest.sreg=SREG_DS;
    operand_read(&opr_dest);
    cpu.eax=opr_dest.val;  
    cpu.esp+=data_size/8;

    return 1;
}