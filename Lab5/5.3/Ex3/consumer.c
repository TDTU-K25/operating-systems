#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 1024

typedef struct {
	char str[40];
	int numberOfSetence;
} StringList;

int main(int argc, char* argv[]) {
	key_t key;
	if((key = ftok(".", 65)) == -1){
		perror("Key created.\n");
		return 1;
	}

	int shmid = shmget(key, SIZE, IPC_CREAT | 0666);
	if (shmid == -1) {
		perror("Shared memory created.\n");
		return 2;
	}
	
	StringList* buffer = (StringList*) shmat(shmid, 0, 0);

	int i;
	for (i = 0; i < buffer[0].numberOfSetence; i++) {
		printf("Item from Producer: %s\n", buffer[i].str);
	}

	shmdt((void*) buffer);
	shmctl(shmid, IPC_RMID, (struct shmid_ds*) 0);
	return 1;
}
