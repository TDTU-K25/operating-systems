#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

void main(int agrc, char ** argv) {
	pid_t pid;
	struct timeval start, end;
	gettimeofday(&start, NULL);
	pid = fork();
	if (pid == 0) { // child process
		printf("Call system to execute %s\n",argv[1]);
		system(argv[1]);
	}
	else if (pid > 0) { // parent process
		wait(NULL);
		gettimeofday(&end, NULL);
		double seconds = (end.tv_sec - start.tv_sec);
    		double micros = (end.tv_usec - start.tv_usec) / 1000000.0;
    		double elapsedTime = seconds + micros;
    		printf("The elapsed time is %f\n", elapsedTime);
	}
	else {
		printf("Error\n");
	}
}
