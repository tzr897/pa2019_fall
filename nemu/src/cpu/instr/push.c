#include "cpuid.h/instr.h"

static void instr_execute_1op()
{
    operand_read(&opr_src);
    cpu.esp-=data_size/8;
    
}