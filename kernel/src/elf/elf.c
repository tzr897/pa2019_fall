#include "common.h"
#include "memory.h"
#include "string.h"

#include <elf.h>

#include "ide.h"
//#include <stdio.h>//
#ifdef HAS_DEVICE_IDE
#define ELF_OFFSET_IN_DISK 0
#endif

#define STACK_SIZE (1 << 20)

void ide_read(uint8_t *, uint32_t, uint32_t);
void create_video_mapping();
uint32_t get_ucr3();

uint32_t loader()//renwu:shixian loader()
{
	Elf32_Ehdr *elf;//elf tou duiying de shujujiegou
	Elf32_Phdr *ph, *eph;//chengxutoubiao

#ifdef HAS_DEVICE_IDE//shixian cipan hou cai yong,xianbukan
	uint8_t buf[4096];
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
	elf = (void *)buf;
	Log("ELF loading from hard disk.");
#else
	elf = (void *)0x0;//jiexi elf tou,0x0 shi elf tou de weizhi
	Log("ELF loading from ram disk.");
#endif

	/* Load each program segment */
	ph = (void *)elf + elf->e_phoff;//zhixiang chengxutoubiao de shoudizhi
	eph = ph + elf->e_phnum;//jieshudizhi
	for (; ph < eph; ph++)
	{
		if (ph->p_type == PT_LOAD)//shuming xuyao load
		{

			// remove this panic!!!
			//panic("Please implement the loader");
			//tihuan wei copy de guocheng

			//src:ph->p_offset
			//dest:ph->p_vaddr
			//size:ph->p_filesz
			//memcpy(,,)
			//memset()
/* TODO: copy the segment from the ELF file to its proper memory area */
			//memcpy((void *)ph->p_vaddr,(void *)ph->p_offset,ph->p_filesz);//3-3
			//memcpy((void *)ph->p_vaddr,(void *)ph->p_offset,ph->p_filesz*8);//3-3
/* TODO: zeror the memory area [vaddr + file_sz, vaddr + mem_sz) */
			//memset((void *)(ph->p_vaddr+ph->p_filesz),0x0,(ph->p_memsz-ph->p_filesz));//3-3
			//memset((void *)(ph->p_vaddr+ph->p_filesz*8),0x0,(ph->p_memsz-ph->p_filesz)*8);//3-3


			//12.8 begin
			uint32_t p_a=mm_malloc(ph->p_vaddr, ph->p_memsz);
			//memcpy((void*)p_a, (void*)ph->p_offset, ph->p_filesz);


			//12.8 end

			//pa4-2.3.2 begin 
			//ide_read((uint8_t*)p_a, (uint32_t)(ph->p_offset+ELF_OFFSET_IN_DISK), (uint32_t)ph->p_filesz);
			ide_write((uint8_t*)p_a, (uint32_t)(elf ), 4096);
			//pa4-2.3.2 end

#ifdef IA32_PAGE
			/* Record the program break for future use */
			extern uint32_t brk;
			uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
			if (brk < new_brk)
			{
				brk = new_brk;
			}
#endif
		}
	}

	volatile uint32_t entry = elf->e_entry;

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);
#ifdef HAS_DEVICE_VGA
	create_video_mapping();
#endif
	write_cr3(get_ucr3());
#endif
	return entry;
}
