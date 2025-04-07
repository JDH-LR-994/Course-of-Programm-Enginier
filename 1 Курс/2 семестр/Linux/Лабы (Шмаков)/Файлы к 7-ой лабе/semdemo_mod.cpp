/*
** semdemo_mod.cpp - демонстрация использования семафоров с возможностью многократного выполнения
** Основные изменения:
** 1. Добавлен цикл while для повторного использования семафора
** 2. Добавлены подсказки для пользователя
** 3. Сохранена вся исходная функциональность
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MAX_RETRIES 10  // Максимальное количество попыток ожидания инициализации

// Объединение для работы с semctl
union semun {
    int val;                // Значение для SETVAL
    struct semid_ds *buf;    // Буфер для IPC_STAT, IPC_SET
    ushort *array;          // Массив для GETALL, SETALL
};

// Функция инициализации семафора
int initsem(key_t key, int nsems) {
    int i;
    union semun arg;
    struct semid_ds buf;
    struct sembuf sb;
    int semid;

    // Пытаемся создать новый набор семафоров
    semid = semget(key, nsems, IPC_CREAT | IPC_EXCL | 0666);

    if (semid >= 0) { // Если создали успешно
        sb.sem_op = 1;  // Операция освобождения
        sb.sem_flg = 0;
        arg.val = 1;    // Начальное значение семафора

        printf("Нажмите Enter для инициализации семафора\n");
        getchar();

        // Инициализируем все семафоры в наборе
        for(sb.sem_num = 0; sb.sem_num < nsems; sb.sem_num++) {
            if (semop(semid, &sb, 1) == -1) {
                int e = errno;
                semctl(semid, 0, IPC_RMID); // Удаляем при ошибке
                errno = e;
                return -1;
            }
        }
    }
    else if (errno == EEXIST) { // Если семафор уже существует
        semid = semget(key, nsems, 0); // Получаем ID существующего
        if (semid < 0) return semid;

        // Ждем инициализации другим процессом
        arg.buf = &buf;
        for(i = 0; i < MAX_RETRIES && !ready; i++) {
            semctl(semid, nsems-1, IPC_STAT, arg);
            if (arg.buf->sem_otime != 0) { // Проверяем время последней операции
                ready = 1;
            } else {
                sleep(1); // Ждем 1 секунду перед повторной проверкой
            }
        }
        if (!ready) {
            errno = ETIME;
            return -1;
        }
    }
    else {
        return semid; // Возвращаем ошибку
    }

    return semid;
}

int main(void) {
    printf("Введите 'q' для выхода или любую другую клавишу для продолжения\n");
    
    // Основной цикл программы
    while(getchar() != 'q') { // Продолжаем пока не введено 'q'
        key_t key;
        int semid;
        char u_char = 'J'; // Произвольный символ для генерации ключа
        struct sembuf sb;

        sb.sem_num = 0;    // Работаем с первым семафором в наборе
        sb.sem_op = -1;    // Операция захвата (уменьшение значения)
        sb.sem_flg = SEM_UNDO; // Автоматический откат при завершении

        // Генерируем ключ для семафора
        if ((key = ftok(".", u_char)) == -1) {
            perror("Ошибка ftok");
            exit(1);
        }

        // Получаем/создаем семафор
        if ((semid = initsem(key, 1)) == -1) {
            perror("Ошибка initsem");
            exit(1);
        }

        printf("Нажмите Enter для захвата семафора: ");
        getchar();
        printf("Пытаюсь захватить семафор...\n");

        // Пытаемся захватить семафор
        if (semop(semid, &sb, 1) == -1) {
            perror("Ошибка semop (захват)");
            exit(1);
        }

        printf("Семафор захвачен!\n");
        printf("Нажмите Enter для освобождения семафора: ");
        getchar();

        sb.sem_op = 1; // Операция освобождения (увеличение значения)
        // Пытаемся освободить семафор
        if (semop(semid, &sb, 1) == -1) {
            perror("Ошибка semop (освобождение)");
            exit(1);
        }

        printf("Семафор освобожден\n");
        printf("Введите 'q' для выхода или любую другую клавишу для продолжения\n");
    }
    
    return 0;
}