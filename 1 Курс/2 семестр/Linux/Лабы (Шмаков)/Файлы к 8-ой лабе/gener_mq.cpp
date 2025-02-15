/* The program gener_mq.cpp */
/* Message queue generation */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 5 // Максимальное количество очередей сообщений

int main(void)
{
    FILE *fin;
    char buffer[PIPE_BUF]; // Буфер для чтения вывода команды
    char u_char = 'A';     // Начальный символ для генерации ключа
    int i, n, mid[MAX];    // mid - массив для хранения идентификаторов очередей сообщений
    key_t key;             // Ключ для создания очереди сообщений

    // Создаем MAX очередей сообщений
    for (i = 0; i < MAX; ++i, ++u_char)
    {
        // Генерация ключа для очереди сообщений
        key = ftok(".", u_char);

        // Создание очереди сообщений с правами доступа 0660 (чтение и запись для владельца и группы)
        if ((mid[i] = msgget(key, IPC_CREAT | 0660)) == -1)
        {
            perror("Queue create"); // Вывод ошибки, если не удалось создать очередь
            exit(1);
        }
    }

    // Запуск команды ipcs для отображения информации о системных IPC объектах
    fin = popen("ipcs", "r");

    // Чтение вывода команды ipcs и вывод его на стандартный вывод
    while ((n = read(fileno(fin), buffer, PIPE_BUF)) > 0)
        write(fileno(stdout), buffer, n);

    // Закрытие потока, связанного с командой ipcs
    pclose(fin);

    // Удаление созданных очередей сообщений
    for (i = 0; i < MAX; ++i)
        msgctl(mid[i], IPC_RMID, NULL); // Удаление очереди сообщений

    exit(0); // Завершение программы
}