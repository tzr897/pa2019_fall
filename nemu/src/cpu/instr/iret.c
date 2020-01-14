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
	
}