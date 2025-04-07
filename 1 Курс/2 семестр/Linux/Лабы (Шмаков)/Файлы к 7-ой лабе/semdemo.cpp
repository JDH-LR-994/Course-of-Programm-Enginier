#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MAX_RETRIES 10  // Максимальное число попыток ожидания инициализации

// Объединение для semctl()
union semun {
    int val;               // Значение для SETVAL
    struct semid_ds *buf;  // Буфер для IPC_STAT, IPC_SET
    ushort *array;         // Массив для GETALL, SETALL
};

// Инициализация семафора
int initsem(key_t key, int nsems) {
    int semid;
    union semun arg;
    struct sembuf sb = {0, 1, 0};  // Операция освобождения (sem_op = 1)

    // Пытаемся создать новый семафор
    semid = semget(key, nsems, IPC_CREAT | IPC_EXCL | 0666);

    if (semid >= 0) {  // Семафор создан
        arg.val = 1;   // Инициализируем значением 1 (доступен)
        printf("Семафор создан. Нажмите Enter для инициализации.\n");
        getchar();

        // Освобождаем семафоры (устанавливаем sem_otime)
        for (sb.sem_num = 0; sb.sem_num < nsems; sb.sem_num++) {
            if (semop(semid, &sb, 1) == -1) {
                perror("semop");
                semctl(semid, 0, IPC_RMID);  // Удаляем при ошибке
                return -1;
            }
        }
    } 
    else if (errno == EEXIST) {  // Семафор уже существует
        semid = semget(key, nsems, 0);  // Получаем ID существующего
        if (semid < 0) return -1;

        // Ждём инициализации другим процессом (проверяем sem_otime)
        struct semid_ds buf;
        arg.buf = &buf;
        for (int i = 0; i < MAX_RETRIES; i++) {
            semctl(semid, nsems-1, IPC_STAT, arg);
            if (arg.buf->sem_otime != 0) break;  // Готов
            sleep(1);
        }
    } 
    else {
        return -1;  // Ошибка
    }
    return semid;
}

int main() {
    key_t key = ftok(".", 'J');  // Генерируем ключ
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int semid = initsem(key, 1);  // Инициализируем семафор
    if (semid == -1) {
        perror("initsem");
        exit(1);
    }

    struct sembuf sb = {0, -1, SEM_UNDO};  // Захват (sem_op = -1)

    // Захватываем семафор
    printf("Нажмите Enter для захвата семафора...\n");
    getchar();
    printf("Попытка захвата...\n");
    if (semop(semid, &sb, 1) == -1) {
        perror("semop");
        exit(1);
    }
    printf("Семафор захвачен!\n");

    // Освобождаем семафор
    printf("Нажмите Enter для освобождения...\n");
    getchar();
    sb.sem_op = 1;  // Освобождение (sem_op = +1)
    if (semop(semid, &sb, 1) == -1) {
        perror("semop");
        exit(1);
    }
    printf("Семафор освобождён.\n");

    return 0;
}