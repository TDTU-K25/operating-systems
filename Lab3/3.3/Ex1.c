#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printPID(pid_t temp) {
	printf("My ID: %d\n", getpid());
	printf("ID of child process: %d\n", temp);
}

void main(int argc, char ** argv) {
	printf("Current process: %d\n", getpid());
	pid_t pidAB;
	pidAB = fork(); // A sinh ra B
		if (pidAB > 0) { // parent process (A)
			printPID(pidAB); // My ID (A), ID child process (B)
			
			pid_t pidAC;
			pidAC = fork(); // A sinh ra C
			if (pidAC > 0) { // parent process (A)
				printPID(pidAC); // My ID (A), ID child process (C)
			}
			else if (pidAC == 0) { // child process (C)
				pid_t pidCH; 
				pidCH = fork(); // C sinh ra H
				if (pidCH > 0) { // parent process (C)
					printPID(pidCH);
				}
				else if (pidCH == 0) { // child process (H)
					exit(0);  
				}
			}
			wait(NULL);
		}
		else if (pidAB == 0) { // child process (B)
			pid_t pidBD;
			pidBD = fork(); // B sinh ra D
			if (pidBD > 0) { // parent process (B)
				printPID(pidBD);
				
				pid_t pidBE;
				pidBE = fork(); // B sinh ra E
				if (pidBE > 0) { // parent process (B)
					printPID(pidBE);
				}
				else if (pidBE == 0) { // child process (E)
					exit(0);
				}
			}
			else if (pidBD == 0) { // child process (D)
				exit(0); 
			} 
		}
		else {
			printf("Error\n");
		}
}

