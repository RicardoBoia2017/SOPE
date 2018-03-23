//NOT WORKING

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

struct sum
{
	char x[10];
	char y[10];
};


int main(void)
{
	int	fd[2];
	pid_t pid;
	struct sum numeros;

	pipe(fd);
	pid = fork();

	if (pid >0)//pai
	{
		printf("PARENT:\n");
		printf("x?");
		scanf("%s",&numeros.x);
		printf("y?");
		scanf("%s",&numeros.y);
		close(fd[READ]);
		write(fd[WRITE],&sum,20*sizeof(int));
		close(fd[WRITE]);
	}
	else //filho
	{
		char a[10];
		char b[10];
		close(fd[WRITE]);
		read(fd[READ],b,20*sizeof(int));
		printf("SON:\n");//WHY HERE AND NOT ABOVE ...?!
		printf("x + y = %d\n", b[0]+b[1] );//atoi(b[0]) + atoi(b[1]) );
		close(fd[READ]);
	}
	return 0;
}
