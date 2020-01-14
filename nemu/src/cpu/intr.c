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
	data_size=32;
	OPERAND p_eflags;
	cpu.esp-=data_size/8;
	p_eflags.data_size=data_size;
	p_eflags.type=OPR_MEM;
	p_eflags.addr=cpu.esp;
	p_eflags.sreg=SREG_DS;
	p_eflags.val=cpu.eflags.val;
	operand_write(&p_eflags);

//Push CS
	OPERAND p_cs;
	cpu.esp-=data_size/8;
	p_cs.data_size=data_size;
	p_cs.type=OPR_MEM;
	p_cs.addr=cpu.esp;
	p_cs.sreg=SREG_DS;
	p_cs.val=cpu.cs.val;
	operand_write(&p_cs);

//Push EIP
	OPERAND p_eip;
	cpu.esp-=data_size/8;
	p_eip.data_size=data_size;
	p_eip.type=OPR_MEM;
	p_eip.addr=cpu.esp;
	p_eip.sreg=SREG_DS;
	p_eip.val=cpu.eip;
	operand_write(&p_eip);


// Find the IDT entry using 'intr_no'
	GateDesc gd;
	gd.val[0]=paddr_read((cpu.idtr.base+8*intr_no),4);
	gd.val[1]=paddr_read((cpu.idtr.base+8*intr_no+4),4);


// Clear IF if it is an interrupt
	if(gd.type==14)
	{
		cpu.eflags.IF=0;
	}

// Set EIP to the entry of the interrupt handl
	cpu.eip=gd.offset_31_16<<16 | gd.offset_15_0;


#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
