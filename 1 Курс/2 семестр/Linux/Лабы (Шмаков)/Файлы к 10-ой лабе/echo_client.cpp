/*
** Эхо-клиент для UNIX-сокетов
** Подключается к серверу и отправляет сообщения, получая их обратно
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/echo_socket"  // Путь к сокету сервера

int main(void) {
    int s, t, len;
    struct sockaddr_un remote;  // Адрес сервера
    char str[100];  // Буфер для данных

    // 1. Создаём UNIX-сокет
    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect...\n");

    // 2. Настраиваем адрес сервера
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);

    // 3. Подключаемся к серверу
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected.\n");

    // 4. Основной цикл клиента
    while (printf("> "), fgets(str, 100, stdin), !feof(stdin)) {
        // 5. Отправляем сообщение серверу
        if (send(s, str, strlen(str), 0) == -1) {
            perror("send");
            exit(1);
        }

        // 6. Получаем ответ от сервера
        if ((t = recv(s, str, 100, 0)) > 0) {
            str[t] = '\0';  // Добавляем ноль в конец строки
            printf("echo> %s", str);  // Выводим эхо
        } else {
            if (t < 0) perror("recv");
            else printf("Server closed connection\n");
            exit(1);
        }
    }

    close(s);  // Закрываем сокет
    return 0;
}