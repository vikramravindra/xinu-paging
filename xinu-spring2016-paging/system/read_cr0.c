#include <xinu.h>

uint32 read_cr0()
{
	uint32 ret;
	asm("movl %%cr0, %%eax; \
	     movl %%eax, %0"
	     :"=r"(ret)
	     :
	     :"%eax");
	return ret;

}
