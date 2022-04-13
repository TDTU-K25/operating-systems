#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

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
	int fp1[2],
	    fp2[2],
	    fp3[2],
	    fp4[2],
	    a,
	    b;
	char operator;
	int pid;
	
	if (argc < 4) {
		printf("Doi so thieu.\n");
		return -1;
	}
	
	if (pipe(fp1) == 0 && pipe(fp2) == 0 && pipe(fp3) == 0 && pipe(fp4) == 0) {
		pid = fork();
		
		if (pid < 0) {
			printf("Fork failed\n");
			return -1;
		}
		
		else if (pid == 0) { // Child process
			close(fp1[1]);
			read(fp1[0], &a, sizeof(a));
			close(fp1[0]);
			
			close(fp2[1]);
			read(fp2[0], &b, sizeof(b));
			close(fp2[0]);
			
			close(fp3[1]);
			read(fp3[0], &operator, sizeof(operator));
			close(fp3[0]);
			
			int res = caculator(a, b, operator);
			close(fp4[0]);
			write(fp4[1], &res, sizeof(res));
			close(fp4[1]);
		}
		
		else { // Parent process
			close(fp1[0]);
			int c = atoi(argv[1]);
			write(fp1[1], &c, sizeof(c));
			close(fp1[1]);
			
			close(fp2[0]);
			int d = atoi(argv[2]);
			write(fp2[1], &d, sizeof(d));
			close(fp2[1]);
			
			close(fp3[0]);
			char tempString[1];
			strcpy(tempString, argv[3]);
			char tempOperator = tempString[0];
			write(fp3[1], &tempOperator, sizeof(tempOperator));
			close(fp3[1]);

			
			close(fp4[1]);
			int temp;
			read(fp4[0], &temp, sizeof(temp));
			close(fp4[0]);
			
			printf("%d %c %d = %d\n", c, tempOperator, d, temp);
		}
	}
}
