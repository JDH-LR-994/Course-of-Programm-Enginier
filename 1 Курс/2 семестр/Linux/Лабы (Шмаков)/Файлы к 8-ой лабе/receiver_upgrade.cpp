/*
** receiver.cpp -- receives messages of a specific type from a message queue
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
    long mtype;     // Тип сообщения
    char mtext[200]; // Текст сообщения
};

int main(int argc, char *argv[]) {
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    // Проверка аргументов командной строки
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <message_type>\n", argv[0]);
        exit(1);
    }

    long msgtype = atol(argv[1]); // Тип сообщения, который будет читать этот процесс

    // Генерация ключа для очереди сообщений
    if ((key = ftok(".", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Подключение к очереди сообщений
    if ((msqid = msgget(key, 0644)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Receiver for message type %ld: ready to receive messages.\n", msgtype);

    // Бесконечный цикл для чтения сообщений
    while (1) {
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), msgtype, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Received message of type %ld: \"%s\"\n", buf.mtype, buf.mtext);
    }

    return 0;
}
