#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include "memory/cache.h"

CacheLine mycache[1024];

void init_cache()
{
    for(int i=0;i<1024;++i)
    {
        mycache[i].valid_bit=0;
    }
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine *cache)
{
    /*
    uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	return ret;
     */
    uint32_t ret=0;
    uint32_t mark=(paddr>>13)&0x7ffff;
    uint32_t group=(paddr>>6)&0x7f;
    uint32_t baddr=paddr&0x3f;

}

void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine *cache)
{

}
