#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	int p1_2_p2[2];
	if(pipe(p1_2_p2)==-1)
	{
		perror("Error on pipe");
		exit(1);
	}
	int k = fork();
	if(k==-1)
	{
		perror("Error on fork");
		exit(1);
	}
	else if (k==0)
	{
		close(p1_2_p2[0]);
		int fd = open(argv[1],O_RDONLY);
		if(fd==-1)
		{
			perror("Error on fifo");
			exit(1);
		}
		int div=0,sum=0;
		while((read(fd,&div,4)))
		{
			sum+=div;
		}
		write(p1_2_p2[1],&sum,4);
		close(p1_2_p2[1]);
		close(fd);
		exit(0);
	}
	k=fork();
	if(k==-1)
	{
		perror("Error on fork");
		wait(0);
		exit(1);
	}
	else if(k==0)
	{
		close(p1_2_p2[1]);
		int sum=0;
		read(p1_2_p2[0],&sum,4);
		close(p1_2_p2[0]);
		printf("Sum: %d\n",sum);
		exit(0);
	}
	close(p1_2_p2[0]);
	close(p1_2_p2[1]);
	wait(0);
	wait(0);
	unlink(argv[1]);
}
