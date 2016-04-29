#include <xinu.h>

void allocate_frame(int pid, int type, uint32 vpage)
{
	int i;
	for (i = 0; i < NFRAMES; i++)
	{
		if(invertpagetable[page_head].empty == TRUE)
		{
			invertpagetable[page_head].pid = pid;
			invertpagetable[page_head].type = type;
			invertpagetable[page_head].empty = FALSE;
			invertpagetable[page_head].vpage = vpage;
			return;
		}	
		page_head = (++page_head) % NFRAMES;		
	}
	kprintf ("Could not find any empty pages. Must evict\n");
	if (policy == FIFO)
	{
		kprintf("Eviction Policy: FIFO\n");
		uint32 evict_page = (page_head + 1) % NFRAMES;
		while(invertpagetable[page_head].type != FRAME_REG)
		{
			evict_page = (page_head + 1) % NFRAMES;
			if (evict_page == (page_head + 1) % NFRAMES)
			{
				kprintf ("All frames filled by directories or tables!\n");
			}
		}
		page_head = evict_page;
		
		int old_pid = invertpagetable[page_head].pid;
		int old_type = invertpagetable[page_head].type;
		int old_vpage = invertpagetable[page_head].vpage;

		int old_bs = bs_page(old_vpage);
		int old_pd = pd(old_vpage);
		int old_pt = pt(old_vpage);
		
		struct procent *old_prptr = &proctab[old_pid];
		pd_t *old_pd_t = old_prptr->prpagedir;
		pt_t *old_pt_t = (old_pd_t[old_pd].pd_base << 12);
		old_pt_t[old_pt].pt_pres = 0;
		char* addr = (char *)frame2addr(page_head);
		if(open_bs(old_prptr->prbs) == (uint32)-1 ||
		   write_bs(addr, old_prptr->prbs, old_bs)||
		   close_bs(old_prptr->prbs) == (uint32)-1)
		{
			kprintf("Backing store error during eviction!");
			return;
		}
		invertpagetable[page_head].pid = pid;
		invertpagetable[page_head].type = type;
		invertpagetable[page_head].empty = FALSE;
		invertpagetable[page_head].vpage = vpage;
	}

}
uint32 frame2addr(uint32 frameindex)
{
	return (FRAME0 + frameindex) * NBPG; 
}

/*uint32 print_invertpagetable(int count)
  {
  int i;
  for(i = 0; i < count; i++)
  kprintf("%

  }*/

