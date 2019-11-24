#include <stdio.h>
#include <memory.h>
#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include "memory/cache.h"
#include <stdlib.h>

struct CacheLine vcache;

