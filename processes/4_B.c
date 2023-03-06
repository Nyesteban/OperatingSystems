#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd_fifo = open("fifo4",O_RDONLY);
	if(fd_fifo==-1)
	{
		perror("Error on fifo");
		exit(1);
	}
	char value=0;
	read(fd_fifo,&value,1);
	printf("ASCII: %hhu\n",value);
	close(fd_fifo);
	unlink("fifo4");
	return 0;
}
