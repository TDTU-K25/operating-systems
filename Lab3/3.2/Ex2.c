#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void collatzSequence (int n) {
	while (n != 1) {
		if (n % 2 != 0) {
			printf("%d, ", n);
			n = 3*n + 1;
		}
		else {
			printf("%d, ", n);
			n /= 2;
		}
	}
	printf("%d\n", n);
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
			collatzSequence(n);
		}
		else if (pid > 0) { // parent process
			wait(NULL);
			printf("Ket thuc tien trinh con\n");
		}
	}
}
