#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>
#include "memory/cache.h"

uint8_t hw_mem[MEM_SIZE_B];


uint32_t hw_mem_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data)
{
	memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;
#ifdef CACHE_ENABLED
        ret=cache_read(paddr, len, cache);
#else
		ret = hw_mem_read(paddr, len);
#endif
	return ret;
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data)
{
#ifdef CACHE_ENABLED
        cache_write(paddr, len, data, cache);
#else
		hw_mem_write(paddr, len, data);
#endif
}

uint32_t laddr_read(laddr_t laddr, size_t len)
{
	// return paddr_read(laddr, len);
	assert(len==1 || len==2 || len==4);
//#ifdef IA32_PAGE
	paddr_t paddr=laddr;
	if(cpu.cr0.pg==1&&cpu.cr0.pe==1)
	{
		//uint32_t dir = laddr >> 22;
		//uint32_t page = (laddr >> 12) & 0x3ff;
		uint32_t offset = laddr & 0xfff;
		if(offset + len > 0x1000)//data cross the page boundary
		{
			uint32_t res1, res2;
			size_t len1, len2;
			len1 = offset + len - 0x1000;
			len2 = len - len1;
			res1 = laddr_read(laddr + len2, len1);
			res2 = laddr_read(laddr, len2);
			return (res1 << len2*8) | res2;
		}
		else
		{
			paddr = page_translate(laddr);
			
		}
	}
	//return paddr_read(paddr, len);
	return hw_mem_read(paddr, len);
else
	//return paddr_read(laddr, len);
	return hw_mem_read(laddr, len);
//#endif
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data)
{
//#ifdef IA32_PAGE
	paddr_t paddr=laddr;
	if(cpu.cr0.pg==1&&cpu.cr0.pe==1)
	{
		//uint32_t dir = laddr >> 22;
		//uint32_t page = (laddr >> 12) & 0x3ff;
		uint32_t offset = laddr & 0xfff;
		if(offset+len > 0x1000)//data cross the page boundary
		{
			uint32_t data1;
			size_t len1, len2;		
			len1 = offset + len - 0x1000;
			len2 = len - len1;
			data1 = data >> (len2*8);
			laddr_write(laddr, len2, data);
			laddr_write(laddr + len2, len1, data1);
		}
		else
		{
			paddr = page_translate(laddr);			
		}
	}
	//paddr_write(paddr, len, data);
	hw_mem_write(paddr, len, data);
else
	//paddr_write(laddr, len, data);//12.8
	hw_mem_write(laddr, len, data);
//#endif
}

uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
	return laddr_read(vaddr, len);
#else
	uint32_t laddr=vaddr;
	if(cpu.cr0.pe)//11.30
	{
		laddr=segment_translate(vaddr,sreg);
	}
	return laddr_read(laddr, len);
#endif
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data)
{
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
	laddr_write(vaddr, len, data);
#else
	uint32_t laddr=vaddr;
	if(cpu.cr0.pe)//11.30
	{
		laddr=segment_translate(vaddr,sreg);
	}
	laddr_write(laddr, len, data);

#endif
}

void init_mem()
{
	// clear the memory on initiation
	//
#ifdef CACHE_ENABLED
	init_cache();
#else
	//
	memset(hw_mem, 0, MEM_SIZE_B);
#endif

#ifdef TLB_ENABLED
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t *get_mem_addr()
{
	return hw_mem;
}




