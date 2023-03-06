#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

int contains_7_or_is_multiple_of_7(int nr)
{
	if(nr%7==0)
		return 1;
	while(nr>0)
	{
		if(nr%10==7)
			return 1;
		nr=nr/10;
	}
	return 0;
}

void fork_and_communicate(int pipes[][2], int index, int n)
{
	if(index + 1 < n)
	{
		int f = fork();
		if (f==-1)
		{
			perror("Error on fork");
			return;
		}
		else if (f==0)
		{
			fork_and_communicate(pipes, index+1, n);
			return;
		}
	}
	int nr=1,i;
	int read_idx = index % n;
	int write_idx = (index+1) % n;
       for(i=0;i<n;i++)
       {
	       if(i==read_idx)
		       close(pipes[i][1]);
	       else if(i==write_idx)
		       close(pipes[i][0]);
	       else
	       {
		       close(pipes[i][0]);
		       close(pipes[i][1]);
	       }
       }
	if(index==0)
	{
		printf("%d - start\n", nr);
		if(0 > write(pipes[write_idx][1],&nr, sizeof(int)))
			perror("Error on writing number");
	}
	while(nr>=1)
	{
		if(0>read(pipes[read_idx][0],&nr,sizeof(int)))
			perror("Error on reading number");
		if(nr!=0)
		{
			nr++;
			int success = random() % 3;
			if(contains_7_or_is_multiple_of_7(nr))
			{
				if(!success)
				{
					printf("%d - fail\n",nr);
					nr=0;
				}
				else
					printf("Boltz!\n");	
			}
			else
				printf("%d\n",nr);
			if(write(pipes[write_idx][1],&nr,sizeof(int))<0)
				perror("Error on writing number");
		}
		else
		{
			if(write(pipes[write_idx][1],&nr,sizeof(int))<0)
				perror("Error on writing number");
			break;	
		}
	}
	wait(0);
	close(pipes[read_idx][0]);
        close(pipes[write_idx][1]);	
}

int main(int argc, char** argv)
{
	if(argc<2)
	{
		printf("Provide an integer argument!\n");
		exit(1);
	}
	int n = atoi(argv[1]), i;
	int pipes[n][2];
	for(i=0;i<n;i++)
	{
		if(0>pipe(pipes[i]))
		{
			perror("Error on opening pipe");
			exit(1);
		}
	}
	srandom(time(NULL));
	fork_and_communicate(pipes,0,n);
	return 0;
}
