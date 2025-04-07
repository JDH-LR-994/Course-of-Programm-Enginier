#include "local_c_i.h"  // Общий заголовочный файл
main(void) {
    int orig_sock, new_sock;  // Дескрипторы сокетов
    struct sockaddr_in clnt_adr, serv_adr;  // Адреса клиента и сервера

    // Создаём TCP-сокет
    if ((orig_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    // Настраиваем адрес сервера (слушаем все интерфейсы)
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;  // IPv4
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);  // Принимаем соединения с любых IP
    serv_adr.sin_port = htons(PORT);  // Порт (из local_c_i.h)

    // Привязываем сокет к адресу
    if (bind(orig_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) < 0) {
        perror("bind");
        close(orig_sock);
        exit(2);
    }

    // Переводим сокет в режим ожидания (очередь = 5)
    if (listen(orig_sock, 5) < 0) {
        perror("listen");
        exit(3);
    }

    // Основной цикл сервера
    do {
        int clnt_len = sizeof(clnt_adr);
        // Принимаем новое соединение
        if ((new_sock = accept(orig_sock, (struct sockaddr *)&clnt_adr, (socklen_t *)&clnt_len)) < 0) {
            perror("accept");
            close(orig_sock);
            exit(4);
        }

        // Создаём дочерний процесс для обработки клиента
        if (fork() == 0) {  // Код для потомка
            close(orig_sock);  // Закрываем главный сокет
            int len;
            while ((len = read(new_sock, buf, BUFSIZ)) > 0) {
                // Переводим символы в верхний регистр
                for (int i = 0; i < len; ++i) {
                    buf[i] = toupper(buf[i]);
                }
                write(new_sock, buf, len);  // Отправляем обратно
                if (buf[0] == '.') break;   // Завершаем при получении точки
            }
            close(new_sock);  // Закрываем клиентский сокет
            exit(0);  // Завершаем процесс-потомок
        } else {
            close(new_sock);  // Закрываем сокет в родителе
        }
    } while (1);  // Бесконечный цикл
}