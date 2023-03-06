#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int letters;
int digits;
pthread_mutex_t mutexes;

void* worker(void* args)
{
	FILE *f = fopen((char*)args,"r");
	char c;
	int local_letters = 0;
	int local_digits = 0;
	while(fscanf(f,"%c",&c) == 1)
	{
		if(c>='0' && c <= '9')
			local_digits++;
		else if((c>='a' && c<='z') || (c>='A' && c<='Z'))
			local_letters++;
	}
	fclose(f);
	pthread_mutex_lock(&mutexes);
	letters+=local_letters;
	digits+=local_digits;
	pthread_mutex_unlock(&mutexes);
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t* trd = (pthread_t*)malloc(sizeof(pthread_t)*(argc-1));
	pthread_mutex_init(&mutexes, NULL);
	for(int i=1;i<argc;i++)
	{
		pthread_create(&trd[i-1],NULL,&worker,(void*)argv[i]);
	}
	for(int i=1;i<argc;i++)
	{
		pthread_join(trd[i-1],NULL);
	}
	printf("%d %d\n",letters,digits);
	free(trd);
	pthread_mutex_destroy(&mutexes);
	return 0;
}
