#include <xinu.h>

long err_code;
unsigned long fault = 0;
#if 1
void page_isr_c()
{
	intmask mask = disable();
	/* Call to cr2 to find which virtual address faulted */
	asm("movl %%cr2, %%eax; \
			movl %%eax, %0"
			:"=r"(fault)
			:
			:"%eax");
	kprintf("Callback to page_isr: %x %x\n", err_code, fault);

	uint32 fault_bs_page, fault_pd, fault_pt;
	fault_bs_page = bs_page(fault);
	fault_pd      = pd(fault);
	fault_pt      = pt(fault);
	kprintf("Here 1\n");	
	struct procent *prptr = &proctab[currpid];
	pd_t *cur_pg_t = prptr->prpagedir;
	pt_t *table_page;
	if(!cur_pg_t[fault_pd].pd_pres) /*Page table missing. Create one! */
	{
		kprintf ("Page table not present, trying to create...\n");
		table_page = (pt_t *)getpage(currpid, FRAME_PG_TAB, -1);		
		cur_pg_t[fault_pd].pd_pres = 1;
		cur_pg_t[fault_pd].pd_base = ((uint32)table_page >> 12);
		kprintf("Page table has been created...\n");

		kprintf("Here 2\n");
		int i;
		for (i = 0; i < 1024; i++)
		{
			table_page[i].pt_write = 1;
		}
	}
	kprintf("Here 3\n");	
	/* faulted page table */
	pt_t* fault_page_table = (pt_t*)(cur_pg_t[fault_pd].pd_base << 12);

	char *fault_page;
	if (!fault_page_table[fault_pt].pt_pres)
	{
		fault_page = getpage(currpid, FRAME_REG, fault_bs_page);
		fault_page_table[fault_pt].pt_pres = 1;
		kprintf ("Bringing faulted page into memory %x \n", fault_page);

	}
	kprintf("Here 4\n");	
	if(open_bs(prptr->prbs) == (uint32)-1 ||
			read_bs(fault_page, prptr->prbs, fault_bs_page) == SYSERR ||
			close_bs(prptr->prbs == (uint32)-1))
	{
		kprintf ("Error with backing store\n");
		restore(mask);
		return;
	}

	restore(mask);
	kprintf("Successfully exiting page_isr...\n");

}




uint32 bs_page(uint32 address)
{
	return (address/NBPG -(FRAME0 + NFRAMES));
}

uint32 pd(uint32 address)
{
	return ((address & 0xFFC00000)) >> 22;
}

uint32 pt(uint32 address)
{
	return ((address & 0x003FF000) >> 12);
}
#endif
