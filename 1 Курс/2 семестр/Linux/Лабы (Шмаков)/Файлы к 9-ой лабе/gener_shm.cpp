/* The program gener_shma.cpp */
/*
 * Создаёт два сегмента раздельной памяти с помощью shmget()
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
main(void)
{
    key_t key = 15;
    int shmid_1, shmid_2;

    if ((shmid_1 = shmget(key, 1000, 0644 | IPC_CREAT)) == -1)
    {
        /*
        key = 15 — ключ для идентификации сегмента.
        1000 — размер сегмента в байтах.
        0644 — права доступа: владелец может читать и писать, остальные — только читать.
        IPC_CREAT — флаг, который указывает, что сегмент должен быть создан, если он не существует.
        */

        perror("shmget shmid_1");
        exit(1);
    }

    printf("First memory identifire is %d \n", shmid_1);
    if ((shmid_2 = shmget(IPC_PRIVATE, 20, 0644)) == -1)
    {
    /*
    IPC_PRIVATE — ключ, который указывает, что сегмент будет уникальным и не связан с другими процессами.
    20 — размер сегмента в байтах.
    0644 — права доступа.
    */
        perror("shmget shmid_2");
        exit(2);
    }
    printf("Second shared memory identifire is %d \n", shmid_2);
    exit(0);
}
