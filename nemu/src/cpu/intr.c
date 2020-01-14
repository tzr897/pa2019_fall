#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	// printf("Please implement raise_intr()");
	// assert(0);

// Trigger an exception/interrupt with 'intr_no'
// 'intr_no' is the index to the IDT

/*
	operand_read(&opr_src);

    cpu.esp-=data_size/8;

    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    
    opr_dest.sreg=SREG_DS;//
    opr_dest.val=opr_src.val;
    operand_write(&opr_dest);
 */
//Push EFLAGS
	OPERAND p_eflags;
	p_eflags.data_size=data_size;
	cpu.esp-=data_size/8;
	p_eflags.addr=cpu.esp;
	p_eflags.sreg=SREG_DS;
	p_eflags.val=cpu.eflags.val;
	operand_write(&p_eflags);

//Push CS
	OPERAND p_cs;
	p_cs.data_size=data_size;
	cpu.esp-=data_size/8;
	p_cs.addr=cpu.esp;
	p_cs.sreg=SREG_DS;
	p_cs.val=cpu.cs;
	operand_write(&p_cs);

//Push EIP
	OPERAND p_eip;
	p_eip.data_size=data_size;
	cpu.esp-=data_size/8;
	p_eip.addr=cpu.esp;
	p_eip.sreg=SREG_DS;
	p_eip.val=cpu.eip;
	operand_write(&p_eip);


// Find the IDT entry using 'intr_no'


// Clear IF if it is an interrupt
	if(intr_no==14)
	{
		cpu.eflags.if=0;
	}

// Set EIP to the entry of the interrupt handl
	cpu.esp+=2*data_size/8 + data_size/4;
	cpu.eip=cpu.esp;













#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
