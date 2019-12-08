#include "cpu/cpu.h"
#include "memory/memory.h"
#include "assert.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	return offset + cpu.segReg[sreg].base;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	SegDesc s;
	uint32_t taddr;
	taddr = (uint32_t)hw_mem + (cpu.segReg[sreg].index*8) + cpu.gdtr.base;
	s.val[0]=paddr_read(taddr, 4);
	s.val[1]=paddr_read(taddr+4, 4);
	cpu.segReg[sreg].base=(s.base_31_24<<24)|(s.base_23_16<<16)|s.base_15_0;
	cpu.segReg[sreg].limit=(s.limit_19_16<<16)|s.limit_15_0;
	cpu.segReg[sreg].privilege_level=s.privilege_level;
	cpu.segReg[sreg].soft_use=s.soft_use;
	//printf("%x\n",taddr);
	//printf("s.val0:%x",s.val[0]);
	//printf("s.val1:%x",s.val[1]);
	assert(cpu.segReg[sreg].base==0);
	
	assert(s.present==1);
	assert(s.granularity==1);
}