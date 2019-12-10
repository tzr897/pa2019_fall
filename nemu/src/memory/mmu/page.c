#include "cpu/cpu.h"
#include "memory/memory.h"
#include "assert.h"

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

// /* the 32bit Page Directory(first level page table) data structure */
// typedef union PageDirectoryEntry {
// 	struct
// 	{
// 		uint32_t present : 1;
// 		uint32_t read_write : 1;
// 		uint32_t user_supervisor : 1;
// 		uint32_t page_write_through : 1;
// 		uint32_t page_cache_disable : 1;
// 		uint32_t accessed : 1;
// 		uint32_t pad0 : 6;
// 		uint32_t page_frame : 20;
// 	};
// 	uint32_t val;
// } PDE;

// /* the 32bit Page Table Entry(second level page table) data structure */
// typedef union PageTableEntry {
// 	struct
// 	{
// 		uint32_t present : 1;
// 		uint32_t read_write : 1;
// 		uint32_t user_supervisor : 1;
// 		uint32_t page_write_through : 1;
// 		uint32_t page_cache_disable : 1;
// 		uint32_t accessed : 1;
// 		uint32_t dirty : 1;
// 		uint32_t pad0 : 1;
// 		uint32_t global : 1;
// 		uint32_t pad1 : 3;
// 		uint32_t page_frame : 20;
// 	};
// 	uint32_t val;
// } PTE;
	uint32_t dir = (laddr >> 22) & 0x3ff;
	uint32_t page = (laddr >> 12) & 0x3ff;
	uint32_t offset = laddr & 0xfff;
	paddr_t res = 0;

	// PDE pde;
	// pde.val = paddr_read(((uint32_t)hw_mem + (cpu.cr3.pdbr<<12) + dir*4), 4);
	// assert(pde.present==1);

	// PTE pte;
	// pte.val = paddr_read(((uint32_t)hw_mem + (pde.page_frame<<12) + page*4), 4);
	// assert(pte.present==1);
	// res = (pte.page_frame<<12) + offset;
	// return res;



	PDE pde;
	pde.val = paddr_read(((cpu.cr3.pdbr<<12) + dir*4), 4);
	assert(pde.present==1);

	PTE pte;
	pte.val = paddr_read(((pde.page_frame<<12) + page*4), 4);
	assert(pte.present==1);

	res = (pte.page_frame<<12) + offset;
	return res;




	// PDE *pde;
	// pde=(PDE*)((uint32_t)hw_mem + (cpu.cr3.pdbr<<12) + dir*4);
	// assert(pde->present==1);
	// //printf("pde ok\n");

	// PTE *pte;
	// pte=(PTE*)((uint32_t)hw_mem + (pde->page_frame<<12) + page*4);
	// assert(pte->present==1);
	// //printf("pte ok\n");

	// res=(pte->page_frame<<12) | offset;
	// return res;


#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
