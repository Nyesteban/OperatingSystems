#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum=0;
pthread_mutex_t mutexes;

typedef struct
{
	char* filename;
	int n;
}threadst;

void* thread1 (void* args)
{
	char* filename = ((threadst*)args)->filename;
	int n = ((threadst*)args)->n;
	FILE *f = fopen(filename,"r");
	int a;
	while(n>0 && fscanf(f,"%d",&a)==1)
	{	if(a%2==0)
		{
			pthread_mutex_lock(&mutexes);
			sum+=a;
			pthread_mutex_unlock(&mutexes);
			n--;
		}
	}
	fclose(f);
	return NULL;
}

int main(int argc, char** argv)
{
	if(argc%2!=1)
	{
		printf("Invalid argc!\n");
		return 1;
	}
	pthread_mutex_init(&mutexes,NULL);
	pthread_t* trd = (pthread_t*)malloc(sizeof(pthread_t)*((argc-1)/2));
	threadst* trdarg = (threadst*)malloc(sizeof(threadst)*((argc-1)/2));
	for(int i=1;i<argc;i=i+2)
	{
		trdarg[i/2].filename = (char*)argv[i];
		trdarg[i/2].n = atoi(argv[i+1]);
		pthread_create(&trd[i/2],NULL,&thread1,&trdarg[i/2]);
	}
	for(int i=1;i<argc;i=i+2)
	{
		pthread_join(trd[i/2],NULL);
	}
	free(trd);
	free(trdarg);
	pthread_mutex_destroy(&mutexes);
	printf("%d\n",sum);
	return 0;
}
