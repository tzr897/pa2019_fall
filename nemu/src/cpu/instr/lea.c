#include "cpu/instr.h"

make_instr_func(lea)
{
    int len = 1;
	//OPERAND opr_dest;
	//operand_read(&opr_src);
	//operand_read(&opr_dest);

	opr_src.data_size=data_size;
	opr_dest.data_size=data_size;

	len += modrm_r_rm(cpu.eip+1, &opr_dest, &opr_src);

	opr_dest.val = opr_src.addr;
	
	operand_write(&opr_dest);

	return len;

}
