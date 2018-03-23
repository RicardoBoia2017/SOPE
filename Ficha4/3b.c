// PROGRAMA p02a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int adder = 1;

void sigusr_handler(int signo) {

	if (signo == SIGUSR1)
		adder = 1;
	else if (signo == SIGUSR2)
		adder = -1;
}

int main(void) {
	int v = 0;
	int pid;



	/*struct sigaction action;
	action.sa_handler = sigusr_handler;
	action.sa_flags = 0;
	sigemptyset(& (action.sa_mask));*/

	if (signal(SIGUSR1, sigusr_handler) < 0) {
			fprintf(stderr, "Unable to install SIGUSR1 handler\n");
			exit(1);
	}

	if (signal(SIGUSR2, sigusr_handler) < 0) {
		fprintf(stderr, "Unable to install SIGUSR2 handler\n");
		exit(1);
	}

	pid = fork();

	srand(time(NULL));

	if (pid < 0) {
		fprintf(stderr, "ERROR]: fork() returned negative value\n");
		exit(1);
	}

	else if (pid == 0) //filho
	{

	}

	else if (pid > 0) //pai
	{
		int i;
		for (i = 0; i < 50; i++) {
			int tmp = rand() % 2;

			if (tmp == 0)
			{
				kill(pid, SIGUSR1);
			}
			else {
				kill(pid, SIGUSR2);
			}
			sleep(1);

		}
		kill(pid, SIGTERM);
	}
	while(1){
		printf("Value = %d\n", v);
		v += adder;
		sleep(1);
	}


}
