#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
	long msg_type;
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

int countRowsOfFile(char fileName[]) {
	FILE *fp;
	fp = fopen(fileName, "r");
	int count = 0;
	char s[20];
	while(fgets(s, sizeof(s), fp) != NULL) {
		count++;
	} 
	fclose(fp);
	return count;
}

int countRowsOfFileAndCountNumsInRow(char fileName[], Sequence* lists) {
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
	for (i = 0; i < countRowsOfFileAndCountNumsInRow("data.txt", lists); i++) {
		for (j = 0; j < lists[i].n; j++) {
			fscanf(fp, "%d", &lists[i].arr[j]);
		}
	}
}

int main(int argc, char* argv[]) {
	key_t key;
	key = ftok("msg.txt",1);
	
	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	Sequence lists[countRowsOfFile("data.txt")];
	lists[0].msg_type = 1;
	
	readFile(lists, "data.txt");
	msgsnd(msgid, &lists, sizeof(lists),0);
	return 0;
}
