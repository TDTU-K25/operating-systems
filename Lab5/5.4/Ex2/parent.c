#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
	long msg_type;
	int msg_array[3];
	char msg_operator;
} message;


int main(int argc, char* argv[]) {
	key_t key;
	key = ftok("msg.txt",1);

	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	message.msg_type = 1;
	message.msg_array[0] = atoi(argv[1]);
	message.msg_array[1] = atoi(argv[2]);
	char tempString[1];
	strcpy(tempString, argv[3]);
	message.msg_operator = tempString[0];
	msgsnd(msgid, &message, sizeof(message),0);
	
	msgrcv(msgid, &message, sizeof(message),2,0);
	printf("%d %c %d = %d\n", message.msg_array[0], message.msg_operator, message.msg_array[1], message.msg_array[2]);
	
	msgctl(msgid, IPC_RMID, NULL);
	return 1;
}
