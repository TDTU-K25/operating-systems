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
	int msg_array[2];
} message;

int factorial(int n) {
	int i;
	int product = 1;
	for (i = 1; i <= n; i++) {
		product *= i;
	}
	return product;
}

int main(int argc, char* argv[]) {
	key_t key;
	// ftok to generate unique key
	key = ftok("msg.txt",1);

	// msgget creates a message queue
	// and returns identifier
	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	msgrcv(msgid, &message, sizeof(message),1,0);
	
	message.msg_array[1] = factorial(message.msg_array[0]);
	message.msg_type = 2;
	msgsnd(msgid, &message, sizeof(message),0);
	
	return 0;
}
