#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1023  // Размер каждого сегмента разделяемой памяти

int main() {
    int shmid1, shmid2, shmid3;  // Идентификаторы сегментов разделяемой памяти
    char *shm1, *shm2, *shm3;    // Указатели на разделяемую память

    // Создание первого сегмента разделяемой памяти
    if ((shmid1 = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget fail for shmid1");
        exit(1);
    }

    // Создание второго сегмента разделяемой памяти
    if ((shmid2 = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget fail for shmid2");
        exit(1);
    }

    // Создание третьего сегмента разделяемой памяти
    if ((shmid3 = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget fail for shmid3");
        exit(1);
    }

    // Подключение первого сегмента к адресному пространству процесса
    if ((shm1 = (char *)shmat(shmid1, 0, 0)) == (char *)-1) {
        perror("shmat fail for shm1");
        exit(2);
    }

    // Подключение второго сегмента к адресному пространству процесса
    if ((shm2 = (char *)shmat(shmid2, 0, 0)) == (char *)-1) {
        perror("shmat fail for shm2");
        exit(2);
    }

    // Подключение третьего сегмента к адресному пространству процесса
    if ((shm3 = (char *)shmat(shmid3, 0, 0)) == (char *)-1) {
        perror("shmat fail for shm3");
        exit(2);
    }

    // Вывод адресов, по которым были подключены сегменты
    printf("Segment 1 attached at address: %p\n", shm1);
    printf("Segment 2 attached at address: %p\n", shm2);
    printf("Segment 3 attached at address: %p\n", shm3);

    // Проверка, размещены ли сегменты в последовательных участках памяти
    if (shm2 == shm1 + SHM_SIZE && shm3 == shm2 + SHM_SIZE) {
        printf("Segments are placed consecutively in memory.\n");
    } else {
        printf("Segments are NOT placed consecutively in memory.\n");
    }

    // Попытка доступа к 1024-му байту каждого сегмента
    printf("\nAttempting to access the 1024th byte of each segment:\n");

    // Попытка доступа к 1024-му байту первого сегмента
    printf("Accessing 1024th byte of segment 1: ");
    shm1[1023] = 'A';  // 1023-й байт (последний допустимый)
    printf("Success (last valid byte).\n");

    printf("Accessing 1024th byte of segment 1: ");
    shm1[1024] = 'B';  // 1024-й байт (выход за пределы)
    printf("This should cause a segmentation fault.\n");

    // Отключение сегментов от адресного пространства процесса
    shmdt(shm1);
    shmdt(shm2);
    shmdt(shm3);

    // Удаление сегментов разделяемой памяти
    shmctl(shmid1, IPC_RMID, NULL);
    shmctl(shmid2, IPC_RMID, NULL);
    shmctl(shmid3, IPC_RMID, NULL);

    return 0;
}