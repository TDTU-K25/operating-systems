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

int main(int argc, char* argv[]) {
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

	if((writefd=open(FIFO1, 1)) < 0)
		perror("Child cannot open writeFIFO.\n");
		
	int c = atoi(argv[1]);
	write(writefd, &c, sizeof(c));
		
	if((writefd=open(FIFO2, 1)) < 0)
		perror("Child cannot open writeFIFO.\n");
		
	int d = atoi(argv[2]);
	write(writefd, &d, sizeof(d));
		
	if((writefd=open(FIFO3, 1)) < 0)
		perror("Child cannot open writeFIFO.\n");
		
	char tempString[1];
	strcpy(tempString, argv[3]);
	char tempOperator = tempString[0];
	write(writefd, &tempOperator, sizeof(tempOperator));
		
	if((readfd=open(FIFO4, 0)) < 0)
		perror("Child cannot open readFIFO.\n");
		
	int temp;
	read(readfd, &temp, sizeof(temp));
		
	printf("%d %c %d = %d\n", c, tempOperator, d, temp);
	close(readfd);
	close(writefd);
	return 1;	
}
