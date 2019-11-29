#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include "memory/cache.h"

CacheLine cache[1024];

void init_cache()
{
    for(int i=0;i<1024;++i)
    {
        cache[i].valid_bit=0;
    }
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine *cache)
{
    int i;
    uint32_t ret=0;
    uint32_t mark=(paddr>>13)&0x7ffff;
    uint32_t group=(paddr>>6)&0x7f;
    uint32_t baddr=paddr&0x3f;
    for(i=0;i<8;i++)
    {
        if((cache[group*8+i].valid_bit==1)&&(cache[group*8+i].tag==mark))
        {
            break;
        }
    }
    if(8==i)
    {
        i=0;
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
    //i yiqueding
    if((baddr+len)<=64)//bukuahang
    {
        memcpy(&ret, &cache[group*8+i].block[baddr], len);
    }
    else//kuahang
    {
        size_t out=baddr+len-64;
        uint32_t ret1=0;
        uint32_t ret2=0;
        memcpy(&ret2, &cache[group*8+i].block[baddr], (64-baddr));
        ret1=cache_read(paddr+(64-baddr), out, cache);
        ret=(ret1<<((64-baddr)*8))|ret2;
    }
    return ret;
}

void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine *cache)
{
    int i;
    uint32_t mark=(paddr>>13)&0x7ffff;
    uint32_t group=(paddr>>6)&0x7f;
    uint32_t baddr=paddr&0x3f;
    for(i=0;i<8;i++)
    {
        if((cache[group*8+i].valid_bit==1)&&(cache[group*8+i].tag==mark))
        {
            break;
        }
    }
    if(8==i)
    {
        if((baddr+len)<=64)
        {
            memcpy(hw_mem+paddr, &data, len);
        }
        else
        {
            size_t out=baddr+len-64;
            uint32_t data1=(data>>((64-baddr)*8));
            cache_write(paddr, 64-baddr, data, cache);
            cache_write(paddr+(64-baddr), out, data1, cache);         
        }
        
    }
    else
    {
        if((baddr+len)<=64)
        {
            memcpy(&cache[group*8+i].block[baddr], &data, len);
            memcpy(hw_mem+paddr, &data, len);
        }
        else
        {
            size_t out=baddr+len-64;
            uint32_t data1=(data>>((64-baddr)*8));
            cache_write(paddr, 64-baddr, data, cache);
            cache_write(paddr+(64-baddr), out, data1, cache);    
            memcpy(hw_mem+paddr, &data, 64-baddr);
        }
    }
}
