#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int f;

void parent_handler(int sig)
{
	printf("Parent process terminating...\n");
	kill(f,SIGUSR1);
	wait(0);
	exit(0);
}

void child_handler(int sig)
{
	printf("Child process terminating...");
	exit(0);	
}

void zombie_handler(int sig)
{
	printf("Parent waiting for child process to terminate...\n");
	wait(0);	
}

int main()
{
	f=fork();
	if(f==-1)
		perror("Error on fork");
	else if(f==0)
	{
		signal(SIGUSR1, child_handler);
		printf("Child- PID:%d, PPID:%d\n",getpid(),getppid());
		while(1)
		{
			printf("Child working...\n");
			sleep(3);
		}
		exit(0);
	}
	else
	{
		signal(SIGUSR1, parent_handler);
		signal(SIGCHLD, zombie_handler);
		printf("Parent- Child ID:%d, PID:%d\n",f,getpid());
		while(1)
		{
			printf("Parent working...\n");
			sleep(2);
		}
	}
	return 0;
}
