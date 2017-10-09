/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <dlfcn.h>
#include <assert.h>

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
//extern void product_consumer_main(void);



/* ============================ [ DATAS     ] ====================================================== */


/* ============================ [ LOCALS    ] ====================================================== */
#if 0
void can_main(void)
{
	can_init();
	cantp_init(0x731,0x732);

	do {
		can_main_rxisr();
		cantp_main_function();
		usleep(1000);
	} while(1);

}
#endif

/* ============================ [ FUNCTIONS ] ====================================================== */
#if 0
int main(int argc,char *argv[])
{
	//product_consumer_main();
	//file_main();
	//eval_main(argv[1]);
	//other();
	//SocketClient_main();
	//can_main();


	return 0;
}
#else
int main(int argc,char *argv[])	/*Dynamic Link Library*/
{
	void *pdlHandle = dlopen("./eval.so", RTLD_LAZY);
	assert(pdlHandle != NULL);
	void (*pSymbol)(const char *expr) =(void (*)(const char *))dlsym(pdlHandle, "eval_main");
	assert(pSymbol != NULL);

	eval_main(argv[1]);

	dlclose(pdlHandle);
}
#endif
