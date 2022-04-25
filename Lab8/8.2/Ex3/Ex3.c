#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex1, mutex2;

void SXKhung() {
	printf("San xuat khung\n");
}

void SXBanhXe() {
	printf("San xuat banh xe\n");
}

void LapRapXe() {
	printf("Lap rap xe\n");
}

void* thread1(void* arg) {
	sem_wait(&mutex2);
	SXKhung();
	sem_post(&mutex1);
}

void* thread2(void* arg) {
	int i;
	sem_wait(&mutex1);
	for (i = 0; i < 4; i++) {
		SXBanhXe();
	}
	LapRapXe();
	sem_post(&mutex2);
}

int main(int argc, char* argv) {
	sem_init(&mutex1, 0, 0);
	sem_init(&mutex2, 0, 1);
	pthread_t t1,t2;
	int numberOfCars;
	printf("So xe muon san xuat: ");
	scanf("%d", &numberOfCars);
	int i;
	for (i = 1; i <= numberOfCars; i++) {
		pthread_create(&t1,NULL,thread1,NULL);
		pthread_create(&t2,NULL,thread2,NULL);
		pthread_join(t1,NULL);
		pthread_join(t2,NULL);	
		printf("\n");
	}
	sem_destroy(&mutex1);
	sem_destroy(&mutex2);
	return 0;
}
