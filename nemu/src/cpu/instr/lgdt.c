#include "cpu/instr.h"

make_instr_func(lgdt)
{
    int len=1;
    OPERAND rm;
    rm.data_size=data_size;
    len+=modrm_rm(eip + 1, &rm);
    operand_read(&rm);
	cpu.gdtr.limit = rm.val & 0xffff;
    cpu.gdtr.base = rm.val;
    return len;
}