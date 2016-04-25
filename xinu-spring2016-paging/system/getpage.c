#include <xinu.h>
char *next = (char *)(NBPG * FRAME0);
char *getpage()
{
	char *ret = next;
	memset(ret, 0, 4096);
	next = next + NBPG;
	return ret;

}
