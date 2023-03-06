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
		printf("Program takes exactly one argument.\n");
		exit(1);
	}
	if(0>mkfifo(argv[1],0600))
	{
		perror("Error on fifo");
		exit(1);
	}
	int nr;
	scanf("%d",&nr);
	int fd = open(argv[1],O_WRONLY);
	if(fd==-1)
	{
		perror("Error on fifo");
		exit(1);
	}
	for(int i=1;i<=nr;i++)
	{
		if(nr%i==0)
			write(fd,&i,4);
	}
	close(fd);
	return 0;
}
