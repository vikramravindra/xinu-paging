/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{

	/* Start the network */
	/* DO NOT REMOVE OR COMMENT THIS CALL */
	kprintf ("In main process...\n");
	netstart();

	/* Initialize the page server */
	/* DO NOT REMOVE OR COMMENT THIS CALL */
	psinit();
	//kprintf("\n...creating a shell\n");
	recvclr();
	//resume(vcreate(test1, 2048, 10, 50, "test", 0, NULL));
	resume(vcreate(test2, 2048, 10, 50, "test1", 0, NULL));
	//resume(vcreate(shell, 8192, 10, 50, "shell", 1, CONSOLE));
	//kprintf("returned from shell\n");
	/* Wait for shell to exit and recreate it */

	/*while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}*/
	return OK;
}
