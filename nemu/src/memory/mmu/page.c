#include "cpu/cpu.h"
#include "memory/memory.h"
#include "assert.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	// printf("\nPlease implement page_translate()\n");
	// assert(0);
	uint32_t dir = (laddr >> 22) & 0x3ff;
	uint32_t page = (laddr >> 12) & 0x3ff;
	uint32_t offset = laddr & 0xfff;
	paddr_t res = 0;

	PDE pde;
	pde.val = paddr_read(((cpu.cr3.pdbr<<12) + dir*4), 4);
	//assert(pde.present==1);

	PTE pte;
	pte.val = paddr_read(((pde.page_frame<<12) + page*4), 4);
	assert(pte.present==1);

	res = (pte.page_frame<<12) + offset;
	return res;


#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
