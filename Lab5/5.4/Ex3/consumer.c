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
	char msg_text[40];
	int msg_numberOfSetence;
} msg_buffer;

int main(int argc, char* argv[]) {
	key_t key;
	// ftok to generate unique key
	key = ftok("msg.txt",1);

	// msgget creates a message queue
	// and returns identifier
	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	msg_buffer message[10];
	msgrcv(msgid, &message, sizeof(message),1,0);
	
	int i;
	for (i = 0; i < message[0].msg_numberOfSetence ; i++) {
		printf("Item from Producer: %s\n", message[i].msg_text);
	}

	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
