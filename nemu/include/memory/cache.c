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
        (cache[i]).valid_bit=0;
    }
}

