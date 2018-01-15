#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
int main()
{
        int fd[4],i, len;
        int pid;
        pipe(fd);
        pipe(fd+2);
        pid = fork();
        if (pid == 0)
        {
                char buff[20];
                close(fd[0]);
                close(fd[3]);
                read(fd[2], buff, sizeof(buff));
                printf("Recieved input from parent\n");
                printf("The file name recieved is : ");
	 	fputs(buff,stdout);
		int fdfile;
		int length=strlen(buff);
		char new[length-1];
		int i;
		for( i=0;i<length-1;i++)
		{
			new[i]=buff[i];
		}
		fdfile=open(new,sizeof(new));
		if(fdfile<0)
		{
			printf("Error in the filename\n");
		}
		else
		{
			printf("File opened successfully\n");
                }
		char buffer[1024];
		int n;
		while((n=read(fdfile,buffer,sizeof(buffer)))>0)
		{
			write(fd[1],buffer,n);
		}
		close(fd[1]);
                close(fd[2]);
                return 0;
        }
        else
        {
                close(fd[1]);
                close(fd[2]);
                char name[100];
                printf("Enter the name of the file \n");
               	fgets(name,100,stdin);
                printf("Sending input from parent\n");
                write(fd[3],name,sizeof(name));
		int n;
		char buffer[1024];
		while((n=read(fd[0],buffer,sizeof(buffer)))>0)
		{
			write(1,buffer,n);
		}
		close(fd[0]);
		close(fd[3]);
	}
}
                                         

