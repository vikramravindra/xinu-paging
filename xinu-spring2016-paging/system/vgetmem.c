#include <xinu.h>
#if 1 
char  	*vgetmem(
	  uint32	nbytes		/* Size of memory requested	*/
	)
{

	intmask mask;
	mask = disable();
	struct procent *prptr = &proctab[currpid];
	
	char *ret = get_vaddress(prptr->prvfreelist, nbytes);
	if (ret == NULL)
		return (char *)SYSERR;
	return ret;
}

#endif
