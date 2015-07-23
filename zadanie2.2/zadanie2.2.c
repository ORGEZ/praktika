#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 2
#define SIZE 5

int a = 0;
int i;

void *sum (void *num)
{
	long int t_num;
	t_num=(long int) num;

	printf("(#first) Создан новый поток! Номер потока: %ld\n", t_num);
	for ( i = 0; i < SIZE; i++)
	{
		sleep(1);
		a = a + 2*i;
		printf("(#first) Значение увеличено на %d!\n", 2*i);
	}
}

void *s4et(void *num)
{
	long t_num;
	t_num = (long) num;

	printf ("(#second) Создан новый поток! Номер потока: %ld\n", t_num);

	while (i != SIZE)
	{
		sleep(1);
		printf ("(#second) a = %d\n",a);
	}
}

int main()
{
	pthread_t first;
	pthread_t second;

	int rc;
	int i;
	long int t = 0;

	rc = pthread_create (&first, NULL, sum, (void *)t);
	if (rc)
	{
		printf ("ERROR\n");
		exit (-1);
 	}
 	t++;

	rc = pthread_create(&second, NULL, s4et, (void *)t);
	if (rc)
	{
		printf("ERROR\n");
		exit(-1);
 	}

	pthread_join (first, NULL);
	pthread_join (second, NULL);
	return 0;
}
