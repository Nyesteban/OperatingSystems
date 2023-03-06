#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	int i, n=3;
	for(i=0;i<n;i++)
	{
		int f = fork();
		if (f==-1)
			printf("Error\n");
		else if (f==0)
		{
			printf("Child. Child ID: %d, Parent ID: %d\n",getpid(),getppid());
			exit(0);
		}
		else
		{
			printf("Parent. Child ID: %d, Parent ID: %d\n",f,getpid());
		}

	}
	for(i=0;i<n;i++)
		wait(0);
	return 0;
}
