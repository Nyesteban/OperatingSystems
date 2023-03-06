#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv)
{
	char filename[51];
	scanf("%s",filename);
	int fd_file;
	fd_file=open(filename,O_RDONLY);
	if(fd_file==-1)
	{
		perror("Error opening file");
		exit(1);
	}
	if(0>mkfifo("fifo1",0600))
	{
		perror("Error making fifo");
		exit(1);
	}
	int fd_fifo = open("fifo1", O_WRONLY);
	char current=0;
	int k=0;
	while((k=read(fd_file,&current,1)))
	{
		if(k==-1)
			break;
		if(k>0)
		{
			if(current>='0' && current<='9')
				write(fd_fifo,&current,1);
		}
	}
	close(fd_file);
	close(fd_fifo);
	return 0;
}
