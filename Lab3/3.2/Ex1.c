#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int sum_n(int n) {
	int sum = 0;
	int i;
	for (i = 1; i <= n; i++) {
		sum += i;
	}
	return sum;
}

int sum_of_div_n(int n) {
	int sum = 0;
	int i;
	for (i = 1; i <= n; i++) {
		if (n % i == 0) {
			sum += i;
		}
	}
	return sum;
}

void main(int argc, char ** argv) {
	pid_t pid;
	int n = atoi(argv[1]);
	if (n <= 0) {
		printf("Doi so khong la so nguyen duong\n");
	}
	else {
		pid = fork();
		if (pid == 0) { // child process
			printf("Sum of divisor of %d = %d\n", n, sum_of_div_n(n));
		}
		else if (pid > 0) { // parent process
			printf("Sum of 1 to %d = %d\n", n, sum_n(n));
			wait(NULL);
		}
	}
}
