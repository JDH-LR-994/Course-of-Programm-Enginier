/*
** sender.cpp -- sends messages of different types to a message queue
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
    long mtype;     // Тип сообщения
    char mtext[200]; // Текст сообщения
};

int main(void) {
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    // Генерация ключа для очереди сообщений
    if ((key = ftok(".", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Подключение к очереди сообщений
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Enter lines of text, ^D to quit:\n");

    while (fgets(buf.mtext, sizeof(buf.mtext), stdin) != NULL) {
        int len = strlen(buf.mtext);

        // Удаляем символ новой строки, если он есть
        if (buf.mtext[len - 1] == '\n') buf.mtext[len - 1] = '\0';

        // Задаем тип сообщения (1 или 2)
        printf("Enter message type (1 or 2): ");
        scanf("%ld", &buf.mtype);
        getchar(); // Убираем оставшийся символ новой строки

        // Отправляем сообщение в очередь
        if (msgsnd(msqid, &buf, len + 1, 0) == -1) {
            perror("msgsnd");
        }
    }

    // Удаление очереди сообщений
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
