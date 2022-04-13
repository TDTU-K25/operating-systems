#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

int isPrimeNum(int n) {
	int i;
	for (i = 2; i <= n/2; i++) {
		if (n % i == 0) {
			return 0;
		}
	}
	return 1;
} 

void* printPrimeNum(void* arg) {
	int n = (*(int*) arg);
	if (isPrimeNum(n) == 1) {
		printf("%d ", n);
	}
}

int main (int argc, char ** argv) {
	int n = atoi(argv[1]);
	struct timeval start, end;
	pthread_t tid[4];
	int i = 2;
	gettimeofday(&start, NULL);
	while (i <= n) {

	pthread_create(&tid[0], NULL, printPrimeNum, &i);
	pthread_join (tid[0], NULL);
	
	i++;
	if (i > n) {
		break;
	}
	pthread_create(&tid[1], NULL, printPrimeNum, &i);
	pthread_join (tid[1], NULL);

	i++;
	pthread_create(&tid[2], NULL, printPrimeNum, &i);
	pthread_join (tid[2], NULL);

	i++;
	pthread_create(&tid[3], NULL, printPrimeNum, &i);
	pthread_join (tid[3], NULL);
	
	i++;
}

	gettimeofday(&end, NULL);
	double timeSpent = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec)));
	printf("\n%f\n", timeSpent);
}
