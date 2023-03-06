#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd_fifo = open("fifo3",O_RDONLY);
	if(fd_fifo==-1)
	{
		perror("Error on fifo");
		exit(1);
	}
	int value;
	read(fd_fifo,&value,4);
	printf("%d\n",value);
	close(fd_fifo);
	unlink("fifo3");
	return 0;
}
