#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void *thread_add (void *kol)
{
	int i;
	long num;
	num=(long int)kol;

	printf("Номер потока: %ld\n", num);

	for (i = 0; i < 10; i++)
	{
		printf ("Идентификатор потока #%ld: %u\n", num, pthread_self());
		sleep(1);
	}
}

int main()
{
	pthread_t threads[NUM_THREADS];
	pthread_t abc;
	int rc;
	long int t;

	for (t=1; t<NUM_THREADS+1; t++)
	{
		printf ("Создан поток #%ld\n", t);
		rc=pthread_create (&threads[t], NULL, thread_add, (void *)t);
		if (rc)
		{
			printf ("ERROR\n");
			exit (-1);
 		}
 	}

 	for(t=1; t<NUM_THREADS+1; t++)
 	{
		pthread_join (threads[t], NULL);
		printf ("Поток #%ld завершен\n", t);
	}
	return 0;
}
