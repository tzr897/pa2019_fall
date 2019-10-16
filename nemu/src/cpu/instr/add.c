#include "cpu/instr.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	
	operand_write(&opr_dest);
}

make_instr_func()