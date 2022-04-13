#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <fcntl.h> 
#define FIFO1 "/tmp/ff.1"
#define FIFO2 "/tmp/ff.2"
#define PM 0666
extern int errno;
#define PIPE_BUF 4096

int factorial(int n) {
	int i;
	int product = 1;
	for (i = 1; i <= n; i++) {
		product *= i;
	}
	return product;
}

int main(int argc, char* argv[]) {
	int buffer;
	int childpid, readfd, writefd;
	
	if (atoi(argv[1]) < 4) {
		printf("Doi so sai.\n");
		return -1;
	}
	
	if((mknod(FIFO1, S_IFIFO | PM, 0) < 0) && (errno != EEXIST)) {
		printf("Fail to create FIFO1. Aborted.\n");
		return -1;
	}
	
	if((mknod(FIFO2, S_IFIFO | PM, 0) < 0) && (errno != EEXIST)) {
		unlink(FIFO1);
		printf("Fail to create FIFO2. Aborted.\n");
		return -1;
	}

	childpid=fork();
	if(childpid == 0) { // Child process
		if((readfd=open(FIFO1, 0)) < 0)
			perror("Child cannot open readFIFO.\n");
		if((writefd=open(FIFO2, 1)) < 0)
			perror("Child cannot open writeFIFO.\n");
		read(readfd, &buffer, sizeof(buffer));
		printf("Child read from parent: %d\n", buffer);
		
		int result = factorial(buffer);
		write(writefd, &result, sizeof(result));
		printf("Data from child: %d\n", result);
		close(readfd);
		close(writefd);
		return 1;
	}
	
	else if(childpid > 0) { // Parent process
		printf("Date from parent: %s\n", argv[1]);
		if((writefd=open(FIFO1, 1)) < 0)
			perror("Parent cannot open writeFIFO.\n");
		if((readfd=open(FIFO2, 0)) < 0)
			perror("Child cannot open readFIFO.\n");
		int n = atoi(argv[1]);
		write(writefd, &n, sizeof(n));
		printf("Already write\n");
		
		int temp;
		read(readfd, &temp, sizeof(temp)); 
		printf("Data get from child: %d\n", temp);
		close(writefd);
		close(readfd);
		
		
		
		if(unlink(FIFO1) < 0)
			perror("Cannot remove FIFO1.\n");
		if(unlink(FIFO2) < 0)
			perror("Cannot remove FIFO2.\n");
		return 1;
	}
	else { 
		printf("Fork failed\n"); 
		return -1;
	}	
}
