#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	if(argc!=2)
	{
		printf("This program takes exactly one argument.\n");
		return 1;	
	}
	int p1_2_p2[2];
	pipe(p1_2_p2);
	int k=fork();
	if(k==-1)
	{
		close(p1_2_p2[0]);
		close(p1_2_p2[1]);
		perror("Error on fork");
		exit(1);
	}
	else if (k==0)
	{
		close(p1_2_p2[0]);
		FILE *f = fopen(argv[1],"r");
		if(f==NULL)
		{
			close(p1_2_p2[1]);
			perror("Error on file");
			exit(1);
		}
		int value=0,n=0;
		scanf("%d",&n);
		while(n!=0 && fscanf(f,"%d",&value)==1)
		{
			write(p1_2_p2[1],&value,4);
			n--;
		}
		close(p1_2_p2[1]);
		fclose(f);
		exit(0);
	}
	k = fork();
	if (k==-1)
	{
                close(p1_2_p2[0]);
		close(p1_2_p2[1]);
		perror("Error on fork");
		exit(1);
	}
	else if (k==0)
	{
		close(p1_2_p2[1]);
		int value=0,sum=0;
		while(read(p1_2_p2[0],&value,4)>0)
		{
			if(value%2==1)
				sum+=value;
		}
		close(p1_2_p2[0]);
		mkfifo("fifo3",0600);
		int fd_fifo = open("fifo3",O_WRONLY);
		if(fd_fifo==-1)	
		{
			perror("Error on fifo");
			wait(0);
			exit(1);
		}
		write(fd_fifo,&sum,4);
		close(fd_fifo);
		exit(0);
	}
	close(p1_2_p2[0]);
	close(p1_2_p2[1]);
	wait(0);
	wait(0);
	return 0;
}
