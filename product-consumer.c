#if 0
/* ============================ [ INCLUDES  ] ====================================================== */
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/queue.h>
#include <stdbool.h>
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
typedef struct number_entry_s
{
	int number;
	STAILQ_ENTRY(number_entry_s) next;
} number_entry_t;

/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static pthread_t threadProduct;
static pthread_t threadConsumer;
static pthread_mutex_t qcLock = PTHREAD_MUTEX_INITIALIZER;
static sem_t semProduct;
static sem_t semConsumer;
static sem_t semLock;
static STAILQ_HEAD(,number_entry_s) numberList;
/* ============================ [ LOCALS    ] ====================================================== */
static void product_main (void * param)
{
	number_entry_t* entry;
	for(;;)
	{
		entry = malloc(sizeof(number_entry_t));
		if(entry != NULL)
		{
			entry->number = rand()+(int)param;
			sem_wait(&semLock);
			STAILQ_INSERT_TAIL(&numberList,entry,next);
			sem_post(&semLock);
			printf("product<%d> number %d\n",(int)param,entry->number);
			sem_post(&semProduct);
			//sem_wait(&semConsumer);
		}

		usleep(500000);
	}
}
static void product_consumer (void * param)
{
	number_entry_t* entry;
	for(;;)
	{
		sem_wait(&semProduct);
		sem_wait(&semLock);
		while(false == STAILQ_EMPTY(&numberList))
		{
			entry = STAILQ_FIRST(&numberList);
			STAILQ_REMOVE_HEAD(&numberList, next);

			printf("consume number %d\n",entry->number);
			free(entry);
		}
		sem_post(&semLock);
		usleep(2000000);
		//sem_post(&semConsumer);
	}
}

/* ============================ [ FUNCTIONS ] ====================================================== */


void product_consumer_main(void)
{
	STAILQ_INIT(&numberList);

	sem_init(&semProduct,0,0);
	sem_init(&semConsumer,0,0);
	sem_init(&semLock,0,1);

	pthread_create(&threadConsumer,NULL,product_consumer,(void*)0x5678);
	pthread_create(&threadProduct,NULL,product_main,(void*)0x1);
	pthread_create(&threadProduct,NULL,product_main,(void*)0x2);


	while(1) usleep(1000);
}

#endif

