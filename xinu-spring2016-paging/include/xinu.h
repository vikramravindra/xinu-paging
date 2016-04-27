/* xinu.h - include all system header files */

#include <kernel.h>
#include <conf.h>
#include <process.h>
#include <queue.h>
#include <resched.h>
#include <mark.h>
#include <semaphore.h>
#include <memory.h>
#include <bufpool.h>
#include <clock.h>
#include <ports.h>
#include <uart.h>
#include <tty.h>
#include <device.h>
#include <interrupt.h>
#include <file.h>
#include <rfilesys.h>
#include <rdisksys.h>
#include <lfilesys.h>
#include <ether.h>
#include <gpio.h>
#include <net.h>
#include <ip.h>
#include <arp.h>
#include <udp.h>
#include <dhcp.h>
#include <icmp.h>
#include <tftp.h>
#include <name.h>
#include <shell.h>
#include <date.h>
#include <prototypes.h>
#include <delay.h>
#include <pci.h>
#include <quark_eth.h>
#include <quark_pdat.h>
#include <quark_irq.h>
#include <multiboot.h>
#include <stdio.h>
#include <string.h>
#include <paging.h>
#include <page_server.h>




/* Lab 5 definitions */
void initialize_paging();
void page_isr();
void page_isr_c();
void write_cr3(unsigned long *);
char* getpage();
void enable_paging();
uint32 read_cr0();
void write_cr0(uint32 );
void identity_mapping(int );

void test();
char* vgetmem(uint32 );
char *vgetmem_internal(int );
vmemlist* create_vlist();
vmemlist* create_node();
void delete_node(vmemlist* );
char* get_vaddress(vmemlist *, int );
void free_vaddress(vmemlist *, char* , int );
void vfreemem(char *, uint32 );

