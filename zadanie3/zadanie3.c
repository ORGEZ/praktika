#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 3

int global_i = 1;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait;


void *polez_rab(void *num)
{
    long t_num;
    t_num = (long) num;

    pthread_mutex_lock(&mut);
    global_i++;
    pthread_mutex_unlock(&mut); 
    sleep (global_i);
    printf("Поток #%ld - выполнение работы завершено!\n", t_num);
    pthread_mutex_lock(&mut);
    if (global_i != 1 + NUM_THREADS)
    {
            pthread_cond_wait(&wait, &mut);
    }
    else
    {
        pthread_mutex_unlock(&mut); 
        pthread_cond_broadcast(&wait);
    }   
}


int main (){
    pthread_cond_init(&wait, NULL);
    pthread_t threads[NUM_THREADS];
    int rc, t;

    for(t = 0; t < NUM_THREADS; t++)
    {
        printf("In main: creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, polez_rab, (void*) t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
        printf("Thread #%d finished\n", t);
    }
return 0;
}
