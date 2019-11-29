#ifndef __INSTR_CACHE_H__
#define __INSTR_CACHE_H__

#include "nemu.h"

typedef struct 
{
    bool valid_bit;
    uint32_t tag;
    uint8_t block[64];
}CacheLine;

//extern CacheLine cache[1024];

void init_cache();

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine *cache);

void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine *cache);





#endif