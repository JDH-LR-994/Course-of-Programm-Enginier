/*
** Эхо-сервер для UNIX-сокетов
** Принимает сообщения от клиента и отправляет их обратно (эхо)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/echo_socket"  // Путь к файлу сокета

int main(void) {
    int s, s2, t, len;
    struct sockaddr_un local, remote;  // Структуры адресов
    char str[100];  // Буфер для данных

    // 1. Создаём UNIX-сокет (SOCK_STREAM = TCP-подобный)
    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // 2. Настраиваем адрес сервера
    local.sun_family = AF_UNIX;  // Семейство = UNIX-сокет
    strcpy(local.sun_path, SOCK_PATH);  // Путь к сокету
    unlink(local.sun_path);  // Удаляем старый сокет (если есть)
    len = strlen(local.sun_path) + sizeof(local.sun_family);

    // 3. Привязываем сокет к адресу
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }

    // 4. Переводим сокет в режим ожидания (очередь = 5)
    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }

    // 5. Основной цикл сервера
    for(;;) {
        printf("Waiting for a connection...\n");
        t = sizeof(remote);

        // 6. Принимаем новое соединение
        if ((s2 = accept(s, (struct sockaddr *)&remote, (socklen_t *)&t)) == -1) {
            perror("accept");
            exit(1);
        }

        printf("Connected.\n");

        // 7. Читаем данные от клиента и отправляем обратно
        int done = 0;
        do {
            int n = recv(s2, str, 100, 0);  // Чтение данных
            if (n <= 0) {
                if (n < 0) perror("recv");
                done = 1;  // Клиент отключился
            }

            if (!done) {
                if (send(s2, str, n, 0) < 0) {  // Отправка эха
                    perror("send");
                    done = 1;
                }
            }
        } while (!done);

        close(s2);  // Закрываем соединение
    }

    close(s);  // Закрываем сокет (недостижимо в данном коде)
    return 0;
}