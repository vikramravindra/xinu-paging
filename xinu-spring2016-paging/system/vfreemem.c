#include <xinu.h>

void vfreemem(
	char	*blkaddr,
	uint32  nbytes
     )

{
	intmask mask;
	mask = disable();
	if (blkaddr < (char *)4096 || blkaddr >= (char *)0x90000000)
	{
		kprintf ("Attempting to free invalid address!");
		return;
	}
	free_vaddress(proctab[currpid].prvfreelist, blkaddr, nbytes);	
	restore(mask);

}
