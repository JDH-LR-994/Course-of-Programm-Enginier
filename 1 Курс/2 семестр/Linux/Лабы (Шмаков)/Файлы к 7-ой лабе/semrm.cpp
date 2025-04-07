/*
** semrm.cpp -- удаление семафора
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(void) {
    key_t key;  // Ключ для доступа к семафору
    int semid;  // ID семафора

    // 1. Генерация ключа (должен совпадать с ключом в semdemo.cpp)
    if ((key = ftok(".", 'J')) == -1) {  // '.' — текущий каталог, 'J' — проектный идентификатор
        perror("Ошибка ftok");
        exit(1);
    }

    // 2. Получение ID существующего семафора
    // Аргументы:
    //   key — ключ, созданный ftok()
    //   1  — количество семафоров в наборе
    //   0  — флаги (не создаём новый, только получаем существующий)
    if ((semid = semget(key, 1, 0)) == -1) {
        perror("Ошибка semget");
        exit(1);
    }

    // 3. Удаление семафора
    // Аргументы:
    //   semid — ID семафора
    //   0     — номер семафора в наборе (не используется при IPC_RMID)
    //   IPC_RMID — команда удаления
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("Ошибка semctl");
        exit(1);
    }

    printf("Семафор успешно удалён!\n");
    return 0;
}