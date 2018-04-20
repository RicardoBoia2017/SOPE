// PROGRAMA p01.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define STDERR 2
#define NUMITER 10000

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;  // mutex p/a sec.critica


void * thrfunc(void * arg) {
	pthread_mutex_lock(&mut);

	int i;
	int * count = malloc (sizeof(int));
	* count = 0;

	fprintf(stderr, "Starting thread %s\n", (char *) arg);
	for (i = 1; i <= NUMITER; i++)
	{
		write(STDERR, arg, 1);
		(*count) ++;
	}


	pthread_mutex_unlock(&mut);

	return (void*) count;
}

int main() {
	pthread_t ta, tb;
	void * n1, * n2;

	pthread_create(&ta, NULL, thrfunc, "1");
	pthread_create(&tb, NULL, thrfunc, "2");

	pthread_join(ta, &n1);
	pthread_join(tb, &n2);

	printf ("Thread A: %d\n", *(int *)n1);
	printf ("Thread B: %d\n", *(int *)n2);

	return 0;
}
