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
	p_eflags.sreg=SREG_DS;
	p_eflags.val=cpu.eflags.val;
	operand_write(&p_eflags);

//Push CS

//Push EIP




// Find the IDT entry using 'intr_no'


// Clear IF if it is an interrupt


// Set EIP to the entry of the interrupt handl













#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
