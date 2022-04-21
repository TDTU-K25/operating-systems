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

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void ascendSort(int arr[], int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (arr[i] > arr[j]) {
				swap(&arr[i], &arr[j]);
			}
		}
	}
}

int sumOfNumsInSequence(int arr[], int n) {
	int i;
	int sum = 0;
	for (i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

void printArray(int arr[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	key_t key;
	key = ftok("msg.txt",1);
	
	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	Sequence lists[countRowsOfFile("data.txt")];
	
	msgrcv(msgid, &lists, sizeof(lists),1,0);
	int i;
	for (i = 0; i < countRowsOfFile("data.txt"); i++) {
		ascendSort(lists[i].arr, lists[i].n);
		printArray(lists[i].arr, lists[i].n);
		printf("Sum = %d\n", sumOfNumsInSequence(lists[i].arr, lists[i].n));
	}
	
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
