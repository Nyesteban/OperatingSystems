#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc!=2)
	{
		printf("This program takes exactly 2 arguments.\n");
		return 1;
	}
	int p1_2_p2[2];
	pipe(p1_2_p2);
	int k = fork();
	if(k==-1)
	{
		close(p1_2_p2[0]);
		close(p1_2_p2[1]);
		perror("Error on fork");
		exit(1);
	}
	else if (k==0) //P1
	{
		close(p1_2_p2[0]);
		int fd_fifo = open(argv[1],O_RDONLY);
		if(fd_fifo==-1)
		{
			close(p1_2_p2[1]);
			perror("Error on fifo");
			exit(1);
		}
		int ans;
		read(fd_fifo,&ans,sizeof(int));
		close(fd_fifo);
		for(int i=1;i<=ans;i++)
			if(ans%i==0)
				write(p1_2_p2[1],&i,sizeof(int));
		close(p1_2_p2[1]);
		exit(0);
	}
	k=fork();
	if(k==-1)
	{
		close(p1_2_p2[0]);
        	close(p1_2_p2[1]);
		wait(0);
		perror("Error on fork");
		exit(1);
	}
	else if(k==0)
	{
		close(p1_2_p2[1]);
		int nr=0;
		while(read(p1_2_p2[0],&nr,sizeof(int))>0)
			printf("%d\n",nr);
		close(p1_2_p2[0]);
		exit(0);
	}
	close(p1_2_p2[0]);
	close(p1_2_p2[1]);
	wait(0);
	wait(0);
	unlink(argv[1]);
	return 0;
}
