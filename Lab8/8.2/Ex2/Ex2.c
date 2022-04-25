#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define SEED 35791246

int count = 0; // the number of points inside circle
sem_t sem;
void* monteCarlo(void *arg) {
	double x, y, z; 
	
	/* initialize random numbers */
	srand(SEED);
	
	int n = (*(int*)arg);
	
	int i;
	for(i = 0; i < n; i++) {
		x = (double)rand()/RAND_MAX;
		y = (double)rand()/RAND_MAX;
		z = x*x + y*y;
		if (z <= 1) {
			sem_wait(&sem);
			count++;
			sem_post(&sem);
		}
	}
}

int main(int argc, char* argv) {
	int numberOfiterations;
	printf("Enter the number of iterations used to estimate pi: ");
	scanf("%d",&numberOfiterations);
	
	sem_init(&sem, 0, 1);
	int numberOfThreads;
	
	printf("Enter num of thread: ");
	scanf("%d", &numberOfThreads);
	
	pthread_t t[numberOfThreads];
	int leng = numberOfiterations / numberOfThreads; // divide the same number of iterations for each thread to deal with
	
	int i;
	for (i = 0; i < numberOfThreads; i++) {
		pthread_create(&t[i], NULL, monteCarlo, &leng);
	}
	
	for (i = 0; i < numberOfThreads; i++) {
		pthread_join(t[i], NULL);
	}
	
	double pi = (double)count / numberOfiterations * 4;
	printf("# of trials = %d , estimate of pi is %g \n", numberOfiterations, pi);
	sem_destroy(&sem);
	return 0;
}
