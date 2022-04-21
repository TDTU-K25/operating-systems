#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 256

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
	int *shm, shmid;
	key_t key;

	if((key=ftok(".", 65))==-1){
		perror("Key created.\n");
		return 1;
	}

	shmid = shmget(key, SIZE, IPC_CREAT | 0666);
	if (shmid == -1) {
		perror("Shared memory created.\n");
		return 2;
	}

	shm = (int*) shmat(shmid, 0, 0);

	sleep(1);
	shm[3] = caculator(shm[0], shm[1], shm[2]);
	shmdt((void*) shm);
	return 0;
}
