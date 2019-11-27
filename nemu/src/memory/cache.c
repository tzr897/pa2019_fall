#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include "memory/cache.h"

CacheLine L1_dcache[1024];

void init_cache()
{
    for(int i=0;i<1024;++i)
    {
        L1_dcache[i].valid_bit=0;
    }
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine *cache)
{
    /*
    uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	return ret;
     */
    int i;
    uint32_t ret=0;
    uint32_t mark=(paddr>>13)&0x7ffff;
    uint32_t group=(paddr>>6)&0x7f;
    uint32_t baddr=paddr&0x3f;
    for(i=0;i<8;++i)
    {
        if((cache[group*8+i].valid_bit==1)&&(cache[group*8+i].tag==mark))
        {
            break;
        }
        if(8==i)
        {
            for(i=0;i<8;++i)
            {
                if(cache[group*8+i].valid_bit==0)
                {
                    break;
                }
            }
            if(8==i)
            {
                srand((unsigned)time(NULL));
                i=rand()%8;
            }
            
            cache[group*8+i].valid_bit=1;
            cache[group*8+i].tag=mark;
            memcpy(cache[group*8+i].block, hw_mem+paddr-baddr, 64);
        }
    }
    //i yiqueding
    if((baddr+len)<64)//bukuahang
    {
        memcpy(&ret, &cache[group*8+i].block, len);
    }
    else//kuahang
    {
        size_t out=baddr+len-64;

    }
    

    

    return ret;
}

void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine *cache)
{
    int i;
    uint32_t mark=(paddr>>13)&0x7ffff;
    uint32_t group=(paddr>>6)&0x7f;
    uint32_t baddr=paddr&0x3f;
}
