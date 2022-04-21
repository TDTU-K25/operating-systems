#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 256

int factorial(int n) {
	int i;
	int product = 1;
	for (i = 1; i <= n; i++) {
		product *= i;
	}
	return product;
}

int main(int argc, char* argv[]) {
	int *shm, shmid;
	key_t key;

	// ftok to generate unique key
	if((key=ftok(".", 65))==-1){
		perror("Key created.\n");
		return 1;
	}

	// Create random shared memory with key above
	shmid = shmget(key, SIZE, IPC_CREAT | 0666);
	if (shmid == -1) {
		perror("Shared memory created.\n");
		return 2;
	}

	// shm is shared between processes
	shm = (int*) shmat(shmid, 0, 0);

	sleep(1);
	shm[1] = factorial(shm[0]);
	
	// remove shm from shared memory
	shmdt((void*) shm);
	return 0;
}
