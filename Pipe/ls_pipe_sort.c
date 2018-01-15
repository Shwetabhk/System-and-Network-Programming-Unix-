#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
void main()
{
	int pid,fd[2];
	pipe(fd);
	pid=fork();
	if(pid==0)
	{
		printf("Child Process Running \n");
		close(fd[0]);
		close(1);
		dup(fd[1]);
		execlp("ls","ls",NULL);
	}
	else
	{
		printf("Parent Process Running\n");
		close(fd[1]);
		close(0);
		dup(fd[0]);
		execlp("sort","sort",NULL);
	}
}

