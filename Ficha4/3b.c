// PROGRAMA p02a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int adder = 1;

void sigusr_handler(int signo) {

	printf ("Entrou no handler\n");
	if (signo == SIGUSR1)
		adder = 1;
	else if (signo == SIGUSR2)
		adder = -1;
}

int main(void) {
	int v = 0;
	int pid;

	pid = fork();

	struct sigaction action;
	action.sa_handler = sigusr_handler;
	action.sa_flags = 0;
	sigemptyset(& (action.sa_mask));


	srand(time(NULL));

	if (pid < 0) {
		fprintf(stderr, "ERROR]: fork() returned negative value\n");
		exit(1);
	}

	else if (pid == 0) //filho
	{
		printf ("Entrou no filho");

		if (sigaction(SIGUSR1, &action, NULL) < 0) {
			fprintf(stderr, "Unable to install SIGUSR1 handler\n");
			exit(1);
		}

		if (sigaction(SIGUSR2, &action, NULL) < 0) {
			fprintf(stderr, "Unable to install SIGUSR2 handler\n");
			exit(1);
		}

		printf("Value = %d\n", v);
		v += adder;
		//sleep(1);
	}

	else if (pid > 0) //pai
	{
		int i;

		for (i = 0; i < 50; i++) {
			int tmp = rand() % 2;

			if (tmp == 0)
			{
				kill(pid, SIGUSR1);
				printf ("USR1\n");
			}
			else {
				kill(pid, SIGUSR2);
				printf ("USR2\n");
			}
			sleep(1);

		}

		kill(pid, SIGTERM);
	}

	exit(0);
}
