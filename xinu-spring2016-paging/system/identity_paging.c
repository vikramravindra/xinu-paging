#include <xinu.h>
void identity_mapping(int pid)
{

	struct procent *pr = &proctab[pid];
	pr->prpagedir = (pd_t *)getpage(pid,FRAME_PG_DIR,-1);
	pd_t *prpagedir = pr->prpagedir;

	intmask mask;
	int i,j;
	pt_t *pg_tab;
	//mask = disable();
	for (j = 0; j < 4; j++)
	{
		pg_tab = (pt_t *)getpage(pid, FRAME_PG_TAB,-1);
		//kprintf ("getpage returns: %x\n", pg_tab);
		prpagedir[j].pd_pres = 1;
		prpagedir[j].pd_write = 1;
		for(i=0; i < 1024; i++)
		{
			pg_tab[i].pt_base = (j << 10) + i;
			pg_tab[i].pt_pres = 1;
			pg_tab[i].pt_write = 1;
			//if (j==2) kprintf ("Page %d has %05x000 %d %d\n",i, pg_tab[i].pt_base, pg_tab[i].pt_pres, pg_tab[i].pt_write);
		}
		prpagedir[j].pd_base = ((uint32)pg_tab) >> 12;
	}

	for (j = 5; j < 1024; j++)
		prpagedir[j].pd_write = 1;

	pg_tab = (pt_t *)getpage(pid, FRAME_PG_TAB,-1);
	prpagedir[576].pd_pres = 1;
	prpagedir[576].pd_write = 1;
	for(i=0; i < 1024; i++)
	{
		pg_tab[i].pt_pres = 1;
		pg_tab[i].pt_write = 1;
		pg_tab[i].pt_base = (576 << 10) + i;
		//kprintf ("Page %d has %05x000\n",i, pg_tab[i].pt_base);
	}
	prpagedir[576].pd_base = ((uint32)pg_tab) >> 12;

	//restore(mask);
	//write_cr3(prpagedir);
	//set_evec(14, (uint32 )&page_isr);
	//kprintf("Enabling paging...\n");
	//enable_paging();
	//kprintf("Page enabled.\n");
}

