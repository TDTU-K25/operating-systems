#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int fp[2];
	char buffer[256];
	int pid;
	
	if (argc < 2) {
		printf("Doi so thieu.\n");
		return -1;
	}
	
	// NOTES: fp[0] is set up for reading, fp[1] is set up for writing
	// If the parent wants to receive data from the child, it should close fp[1], and the child should close fp[0]. If the parent wants to send data to the child, it should close fp[0], and the child should close fp[1].
	
	if (pipe(fp) == 0) {
		pid = fork();
		
		if (pid < 0) {
			printf("Fork failed\n");
			return -1;
		}
		
		else if (pid == 0) { // Child process
		        /* Child process closes up output side of pipe -> close write*/
			close(fp[1]); 
			read(fp[0], buffer, sizeof(buffer)); // open read
			printf("Read from parent: %s\n", buffer);
		}
		
		else { // Parent process
			/* Parent process closes up input side of pipe -> close read*/
			printf("Data from parent: %s\n", argv[1]);
			close(fp[0]); 
			write(fp[1], argv[1], strlen(argv[1])); // open write
			wait(NULL);
		}
	}
}
