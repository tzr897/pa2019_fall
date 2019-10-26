#include "cpu/instr.h"

make_instr_func(jmp_near)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;
}

make_instr_func(jmp_short)
{
        int new_data_size=8;
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = new_data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, new_data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 1 + new_data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + new_data_size / 8;
}

make_instr_func(jmp_near_indirect)
{
/*
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;
        operand_read(&rel);
        int offset = sign_ext(rel.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);
        cpu.eip += offset;
        return 1 + data_size / 8; 
*/
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        //rel.data_size = data_size;

        rel.addr = eip + 1;

        operand_read(&rel);
        // thank Ting Xu from CS'17 for finding this bug
        //print_asm_1("jmp", "", 1 + data_size / 8, &rel);
        if(rel.data_size==16)
        { 
                rel.val = sign_ext(rel.val, data_size);
                cpu.eip=rel.val&0xffff;
        }
        else
        {
                  
                cpu.eip=rel.val;

        }

        return 0;
}
