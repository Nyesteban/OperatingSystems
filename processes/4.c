#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char** argv)
{	
	struct timeval tv1, tv2;
	if (argc < 2)
	{
		printf("Please provide at least one argument.\n");
		exit(1);
	}
	gettimeofday(&tv1, NULL);
	int f = fork();
	if(f==-1)
	{
		perror("Error on fork");
		exit(1);
	}
	else if(f==0)
	{
		if(execvp(argv[1], argv+1)==-1)
		{
			perror("Error running the given command: ");
			exit(1);
		}
	}
	else
	{
		wait(0);
		gettimeofday(&tv2, NULL);
		printf("Total time = %f seconds\n",(double)(tv2.tv_usec-tv1.tv_usec)/1000000+(double)(tv2.tv_sec-tv1.tv_sec));
	}
	return 0;
}
