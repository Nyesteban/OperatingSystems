#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{
	if(argc!=2)
	{
		perror("Program takes exactly one argument.\n");
		exit(1);
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
	else if(k==0)
	{
		close(p1_2_p2[0]);
		FILE *f = fopen(argv[1],"r");
		if(f==NULL)
		{
			perror("Error opening file");
			exit(1);
		}
		int n=0;
		char value=0;
		scanf("%d",&n);
		while(n-- && fscanf(f,"%c",&value)==1)
		{
			;
		}
		write(p1_2_p2[1],&value,1);
		close(p1_2_p2[1]);
		fclose(f);
		exit(0);
	}
	k = fork();
	if(k==-1)
	{
		close(p1_2_p2[0]);
		close(p1_2_p2[1]);
		perror("Error on fork");
		exit(1);
	}
	else if (k==0)
	{
		close(p1_2_p2[1]);
		char value=0;
		read(p1_2_p2[0],&value,1);
		close(p1_2_p2[0]);
		if(value>='0' && value<='9')
			printf("Value is digit\n");
		else if((value>='a' && value<='z') || (value>='A' && value<='Z'))
			printf("Value is letter\n");
		else
			printf("Value is other\n");
		if(mkfifo("fifo4",0600)<0)
		{
			perror("Error on fifo");
			exit(1);
		}
		int fd_fifo = open("fifo4",O_WRONLY);
		if (fd_fifo==-1)
		{
			perror("Error on fifo");
			exit(1);
		}
		write(fd_fifo,&value,1);
		close(fd_fifo);
		exit(0);
	}
	close(p1_2_p2[0]);
	close(p1_2_p2[1]);
	wait(0);
	wait(0);
	return 0;
}
