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
	//return 0;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	SegDesc s;

	cpu.segReg[sreg].base=(s.base_31_24<<24)|(s.base_23_16<<16)|s.base_15_0;
	cpu.segReg[sreg].limit=(s.limit_19_16<<16)|s.limit_15_0;
	cpu.segReg[sreg].privilege_level=s.privilege_level;
	assert(s.present==1);
	assert(s.granularity=1);
}
/*
typedef struct//SegReg 
{
// the 16-bit visible part, i.e., the selector
	union 
	{
		uint16_t val;
		struct 
		{
			uint32_t rpl :2;
			uint32_t ti :1;
			uint32_t index :13;
		};
	};
	// the invisible part, i.e., cache part
	struct 
	{
		uint32_t base;
		uint32_t limit;
		uint32_t type :5;
		uint32_t privilege_level :2;
		uint32_t soft_use :1;
	};
}SegReg;

typedef union SegmentDescriptor {
	struct
	{
		uint32_t limit_15_0 : 16;
		uint32_t base_15_0 : 16;
		uint32_t base_23_16 : 8;
		uint32_t type : 4;
		uint32_t segment_type : 1;
		uint32_t privilege_level : 2;
		uint32_t present : 1;
		uint32_t limit_19_16 : 4;
		uint32_t soft_use : 1;
		uint32_t operation_size : 1;
		uint32_t pad0 : 1;
		uint32_t granularity : 1;
		uint32_t base_31_24 : 8;
	};
	uint32_t val[2];
} SegDesc;

uint32_t segment_translate(uint32_t vaddr, uint8_t sreg);
void load_sreg(uint8_t sreg);
 */
