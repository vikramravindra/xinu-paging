#include <xinu.h>

vmemlist* create_vlist()
{	
	vmemlist* head = create_node();
	head->vaddr = (char *)(NBPG * (FRAME0 + NFRAMES)); //4096
	//kprintf ("Process' virtual address starts at %x\n", head->vaddr);
	head->vlength = 0x90000000 - (NBPG * (FRAME0 + NFRAMES)); //4096
	return head;
}

vmemlist* create_node()
{
	return (vmemlist *)getmem(sizeof(vmemlist));
}

void delete_node(vmemlist * node)
{
	freemem((char *)node, sizeof(vmemlist));
}
char* get_vaddress(vmemlist *head, int size)
{
	vmemlist *temp = head;
	vmemlist *prev = head;
	while (temp != NULL)
	{
		kprintf("Size requested for: %d, Size of current block %x", size, temp->vlength);		
		if (size == temp->vlength)
		{
			if (temp == head)
			{
				char *ret_temp = head->vaddr;
				head = head->vmnext;
				return ret_temp;
			}
			char *ret_temp = temp->vaddr;
			kprintf ("Going to return %x\n", ret_temp);
			prev->vmnext = temp->vmnext;		
			delete_node(temp);
			return ret_temp;
			/* remove from list */
		
		}
		if (size < temp->vlength)
		{
			char *ret_temp = temp->vaddr;
			kprintf ("Going to return %x\n", ret_temp);
			temp->vlength = temp->vlength - size; 
			temp->vaddr += size;
			return ret_temp;
		}
		prev = temp;	
		temp = temp->vmnext;
	}
	kprintf ("Virtual addresses emptied out!\n");
	return NULL;	
}

void free_vaddress(vmemlist *head, char* vaddr, int size)
{
	if (head == NULL)
	{
		head = create_node();
		head->vaddr = vaddr;
		head->vlength = size;
		proctab[currpid].prvfreelist = head;
		return;
	}
	
	vmemlist *temp = head;
	if (temp->vmnext == NULL || vaddr < temp->vaddr) /* There is only one node or the node needs to be inserted at the head */
	{
		//kprintf ("%x %x\n", (char *)(4096 + size) , temp->vaddr);
		if ((char *)((NBPG * (FRAME0 + NFRAMES)) + size) == temp->vaddr) /* co-alesce with first node */
		{
			//kprintf("exact match");
			temp->vaddr = (char *)(NBPG * (FRAME0 + NFRAMES));
			temp->vlength = 0x90000000 - (NBPG * (FRAME0 + NFRAMES));
			return;
		}
		//kprintf ("%x %x\n", (unsigned long)vaddr + (unsigned long )size , temp->vaddr);
		if ((unsigned long)vaddr + (unsigned long )size == (unsigned long)temp->vaddr)
		{
			temp->vaddr = vaddr;
			temp->vlength += size;
			return;
		}
		vmemlist *cur = create_node(); 
		cur->vmnext = head;
		cur->vaddr = vaddr;
		proctab[currpid].prvfreelist = cur;
		cur->vlength = size;
		return;
	}
	vmemlist *prev = head;
	temp = temp->vmnext;
	while (temp != NULL)
	{
		kprintf ("%x %x %x\n", prev->vaddr, vaddr, temp->vaddr);
		if (prev->vaddr < vaddr && temp->vaddr > vaddr)
		{
			kprintf("%x %x\n", (unsigned long)prev->vaddr + prev->vlength + (unsigned long)size, (unsigned long) temp->vaddr);
			if ((unsigned long)prev->vaddr + prev->vlength + (unsigned long)size == (unsigned long) temp->vaddr)
			{
				prev->vlength = prev->vlength + size;
				return;
				/* coalesce */
			}

			vmemlist *cur = create_node();
			cur->vlength = size;
			cur->vaddr = vaddr;
			prev->vmnext = cur;
			cur->vmnext = temp;	
			return;
		}
		prev = temp;
		temp = temp->vmnext;
	}
}

void display_freemem(vmemlist* head)
{
	vmemlist* temp = head;
	while(temp != NULL)
	{
		kprintf("(%x %x) ", temp->vaddr, temp->vlength);
		temp = temp->vmnext;
	}
	kprintf ("\n");
}


