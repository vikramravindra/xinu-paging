#include <xinu.h>

void test1()
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

void test2()
{
	
	char *ret1 = vgetmem(2 * NBPG);
	char *ret2 = vgetmem(2 * NBPG);
	int i;
	for(i = 0; i < 2 * NBPG; i++)
	{
		ret1[i] = 'a';
	}
	for(i = 0; i < 2 * NBPG; i++)
	{
		kprintf("%c",ret1[i]);
	}
	kprintf("\n");
	for(i = 0; i < 2 * NBPG; i++)
	{
		ret2[i] = 'b';
	}
	for(i = 0; i < 2 * NBPG; i++)
	{
		kprintf("%c",ret2[i]);
	}
	kprintf("\n");
}


void test3()
{
	char *ret1 = vgetmem(5 * NBPG);
	char *ret2 = vgetmem(5 * NBPG);
	int i;
	for (i = 0; i < 5; i++)
	{
		ret1[i*NBPG + 1] = 'a';
		ret2[i*NBPG + 1] = 'b';
	}
	for (i = 0; i < 5; i++)
	{
		kprintf("%c%c",ret1[i*NBPG + 1],ret2[i*NBPG + 1]);
	}

}

