#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

int main()
{
	int p1_2_p2[2];
	pipe(p1_2_p2);
	int k = fork();
	if(k==-1)
	{
		close(p1_2_p2[0]);
		close(p1_2_p2[1]);
		perror("Fail on fork");
		exit(1);
	}
	else if(k==0) //P1
	{
		close(p1_2_p2[0]);
		int fd = open("fifo1",O_RDONLY);
		if(fd==-1)
		{
			close(p1_2_p2[1]);
			perror("Fail on fifo");
			exit(1);
		}
		char current=0;
		int sum=0;
		while((k=read(fd,&current,1)))
		{
			if(k==-1)
				break;
			if(k>0)
				sum+=current-'0';
		}
		write(p1_2_p2[1],&sum,sizeof(int));
		close(p1_2_p2[1]);
		close(fd);
		exit(0);
	}
	k=fork();
	if(k==-1)
	{
		close(p1_2_p2[0]);
		close(p1_2_p2[1]);
		perror("Fail on fork");
		exit(1);
	}
	else if(k==0) //P2
	{
		close(p1_2_p2[1]);
		int sum=0;
		read(p1_2_p2[0],&sum,sizeof(int));
		close(p1_2_p2[0]);
		printf("divisor %d\n",1);
		for(int i=2;i<=sum/2;i++)
		{
			if(sum%i==0)
				printf("divisor %d\n",i);
		}
		printf("divisor %d\n",sum);
		exit(0);
	}
	close(p1_2_p2[0]);
	close(p1_2_p2[1]);
	wait(0);
	wait(0);
	unlink("fifo1");
	return 0;
}
