#include <xinu.h>
static unsigned long *tmp;
void write_cr3(unsigned long *ptr)
{
	tmp = ptr;
	asm("pushl %eax");
	asm("movl tmp, %eax");
	asm("movl %eax, %cr3");
	//*tmp = 0;
	asm("movl %cr3, %eax");
	asm("movl %eax, tmp");
	//kprintf ("cr3 now holds %08x\n", tmp);
	asm("popl %eax");

}
