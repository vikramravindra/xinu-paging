	.text
	.globl page_isr
page_isr:
	popl err_code
	pushal
	cli
	call page_isr_c
	sti
	popal
	iret
