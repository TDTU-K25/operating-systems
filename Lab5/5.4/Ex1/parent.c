#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
struct msg_buffer {
	long msg_type;
	int msg_array[2];
} message;


int main(int argc, char* argv[]) {
	if (atoi(argv[1]) < 3) {
		printf("Doi so sai.\n");
		return 0;
	}
	
	key_t key;
	// ftok to generate unique key
	key = ftok("msg.txt",1);

	// msgget creates a message queue
	// and returns identifier
	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	message.msg_type = 1;
	message.msg_array[0] = atoi(argv[1]);
	msgsnd(msgid, &message, sizeof(message),0);
	
	msgrcv(msgid, &message, sizeof(message),2,0);
	printf("%d! = %d\n", message.msg_array[0], message.msg_array[1]);
	
	msgctl(msgid, IPC_RMID, NULL);
	return 1;
}
