#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

void f(int n)
{
	if(n>0)
	{
		int k = fork();
		if(k<0)
		{
			perror("Error!\n");
			exit(1);
		}
		else if(k==0)
		{
			printf("PID=%d, PPID=%d\n",getpid(),getppid());
			f(n-1);
		}
		
	}
	wait(0);
	exit(0);
}
int main()
{
	f(3);
	return 0;
}
