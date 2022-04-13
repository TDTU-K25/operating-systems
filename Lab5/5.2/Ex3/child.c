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
#define FIFO3 "/tmp/ff.3"
#define FIFO4 "/tmp/ff.4"
#define PM 0666
extern int errno;
#define PIPE_BUF 4096

int caculator(int a, int b, char operator) {
	switch(operator) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
	}
}

int main(int argc, char* argv[]) {
	int a,
	    b;
	char operator;
	int readfd, writefd;
	
	if((mknod(FIFO1, S_IFIFO | PM, 0) < 0) && (errno != EEXIST)) {
		printf("Fail to create FIFO1. Aborted.\n");
		return -1;
	}
	
	if((mknod(FIFO2, S_IFIFO | PM, 0) < 0) && (errno != EEXIST)) {
		unlink(FIFO1);
		printf("Fail to create FIFO2. Aborted.\n");
		return -1;
	}
	
	if((mknod(FIFO3, S_IFIFO | PM, 0) < 0) && (errno != EEXIST)) {
		unlink(FIFO1);
		unlink(FIFO2);
		printf("Fail to create FIFO3. Aborted.\n");
		return -1;
	}
	
	if((mknod(FIFO4, S_IFIFO | PM, 0) < 0) && (errno != EEXIST)) {
		unlink(FIFO1);
		unlink(FIFO2);
		unlink(FIFO3);
		printf("Fail to create FIFO4. Aborted.\n");
		return -1;
	}

	if((readfd=open(FIFO1, 0)) < 0)
		perror("Child cannot open readFIFO.\n");
		
	read(readfd, &a, sizeof(a));
		
	if((readfd=open(FIFO2, 0)) < 0)
		perror("Child cannot open readFIFO.\n");
		
	read(readfd, &b, sizeof(b));
		
	if((readfd=open(FIFO3, 0)) < 0)
		perror("Child cannot open readFIFO.\n");
		
	read(readfd, &operator, sizeof(operator));
		
	if((writefd=open(FIFO4, 1)) < 0)
		perror("Child cannot open writeFIFO.\n");
		
	int res = caculator(a, b, operator);
	write(writefd, &res, sizeof(res));
		
	close(readfd);
	close(writefd);
	return 1;
}
