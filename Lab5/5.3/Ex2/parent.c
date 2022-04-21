#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 256

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

	shm[0] = atoi(argv[1]);
	shm[1] = atoi(argv[2]);
	char tempString[1];
	strcpy(tempString, argv[3]);
	shm[2] = tempString[0];

	sleep(3);
	
	printf("%d %c %d = %d\n", shm[0], shm[2], shm[1], shm[3]);
	shmdt((void*) shm);
	shmctl(shmid, IPC_RMID, (struct shmid_ds*) 0);
	return 1;
}
