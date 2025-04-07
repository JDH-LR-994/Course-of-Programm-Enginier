#include "local_c_i.h"  // Общий заголовочный файл (определяет PORT, BUFSIZ, buf)

int main(int argc, char *argv[]) {
    int orig_sock;  // Дескриптор сокета
    struct sockaddr_in serv_adr;  // Адрес сервера
    struct hostent *host;  // Информация о хосте

    // Проверка аргументов (ожидается имя сервера)
    if (argc != 2) {
        fprintf(stderr, "usage: %s server\n", argv[0]);
        exit(1);
    }

    // Получаем информацию о сервере по имени (например, "localhost")
    host = gethostbyname(argv[1]);
    if (host == NULL) {
        perror("gethostbyname");
        exit(2);
    }

    // Настраиваем адрес сервера
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;  // IPv4
    memcpy(&serv_adr.sin_addr, host->h_addr, host->h_length);  // Копируем IP
    serv_adr.sin_port = htons(PORT);  // Порт (определён в local_c_i.h)

    // Создаём TCP-сокет
    if ((orig_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(3);
    }

    // Подключаемся к серверу
    if (connect(orig_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) < 0) {
        perror("connect");
        exit(4);
    }

    // Основной цикл: читаем ввод пользователя -> отправляем серверу -> получаем ответ
    do {
        write(fileno(stdout), "> ", 3);  // Вывод приглашения "> "
        if ((len = read(fileno(stdin), buf, BUFSIZ)) > 0) {  // Чтение ввода
            write(orig_sock, buf, len);  // Отправка серверу
            if ((len = read(orig_sock, buf, len)) > 0) {  // Чтение ответа
                write(fileno(stdout), buf, len);  // Вывод ответа
            }
        }
    } while (buf[0] != '.');  // Завершаем при вводе точки

    close(orig_sock);  // Закрываем сокет
    exit(0);
}