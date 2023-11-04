#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>      
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 1024

// Define a structure for the message
struct message {
    long mtype; // Message type (must be > 0)
    char mtext[MAX_MESSAGE_SIZE];
};

int main() {
    int msgid;
    key_t key;
    struct message msg;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Sender Process
    if (fork() == 0) {
        // Child process (sender)

        // Prepare the message
        msg.mtype = 1; // Message type (must be > 0)
        strcpy(msg.mtext, "Hello, Receiver!");

        // Send the message to the queue
        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("Sender: Sent message to the queue\n");
        exit(0);
    }


    else {

        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Receiver: Received message: %s\n", msg.mtext);

        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(1);
        }
    }

    return 0;
}

