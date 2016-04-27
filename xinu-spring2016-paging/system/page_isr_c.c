#include <xinu.h>

long err_code;
unsigned long fault = 0;
#if 1
void page_isr_c()
{
	asm("movl %%cr2, %%eax; \
	     movl %%eax, %0"
	     :"=r"(fault)
	     :
	     :"%eax");
	kprintf("Callback to page_isr: %x %x\n", err_code, fault);
}

#endif
