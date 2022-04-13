#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int factorial(int n) {
	int i;
	int product = 1;
	for (i = 1; i <= n; i++) {
		product *= i;
	}
	return product;
}

int main(int argc, char* argv[]) {
	int fp1[2],
	    fp2[2];
	int buffer;
	int pid;
	
	if (argc < 2) {
		printf("Doi so thieu.\n");
		return -1;
	}
	
	if (atoi(argv[1]) < 3) {
		printf("Doi so sai.\n");
		return -1;
	}
	
	if (pipe(fp1) == 0 && pipe(fp2) == 0) {
		pid = fork();
		
		if (pid < 0) {
			printf("Fork failed\n");
			return -1;
		}
		
		else if (pid == 0) { // Child process
			close(fp1[1]);
			read(fp1[0], &buffer, sizeof(buffer));
			printf("Read from parent: %d\n", buffer);
			close(fp1[0]);
			
			int res = factorial(buffer);
			printf("Data send to parent: %d\n", res);
			close(fp2[0]);
			write(fp2[1], &res, sizeof(res));
			close(fp2[1]);
		}
		
		else { // Parent process
			close(fp1[0]);
			printf("Data from parent: %s\n", argv[1]);
			int n = atoi(argv[1]);
			write(fp1[1], &n, sizeof(n));
			close(fp1[1]);
			printf("Already write\n");
			
			close(fp2[1]);
			int temp;
			read(fp2[0], &temp, sizeof(temp));
			printf("Data get from child: %d\n", temp);
			close(fp2[0]);
		}
	}
}
