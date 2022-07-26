#include "cpu/instr.h"

make_instr_func(pusha)
{

    //temp <- esp
    uint32_t temp=cpu.esp;
    //eax
    cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=cpu.eax;
    operand_write(&opr_dest);
    //ecx
    cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=cpu.ecx;
    operand_write(&opr_dest);
    //edx
    cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=cpu.edx;
    operand_write(&opr_dest);
    //ebx
    cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=cpu.ebx;
    operand_write(&opr_dest);
    //temp
    cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=temp;
    operand_write(&opr_dest);
    //ebp
    cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=cpu.ebp;
    operand_write(&opr_dest);
    //esi
    cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=cpu.esi;
    operand_write(&opr_dest);
    //edi
    cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=cpu.edi;
    operand_write(&opr_dest);

    return 1;
}