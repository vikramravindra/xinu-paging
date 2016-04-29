#include <xinu.h>
uint32 tmp1 = 0x80000013;
void enable_paging()
{
	uint32 cr0;
	intmask mask;
	//mask = disable();
	cr0 = read_cr0();
	cr0 |= 0x80000001; 
	write_cr0(cr0);
	//restore(mask);
}
