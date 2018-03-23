#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

#define READ 0
#define WRITE 1

int main(void)
{
	int	fd[2];
	int fe[2]
	pid_t pid;

	pipe (fd);
	pipe (fe);

	pid = fork();

	if (pid >0)//pai
	{
		int	a[2];
		int res;
		printf("PARENT:\n"		);
		printf("x y ? ");
		scanf("%d %d",&a[0],&a[1]);
		close(fd[READ]);
		write(fd[WRITE],a,2*sizeof(int));
		close(fd[WRITE]);
		wait();
		close (fe[WRITE]);
		read (fe[READ], res, sizeof(int));
		close(fe[READ]);
		printf ("%d", res);

	}
	else //filho
	{
		int	b[2];//printf("SON:\n");
		close(fd[WRITE]);
		read(fd[READ],b,2*sizeof(int));
		printf("SON:\n");//WHY HERE AND NOT ABOVE ...?!
		int res = b[0] + b[1];
		close(fd[READ]);
		close(fe[READ]);
		write(fd[WRITE],res,2*sizeof(int));
		close (fe[WRITE]);
	}
	return 0;
}
