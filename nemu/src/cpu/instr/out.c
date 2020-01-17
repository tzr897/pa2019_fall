#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(out_b)
{
    OPERAND from,to;

    from.addr=REG_AL;
    from.type=OPR_REG;
    from.data_size=8;

    to.addr=REG_DX;
    to.type=OPR_REG;
    to.data_size=16;

    operand_read(&from);
    operand_read(&to);
    pio_write(to.val, 1, from.val);

    return 1;
}

make_instr_func(out_v)
{
    return 0;
}

//void pio_write(uint16_t port, size_t len, uint32_t data);
//uint32_t pio_read(uint16_t port, size_t len);

/*
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
} */