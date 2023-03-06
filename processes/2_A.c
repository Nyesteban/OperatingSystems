#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int gcd(int a, int b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

int main(int argc, char** argv)
{
	int nr1,nr2;
	if(argc!=2)
	{
		printf("This program receives exactly one argument.\n");
		return 1;
	}
	mkfifo(argv[1],0600);
	int fd_fifo=open(argv[1],O_WRONLY);
	if(fd_fifo==-1)
	{
		perror("Error on fifo");
		exit(1);
	}
	scanf("%d %d",&nr1,&nr2);
	int ans=nr1*nr2/gcd(nr1,nr2);
	write(fd_fifo,&ans,sizeof(int));
	close(fd_fifo);
	return 0;
}
