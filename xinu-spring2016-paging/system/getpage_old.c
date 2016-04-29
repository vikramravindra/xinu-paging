#include <xinu.h>
char *next = (char *)(NBPG * FRAME0);
#if 1
char *getpage_old()
{
	char *ret = next;
	memset(ret, 0, 4096);
	next = next + NBPG;
	return ret;

}
#endif
