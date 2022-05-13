#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include <semaphore.h> 
#include <unistd.h> 
#define BUFFER_SIZE 100

// Cau truc data de luu du lieu lay tu file
typedef struct data {
	int value[BUFFER_SIZE]; //cac gia tri cua file
	int length;	// do lon cua mang value
	char filename[BUFFER_SIZE]; // Ten file truyen vao
	long mesg_type; 	//loai message
} data;

//Cau truc mesg_buffer dung thuc hien gui tin nhan den chu dau gia cho option 2
struct mesg_buffer {
	long mesg_type; 	//loai message
	char won[BUFFER_SIZE];	//Luu tru ten cua nguoi thang cuoc dau gia
	int money;	//Luu so tien dau gia cuoi cung
} message;

char name[]="NULL"; //Bien dung chung, de dat ten cua nguoi dau gia qua tung giai doan
int result=0; //Bien dung chung, de dat so tien dau gia qua tung giai doan
sem_t sem; //Bien dung chung, semaphore dung de quan ly truy cap bien dung chung
int flag=0; //Bien dung chung, dung de phat tin hieu khi co 1 luong chay het du lieu

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

//Ham xuly dung de nap cac du lieu o file vao bien thuoc cau truc data
void *xuly(void* Dulieu)
{
	struct data *fi = (struct data*) Dulieu;
	FILE *fp = fopen(fi->filename, "r");
	
	fi->length = countNumberInFile(fi->filename) - 1;
	int i;
	for (i = 0; i < fi->length; i++) {
		fscanf(fp, "%d", &fi->value[i]);
	}
}

void *goixuly (void* Dulieu) 
{
	struct data *fi = (struct data*) Dulieu;
	xuly(&*fi);
}

//Ham daugia dung de thiet lap dau gia giua cac tieu trinh, moi tieu trinh se chi den 1 file du lieu.
void *daugia(void* Dulieu)
{
	struct data *fi = (struct data*) Dulieu;
	
	int i;
	for (i = 0; i < fi->length; i++) {
	
		if (i == fi->length - 1) {
			flag += 1;
		}
		
		sem_wait(&sem);
		//printf("Name = %s entered\n", fi->filename);
		if (fi->value[i] > result) {
			result = fi->value[i];
			strcpy(name, fi->filename);
			//printf("Name = %s, result = %d\n", name,result);
		} 
		else {
			sem_post(&sem);
		}
		
		if (flag != 0) {
			//printf("Name = %s break\n", fi->filename);
			break;
		}
		
		if (fi->value[i+1] > result) {
			//printf("Name = %s exit\n", fi->filename);
			sleep(2);
			sem_post(&sem);
			sleep(5);	
		} 
		
	}
}

int main(int argc, char *argv[])
{
	// Doi so argv la ten cua cac file de truyen du lieu

	//Dua du lieu vao de xu ly
	
	struct data duLieu;
	strcpy(duLieu.filename, argv[1]);
	
	pthread_t temp;
	pthread_create(&temp, NULL, goixuly, &duLieu); 
	pthread_join(temp, NULL); // wait for the termination of a thread
	
	printf("Nguoi dau gia la: %s\n", duLieu.filename);
	int i;
	printf("Du lieu: ");
	for (i = 0; i < duLieu.length; i++) {
		printf("%d ", duLieu.value[i]);
	}
	printf("\n");
	
	//xuat thong tin sau khi file duoc doc vao du lieu	
	
	//Option1: Tao ra message de gui thong tin vua xy ly duoc sang cho ToChuc
	
	//Option 2: Thuc hien dau gia giua cac tieu trinh, moi tieu trinh doc 1 file
	
	pthread_t tid[4];
	struct data listDuLieu[argc - 1];
	sem_init(&sem, 0, 1);
	
	// lay du lieu
	int j;
	for (j = 0; j < argc - 1; j++) {
		strcpy(listDuLieu[j].filename, argv[j+1]);
		pthread_create(&tid[j], NULL, goixuly, &listDuLieu[j]);
	}

	for (j = 0; j < argc - 1; j++) {
		pthread_join(tid[j], NULL);
	}
	
	// dau gia
	for (j = 0; j < argc - 1; j++) {
		pthread_create(&tid[j], NULL, daugia, &listDuLieu[j]);
	}
	
	for (j = 0; j < argc - 1; j++) {
		pthread_join(tid[j], NULL);
	}
	
	//Gui ket qua ve chu dau gia	
	
	key_t key;
	key = ftok("msg.txt",1);

	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	message.mesg_type = 1;
	strcpy(message.won, name);
	message.money = result;
	msgsnd(msgid, &message, sizeof(message),0);
	
	return 0;
}
