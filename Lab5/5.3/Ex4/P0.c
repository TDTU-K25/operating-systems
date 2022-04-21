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
	int arr[10];
	int n;
} Sequence;

int countNumsInRow(char s[]) {
	int count = 0;
	int i;
	for (i = 0; i < strlen(s); i++) {
		if (s[i] == ' ') {
			count++;
		}
	}
	return count + 1;
}

int countRowsOfFile(char fileName[], Sequence* lists) {
	FILE *fp;
	fp = fopen(fileName, "r");
	int count = 0;
	char s[20];
	while(fgets(s, sizeof(s), fp) != NULL) {
		lists[count].n = countNumsInRow(s);
		count++;
	} 
	fclose(fp);
	return count;
}


void readFile(Sequence* lists, char fileName[]) {
	FILE *fp;
	fp = fopen(fileName, "r");
	char s[20];
	int i, j;
	for (i = 0; i < countRowsOfFile("data.txt", lists); i++) {
		for (j = 0; j < lists[i].n; j++) {
			fscanf(fp, "%d", &lists[i].arr[j]);
		}
	}
}

int main(int argc, char* argv[]) {
	key_t key;
	if((key=ftok(".", 65))==-1){
		perror("Key created.\n");
		return 1;
	}

	int shmid = shmget(key, SIZE, IPC_CREAT | 0666);
	if (shmid == -1) {
		perror("Shared memory created.\n");
		return 2;
	}
	
	Sequence* lists = (Sequence*) shmat(shmid, 0, 0);
	readFile(lists, "data.txt");

	shmdt((void*) lists);
	return 0;
}
