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
    OPERAND from,to;

    from.addr=REG_EAX;
    from.type=OPR_REG;
    from.data_size=data_size;

    to.addr=REG_DX;
    to.type=OPR_REG;
    to.data_size=16;

    operand_read(&from);
    operand_read(&to);
    pio_write(to.val, data_size/8, from.val);

    return 1;
}

//void pio_write(uint16_t port, size_t len, uint32_t data);
//uint32_t pio_read(uint16_t port, size_t len);