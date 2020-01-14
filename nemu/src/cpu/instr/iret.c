#include "cpu/instr.h"

make_instr_func(iret)
{
    //Pop EIP
	OPERAND p_eip;
	p_eip.data_size=data_size;
	p_eip.type=OPR_MEM;
	p_eip.addr=cpu.esp;
	p_eip.sreg=SREG_DS;
    operand_read(&p_eip);
    cpu.esp+=data_size/8;
	cpu.eip=p_eip.val;

    //Pop CS
    OPERAND p_cs;
	p_cs.data_size=data_size;
	p_cs.type=OPR_MEM;
	p_cs.addr=cpu.esp;
	p_cs.sreg=SREG_DS;
    operand_read(&p_cs);
    cpu.esp+=data_size/8;
	cpu.cs.val=p_cs.val;
    
    //Pop EFLAGS
    OPERAND p_eflags;
	p_eflags.data_size=data_size;
	p_eflags.type=OPR_MEM;
	p_eflags.addr=cpu.esp;
	p_eflags.sreg=SREG_DS;
    operand_read(&p_eflags);
    cpu.esp+=data_size/8;
	cpu.cs.val=p_eflags.val;
	
    return 0;
}