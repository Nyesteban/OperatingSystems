#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum=0;
pthread_mutex_t m;
pthread_cond_t c;
int maxvalue = 10000;
int turn = 0;

typedef struct
{
	int n;
	int prev;
	int next;
	int index;
}triple;

void* thread1 (void* arg)
{
	int n = ((triple*)arg)->n;
	int next = ((triple*)arg)->next;
	int prev = ((triple*)arg)->prev;
	int index = ((triple*)arg)->index;
	while(1)
	{
		pthread_mutex_lock(&m);
		while(sum<maxvalue && turn!=index)
			pthread_cond_wait(&c,&m);
		if(sum>=maxvalue)
		{
			pthread_cond_broadcast(&c);
			pthread_mutex_unlock(&m);
			break;
		}
		sum+=n;
		printf("Thread %d increments with %d, sum becomes %d\n",index,n,sum);
		if(sum%2==0)
			turn = next;
		else
			turn = prev;
		pthread_cond_broadcast(&c);
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

int main(int argc, char** argv)
{
	if(argc%3!=1)
	{
		printf ("Invalid argument count!\n");
		return 1;
	}
	pthread_mutex_init(&m,NULL);
	pthread_cond_init(&c,NULL);
	pthread_t* trd = (pthread_t*)malloc(sizeof(pthread_t)*((argc-1)/3));
	triple* ptarg = (triple*)malloc(sizeof(triple)*((argc-1)/3));
	for(int i=1;i<argc;i+=3)
	{
		ptarg[i/3].n = atoi(argv[i]);
		ptarg[i/3].next = atoi(argv[i+1]);
		ptarg[i/3].prev = atoi(argv[i+2]);
		ptarg[i/3].index = i/3;
		pthread_create(&trd[i/3],NULL,&thread1,&ptarg[i/3]);
	}
	for(int i=1;i<argc;i+=3)
	{
		pthread_join(trd[i/3],NULL);
	}
	free(trd);
	free(ptarg);
	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&c);
	return 0;
}
