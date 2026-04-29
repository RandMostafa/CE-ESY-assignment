#include <stdio.h>
#include <string.h>

#define SIZE 15 

typedef struct {
    char buffer[SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

void initBuffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

int writeBuffer(CircularBuffer *cb, char data) {
    if (cb->count == SIZE) {
        printf("[!] Overflow: '%c'\n", data);
        return -1;
    }
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % SIZE;
    cb->count++;
    return 0;
}

int readBuffer(CircularBuffer *cb, char *data) {
    if (cb->count == 0) {
        return -1;
    }
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count--;
    return 0;
}

int main() {
    CircularBuffer myBuffer;
    initBuffer(&myBuffer);

    char name[50];
    char suffix[] = " CE-ESY";
    char fullName[100];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    strcpy(fullName, name);
    strcat(fullName, suffix);

    for (int i = 0; i < (int)strlen(fullName); i++) {
        writeBuffer(&myBuffer, fullName[i]);
    }

    printf("\nResult from buffer: ");
    char tempChar;
    while (myBuffer.count > 0) {
        if (readBuffer(&myBuffer, &tempChar) == 0) {
            printf("%c", tempChar);
        }
    }
    printf("\n");

    if (myBuffer.count == 0) {
        printf("Buffer is empty.\n");
    }

    return 0;
}
