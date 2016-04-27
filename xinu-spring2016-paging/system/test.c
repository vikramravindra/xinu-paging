#include <xinu.h>

void test()
{
	display_freemem(proctab[currpid].prvfreelist);
	
	char *ret = vgetmem(100);
	display_freemem(proctab[currpid].prvfreelist);
	kprintf ("The virtual address returned is %x\n", ret);
	
	char *ret1 = vgetmem(100);
	kprintf ("The virtual address returned is %x\n", ret1);
	display_freemem(proctab[currpid].prvfreelist);
	
	vfreemem(ret, 100);
	kprintf ("After deleting\n");
	display_freemem(proctab[currpid].prvfreelist);
	kprintf ("The virtual address returned is %x\n", ret);
	
	vfreemem(ret1, 100);
	kprintf ("After deleting\n");
	display_freemem(proctab[currpid].prvfreelist);
	kprintf ("The virtual address returned is %x\n", ret);
	
}
