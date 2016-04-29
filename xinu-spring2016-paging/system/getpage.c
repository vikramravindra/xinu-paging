#include <xinu.h>
//char *next = (char *)(NBPG * FRAME0);
char *getpage(int pid, int type, uint32 vpage)
{
	allocate_frame(pid, type, vpage);
	char *ret = frame2addr(page_head);
	memset(ret, 0, 4096);
	//kprintf ("getpage returned frame: %u, address: %x\n", page_head, ret);
	return ret;
}
