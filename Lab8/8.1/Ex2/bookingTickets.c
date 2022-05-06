#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int numberOfTicketsAvaiable;

struct file {
	char fileName[20];	
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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

void* thr1(void* arg) {
	struct file *fi = (struct file*) arg;
	FILE *fp = fopen(fi->fileName, "w");
	printf("Enter the number of tickets: ");
	scanf("%d", &numberOfTicketsAvaiable);
	fprintf(fp, "%d", numberOfTicketsAvaiable);
}

void* thr2(void* arg) {
	struct file *fi = (struct file*) arg;
	
	FILE *fp = fopen(fi->fileName, "r");
	
	pthread_mutex_lock(&mutex);
	int i;
	for (i = 0; i < countNumberInFile(fi->fileName) - 1; i++) {		
		printf("So ve hang hien co: %d\n", numberOfTicketsAvaiable);
		int numberOfTicketAgentWantTobuy;
		fscanf(fp, "%d", &numberOfTicketAgentWantTobuy);
		printf("So ve dai ly 1 muon mua: %d\n", numberOfTicketAgentWantTobuy);
		if (numberOfTicketsAvaiable >= numberOfTicketAgentWantTobuy) {
			numberOfTicketsAvaiable -= numberOfTicketAgentWantTobuy;
			printf("So ve hang con lai: %d\n\n", numberOfTicketsAvaiable);
		}
		if (numberOfTicketsAvaiable == 0 || numberOfTicketsAvaiable < numberOfTicketAgentWantTobuy) {
			printf("Het ve\n");
			break;
		}
	}
	pthread_mutex_unlock(&mutex);
	fclose(fp);
}

void* thr3(void* arg) {
	struct file *fi = (struct file*) arg;
	
	FILE *fp = fopen(fi->fileName, "r");
	
	pthread_mutex_lock(&mutex);
	int i;
	for (i = 0; i < countNumberInFile(fi->fileName) - 1; i++) {
		printf("So ve hang hien co: %d\n", numberOfTicketsAvaiable);
		int numberOfTicketAgentWantTobuy;
		fscanf(fp, "%d", &numberOfTicketAgentWantTobuy);
		printf("So ve dai ly 2 muon mua: %d\n", numberOfTicketAgentWantTobuy);		
		if (numberOfTicketsAvaiable >= numberOfTicketAgentWantTobuy) {
			numberOfTicketsAvaiable -= numberOfTicketAgentWantTobuy;
			printf("So ve hang con lai: %d\n\n", numberOfTicketsAvaiable);
		}
		if (numberOfTicketsAvaiable == 0 || numberOfTicketsAvaiable < numberOfTicketAgentWantTobuy) {
			printf("Het ve\n");
			break;
		}
	}
	pthread_mutex_unlock(&mutex);
	fclose(fp);
}

int main(int argc, char* argv) {
	pthread_t tid[3];

	struct file airplaneCompany;
	strcpy(airplaneCompany.fileName, "sove.txt");
	
	struct file agent1;
	strcpy(agent1.fileName, "daily1.txt");
	
	struct file agent2;
	strcpy(agent2.fileName, "daily2.txt");

	pthread_create(&tid[0], NULL, thr1, (void*) &airplaneCompany);
	pthread_join(tid[0], NULL);


	pthread_create(&tid[1], NULL, thr2, (void*) &agent1);
	pthread_create(&tid[2], NULL, thr3, (void*) &agent2);

	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	
	return 0;
}
