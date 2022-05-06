#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#define SEED 35791246

int count = 0; // the number of points inside circle

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* monteCarlo(void* arg) {
	double x, y, z;
	
	/* initialize random numbers */
	srand(SEED);
	int n = (*(int*)arg);
	
	int i;
	for (i = 0; i < n; i++) {
		x = (double)rand()/RAND_MAX;
		y = (double)rand()/RAND_MAX;
		z = x*x + y*y;
		if (z <= 1) {
			pthread_mutex_lock(&mutex);
			count++;
			pthread_mutex_unlock(&mutex);
		}
	}
}

int main(int argc, char* argv) {
	int numberOfIterations;
	printf("Enter the number of iterations used to estimate pi: ");
	scanf("%d", &numberOfIterations);

	int numberOfThreads;

	printf("Enter number of thread: ");
	scanf("%d", &numberOfThreads);

	pthread_t t[numberOfThreads];
	int leng = numberOfIterations / numberOfThreads; // divide the same number of iterations for each thread to deal with

	int i;
	for (i = 0; i < numberOfThreads; i++) {
		pthread_create(&t[i], NULL, monteCarlo, &leng);
	}

	for (i = 0; i < numberOfThreads; i++) {
		pthread_join(t[i], NULL);		
	}

	double pi = (double)count / numberOfIterations * 4;
	printf("# of trials = %d, estimate of pi is %g\n", numberOfIterations, pi);
	return 0;
}
