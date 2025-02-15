/* The program gener_sem.cpp */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

main(void)
{
    int sem1, sem2, sem3;  // Переменные для хранения идентификаторов семафоров
    char u_char = 'S';  // Символ для генерации ключа
    key_t ipc_key;  // Ключ для создания семафора

    // Генерация ключа с использованием текущего каталога и символа 'S'
    ipc_key = ftok(".", u_char);

    // Создание первого набора семафоров с правами доступа 0666 (чтение и запись для всех)
    if ((sem1 = semget(ipc_key, 3, IPC_CREAT | 0666)) == -1) {
        perror("semget: IPC_CREAT | 0666");  // Вывод ошибки, если не удалось создать семафор
    }
    printf("sem1 identifier is %d\n", sem1);  // Вывод идентификатора первого семафора

    // Попытка создания второго набора семафоров с тем же ключом, но с флагом IPC_EXCL
    // IPC_EXCL гарантирует, что семафор будет создан только если он не существует
    if ((sem2 = semget(ipc_key, 3, IPC_CREAT | IPC_EXCL | 0666)) == -1) {
        perror("semget: IPC_CREATE | IPC_EXCL | 0666");  // Вывод ошибки, если семафор уже существует
    }
    printf("sem2 identifier is %d\n", sem2);  // Вывод идентификатора второго семафора

    // Создание третьего набора семафоров с уникальным ключом IPC_PRIVATE
    // IPC_PRIVATE создает семафор, который может быть использован только текущим процессом
    if ((sem3 = semget(IPC_PRIVATE, 3, 0600)) == -1) {
        perror("semget: IPC_PRIVATE");  // Вывод ошибки, если не удалось создать семафор
    }
    printf("sem3 identifier is %d\n", sem3);  // Вывод идентификатора третьего семафора

    exit(0);  // Завершение программы
}