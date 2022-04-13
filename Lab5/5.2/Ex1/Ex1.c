#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <fcntl.h> 
#define FIFO "/tmp/ff"
#define PM 0666
extern int errno;
#define PIPE_BUF 4096

int main(int argc, char* argv[]) {
	char s[PIPE_BUF];
	int childpid, readfd, writefd;
	
	if((mknod(FIFO, S_IFIFO | PM, 0) < 0) && (errno != EEXIST)) {
		printf("Fail to create FIFO. Aborted.\n");
		return -1;
	}
	
	childpid=fork();
	if(childpid == 0) { // Child process
		if((readfd=open(FIFO, 0)) < 0)
			perror("Child cannot open readFIFO.\n");
		read(readfd, s, PIPE_BUF);
		printf("Child read from parent: %s\n", s);
		close(readfd);
		return 1;
	}
	
	else if(childpid > 0) { // Parent process
		if((writefd=open(FIFO, 1)) < 0)
			perror("Parent cannot open writeFIFO.\n");
		write(writefd, argv[1], strlen(argv[1]));
		close(writefd);
		
		if(unlink(FIFO) < 0)
			perror("Cannot remove FIFO.\n");
		return 1;
	}
	else { 
		printf("Fork failed\n"); 
		return -1;
	}	
}

