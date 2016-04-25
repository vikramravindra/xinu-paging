#include <xinu.h>

void write_cr0(uint32 cr0)
{
	asm("movl %0, %%eax; \
	     movl %%eax, %%cr0"
	     :
	     :"r"(cr0)
	     :"%eax");

}
