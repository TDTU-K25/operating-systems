#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void main() {
	pid_t pid;
	pid = fork();
	if (pid > 0) { // parent process
		printf("Hello %d\n", getpid());
		sleep(10);
		wait(NULL);
	}
	else if (pid == 0) { // child process
		printf("Child %d\n", getpid());
		exit(0);
	}
	else {
		printf("Error\n");
	}
}
