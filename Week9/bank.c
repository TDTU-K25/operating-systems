#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

struct file {
	char fileName[10];
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static int balance = 0;

int countNumberInFile(char fileName[]) {
	FILE *fp = fopen(fileName, "r");
	
	int count = 0;
	int num;

	while(!feof(fp)) {
		fscanf(fp, "%d", &num);
		count++;
	}
	return count;
}

void* thr1(void *arg) {
	struct file *fi = (struct file*) arg;
	FILE *fp = fopen(fi->fileName, "r");
	pthread_mutex_lock(&mutex);
	int i;
	for (i = 1; i < countNumberInFile(fi->fileName); i++) {
		char s[10];
		fgets(s, sizeof(s), fp);
		int transaction = atoi(s);
		balance += transaction;
		printf("File name: %s, transaction = %d, balance = %d\n", fi->fileName, transaction, balance);
		if (balance < 0) {
			printf("Warning: Balance under 0.00\n");
		}
	}
	pthread_mutex_unlock(&mutex);		
}

void main(int agrc, char** argv) {
	pthread_t tid[4];
	struct file data[agrc - 1];
	int i;
	for (i = 0; i < agrc - 1; i++) {
		strcpy(data[i].fileName, argv[i+1]);
		pthread_create(&tid[i], NULL, thr1, &data[i]);
	}

	for (i = 0; i < agrc - 1; i++) {
		pthread_join(tid[i], NULL);
	}

	printf("Final balance = %d\n", balance);
}
