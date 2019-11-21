#include "memory/cache.h"

struct CacheLine vcache;

uint32_t paddr_read(paddr_t paddr, size_t len)
{
    uint32_t ret=0;
#ifdef CACHE_ENABLED
        ret=cache_read(paddr,len,&L1_dcache);
#else
        ret=hw_mem_read(paddr,len);
#endif
    return ret;
}

void paddr_write(paddr_t paddr,size_t len,uint32_t data)
{
#ifdef CACHE_ENABLED
        cache_write(paddr,len,data,&L1_dcache);
#else
        hw_mem_write(paddr,len,data);
#endif

}