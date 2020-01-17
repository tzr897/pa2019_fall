#include "cpu/instr.h"

make_instr_func(in_b)
{
    OPERAND from,to;

    from.addr=REG_DX;
    from.type=OPR_REG;
    from.data_size=16;

    to.addr=REG_AL;
    to.type=OPR_REG;
    to.data_size=8;

    operand_read(&from);
    to.val=pio_read(from.val, 1);
    operand_write(&to);

    return 1;

}

make_instr_func(in_v)
{
    OPERAND from,to;

    from.addr=REG_DX;
    from.type=OPR_REG;
    from.data_size=16;

    to.addr=REG_EAX;
    to.type=OPR_REG;
    to.data_size=data_size;

    operand_read(&from);
    to.val=pio_read(from.val, data_size/8);
    operand_write(&to);
    
    return 1;
}

//void pio_write(uint16_t port, size_t len, uint32_t data);
//uint32_t pio_read(uint16_t port, size_t len);

// opr_dest.type=OPR_MEM;
//     opr_dest.addr=cpu.esp;
//     opr_dest.data_size=data_size;
//     opr_dest.sreg=SREG_DS;
//     operand_read(&opr_dest);
//     cpu.edi=opr_dest.val;  
//     cpu.esp+=data_size/8;