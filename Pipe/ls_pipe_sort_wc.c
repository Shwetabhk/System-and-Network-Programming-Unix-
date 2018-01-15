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
                close(fd[0]);
		close(1);
		dup(fd[1]);
		int pid2,fd2[2];
		pipe(fd2);
		pid2=fork();
		if(pid2==0)
		{
			close(fd[0]);
			close(fd[1]);
			close(fd2[0]);
			close(1);
			dup(fd2[1]);
			execlp("ls","ls",NULL);
		}
		else
		{
			close(fd2[1]);
			close(0);
			dup(fd2[0]);
			execlp("sort","sort",NULL);
		}
        }
        else
        {

		close(fd[1]);
                close(0);
                dup(fd[0]);
                execlp("wc","wc",NULL);
        }
}


