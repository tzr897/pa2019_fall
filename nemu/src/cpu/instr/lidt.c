#include "cpu/instr.h"

make_instr_func(lidt)
{
    int len=1;
    OPERAND rm;
    rm.data_size=data_size;
    len+=modrm_rm(eip + 1, &rm);
    operand_read(&rm);
	cpu.idtr.limit = rm.val & 0xffff;
    rm.addr+=2;
    operand_read(&rm);
    cpu.idtr.base = rm.val;
    return len;
}