#include "cpu/instr.h"

make_instr_func(call_near)
{
    int offset;
    OPERAND rel,i;
    rel.data_size=data_size;
    rel.type=OPR_IMM;
    rel.addr=cpu.eip+1;
    rel.sreg=SREG_CS;
    operand_read(&rel);

    i.data_size=data_size;
    i.type=OPR_MEM;
    cpu.esp-=data_size/8;
    i.addr=cpu.esp;
    i.sreg=SREG_DS;
    i.val=cpu.eip+1+data_size/8;
    operand_write(&i);
    
    offset=sign_ext(rel.val,data_size);
    cpu.eip+=offset+1+data_size/8;
    return 0;

}

make_instr_func(call_near_indirect)
{
    OPERAND rel;
    modrm_rm(cpu.eip+1, &rel);
        
    rel.data_size = data_size;
    operand_read(&rel);

    if(data_size==16)
    {          
        cpu.eip=rel.val&0xffff;
    }
    else
    {
        cpu.eip=rel.val;
    }
    operand_write(&rel);
    return 0; 
}