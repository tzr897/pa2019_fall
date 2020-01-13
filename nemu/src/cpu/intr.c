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

//Push EFLAGS
OPERAND p_eflags;
p_eflags.val=cpu.eflags.val;
p_eflags.data_size=data_size;
cpu.esp-=4;

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
