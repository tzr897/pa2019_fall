#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	// printf("\nPlease implement page_translate()\n");
	// assert(0);
// typedef union//CR3
// {
// 	struct 
// 	{
// 		uint32_t reserve:12;
// 		uint32_t pdbr :20;
// 	};
// 	uint32_t val; 
// }CR3;
	uint32_t dir = laddr >> 22;
	uint32_t page = (laddr >> 12) & 0x3ff;
	uint32_t offset = laddr & 0xfff;
		

















#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
