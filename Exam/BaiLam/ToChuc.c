#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include<sys/types.h>
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
int main()
{
	//Option 1: Nhan thong tin gui tu daugia, xuat thong tin bao gom: Ten nguoi gui, cac chi so value nhan dc.

	//Option 2: Nhan thong tin gui tu daugia, xuat thong tin bao gom: Ten nguoi thang dau gia, so tien sau cung cua dau gia.
	key_t key;
	key = ftok("msg.txt",1);

	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	msgrcv(msgid, &message, sizeof(message),1,0);
	
	printf("Nguoi chien thang la %s\n", message.won);
	printf("So tien la %d\n", message.money);
	
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
