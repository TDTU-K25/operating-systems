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

	int count = 0;
	int i;
	for (i = 0; i < 10; i++) {
			printf("Enter setence: ");
			gets(buffer[i].str);
			count++;
			if (strcmp(buffer[i].str, "Exit") == 0) {
				count--;
				break;
			} 	
	}
	buffer[0].numberOfSetence = count; 
	
	shmdt((void*) buffer);
	return 0;
}
