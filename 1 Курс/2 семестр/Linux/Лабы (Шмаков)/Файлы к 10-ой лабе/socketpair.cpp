#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUF_SZ 10  // Размер буфера для сообщений

int main(void) {
    int sock[2];      // Массив для хранения пары сокетов
    int cpid, i;      // cpid — PID потомка, i — счётчик
    static char buf[BUF_SZ];  // Буфер для данных

    // Создаём пару связанных сокетов (PF_UNIX — локальные, SOCK_STREAM — TCP-подобные)
    if (socketpair(PF_UNIX, SOCK_STREAM, 0, sock) < 0) {
        perror("Generation error");  // Ошибка создания сокетов
        exit(1);
    }

    // Создаём дочерний процесс
    switch (cpid = (int) fork()) {
        case -1:  // Ошибка fork()
            perror("Bad fork");
            exit(2);

        case 0:  // Код для дочернего процесса
            close(sock[1]);  // Закрываем ненужный сокет
            for (i = 0; i < 10; i += 2) {
                sleep(1);  // Пауза 1 сек
                sprintf(buf, "c:%d\n", i);  // Формируем сообщение
                write(sock[0], buf, sizeof(buf));  // Отправляем родителю
                read(sock[0], buf, BUF_SZ);       // Читаем ответ
                printf("c->%s", buf);  // Выводим ответ родителя
            }
            close(sock[0]);  // Закрываем сокет
            break;

        default:  // Код для родительского процесса
            close(sock[0]);  // Закрываем ненужный сокет
            for (i = 1; i < 10; i += 2) {
                sleep(1);  // Пауза 1 сек
                read(sock[1], buf, BUF_SZ);  // Читаем сообщение от потомка
                printf("p->%s", buf);        // Выводим его
                sprintf(buf, "p: %d\n", i);  // Формируем ответ
                write(sock[1], buf, sizeof(buf));  // Отправляем потомку
            }
            close(sock[1]);  // Закрываем сокет
    }
    return 0;
}