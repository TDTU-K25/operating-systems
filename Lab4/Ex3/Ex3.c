#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

struct matrix {
	int a[3][3];
	char fileA[10];
	int b[3][3];
	char fileB[10];
	int c[3][3];
	char fileC[10];
	int d[3][3];
	int e[3][3];
};

void createRandomMatrix(int a[][3]) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			a[i][j] = rand() % 10;
		}
	}
}

void writeMatrixToFile(char filename[], int a[][3]) {
	FILE *fp = fopen(filename, "w");
	int i, j;
	for (i = 0; i < 3; i++) {
    		for (j = 0; j < 3; j++) {
    			fprintf(fp, "%d ", a[i][j]);
    		}
	    	fprintf(fp, "\n");
	}
	fclose(fp);
}

void* thr1(void* param) {
	struct matrix* fi = (struct matrix*) param;
	createRandomMatrix(fi->a);
	writeMatrixToFile(fi->fileA, fi->a);
	createRandomMatrix(fi->b);
	writeMatrixToFile(fi->fileB, fi->b);
}

void readMatrixFromFile(char filename[], int a[][3]) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\nCannot open file.");
		exit(1);
	}
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			fscanf(fp, "%d", &a[i][j]);
		}
	}
}

void sumMatrix(int a[][3], int b[][3], int c[][3]) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void copyMatrix(int a[][3], int b[][3]) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			b[i][j] = a[i][j];
		}
	}
}

void* thr2(void* param) {
	struct matrix* fi = (struct matrix*) param;
	readMatrixFromFile(fi->fileA, fi->d);
	readMatrixFromFile(fi->fileB, fi->e);
	sumMatrix(fi->d, fi->e, fi->c);
	writeMatrixToFile(fi->fileC, fi->c);
}

void main(int argc, char** argv) {
	pthread_t tid[2]; 
	struct matrix ABC;

	strcpy(ABC.fileA, argv[1]);
	strcpy(ABC.fileB, argv[2]);
	strcpy(ABC.fileC, argv[3]);

	srand(time(NULL));
	
	pthread_create(&tid[0], NULL, thr1, (void *) &ABC);
	pthread_join(tid[0], NULL);
	
	pthread_create(&tid[1], NULL, thr2, (void *) &ABC);
	pthread_join(tid[1], NULL);
}
