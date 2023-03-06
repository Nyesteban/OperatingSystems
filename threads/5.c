#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
	char* filename;
	int n;
	char c;
}triplet;

void* thread1(void* arg)
{
	char* filename = ((triplet*)arg)->filename;
	int n = ((triplet*)arg)->n;
	char c = ((triplet*)arg)->c;
	FILE *f = fopen(filename,"r");
	char scanned;
	int nr=0;
	while(fscanf(f,"%c",&scanned)==1)
	{
		if(nr==n)
		{
			if(scanned==c)
				printf("file %s, n %d, c %c: yes\n",filename,n,c);
			else
				printf("file %s, n %d, c %c: no\n",filename,n,c);
			break;
		}
		nr++;
	}
	if(nr<n)
		printf("file %s, n %d, c %c: n is too large\n",filename,n,c);
	fclose(f);
	return NULL;
}

int main(int argc, char** argv)
{
	if(argc%3!=1)
	{
		printf("Invalid argc\n");
		return 1;
	}
	pthread_t* trd = (pthread_t*)malloc(sizeof(pthread_t)*((argc-1)/3));
	triplet* trdarg = (triplet*)malloc(sizeof(triplet)*((argc-1)/3));
	for(int i=1;i<argc;i+=3)
	{
		trdarg[i/3].filename=(char*)argv[i];
		trdarg[i/3].n=atoi(argv[i+1]);
		trdarg[i/3].c=argv[i+2][0];
		pthread_create(&trd[i/3],NULL,&thread1,&trdarg[i/3]);
	}
	for(int i=1;i<argc;i+=3)
	{
		pthread_join(trd[i/3],NULL);
	}
	free(trd);
	free(trdarg);
	return 0;
}
