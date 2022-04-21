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

int caculator(int a, int b, char operator) {
	switch(operator) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
	}
}

int main(int argc, char* argv[]) {
	key_t key;
	key = ftok("msg.txt",1);

	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	msgrcv(msgid, &message, sizeof(message),1,0);
	
	message.msg_array[2] = caculator(message.msg_array[0], message.msg_array[1], message.msg_operator);
	message.msg_type = 2;
	msgsnd(msgid, &message, sizeof(message),0);
	
	return 0;
}
