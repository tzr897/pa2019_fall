#include "cpu/instr.h"

make_instr_func(lgdt)
{
    int len=1;
    OPERAND rm;
    len+=modrm_rm(eip + 1, &rm);

    return len;
}