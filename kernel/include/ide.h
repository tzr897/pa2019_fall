#ifndef __IDE_H__
#define __IDE_H__

void ide_read(uint8_t *buf, uint32_t offset, uint32_t len);
void ide_write(uint8_t *buf, uint32_t offset, uint32_t len);

#endif
