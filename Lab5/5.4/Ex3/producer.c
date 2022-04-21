#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
typedef struct {
	long msg_type;
	char msg_text[40];
	int msg_numberOfSetence;
} msg_buffer;


int main(int argc, char* argv[]) {
	key_t key;
	key = ftok("msg.txt",1);
	
	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	msg_buffer message[10];
	message[0].msg_type = 1;
	int count = 0;
	int i;
	for (i = 0; i < 10; i++) {
			printf("Enter setence: ");
			gets(message[i].msg_text);
			count++;
			if (strcmp(message[i].msg_text, "Exit") == 0) {
				count--;
				break;
			} 	
	}
	message[0].msg_numberOfSetence = count; 
	msgsnd(msgid, &message, sizeof(message),0);
	return 1;
}
