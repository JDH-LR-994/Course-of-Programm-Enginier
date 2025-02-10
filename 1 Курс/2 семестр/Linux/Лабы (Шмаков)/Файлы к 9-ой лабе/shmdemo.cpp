/*
** Создаёт сегмент общей памяти для чтения и записи
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* Размер будет 1024 байта */

int main(int argc, char *argv[]){
	key_t key;
	int shmid;
	char *data;
	int mode;

	if (argc > 2) {
		// Если введено больше двух параметров, то ошибка
		fprintf(stderr, "usage: shmdemo [data_to_write]\n");
		exit(1);
	}

	/* Создаём ключ на основе текущего каталога и символа R*/
	if ((key = ftok(".", 'R')) == -1) {
		perror("ftok");
		exit(1);
	}

	/*Создание или соединения с сегментом общей памяти*/
	if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
		perror("shmget");
		exit(1);
	}

	/* Присоединяем сегмент памяти к процессу */
	data = (char *) shmat(shmid, 0, 0);
	if (data == (char *)(-1)) {
		perror("shmat");
		exit(1);
	}

	/* Чтение или изменение данных из общей памяти */
	if (argc == 2) {
		printf("writing to segment: \"%s\"\n", argv[1]);
		strncpy(data, argv[1], SHM_SIZE); //Для избегания переполнения
	} else 
		printf("segment contains: \"%s\"\n", data); //Вывод содержимого сегмента

	/* Процесс больше не использует нашу общую память */
	if (shmdt(data) == -1) {
		perror("shmdt");
		exit(1);
	}

	return 0;
}
