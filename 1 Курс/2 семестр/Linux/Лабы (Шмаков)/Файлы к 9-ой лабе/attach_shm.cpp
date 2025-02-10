#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 30 // Размер разделяемой памяти

// Внешние переменные, которые указывают на конец различных сегментов памяти программы
extern int etext, edata, end;
/* Создание, подключение и манипуляция раздельной памятью */
main(void){ 
	pid_t pid; // Переменная для идентификатора процесса
	int shmid; // Идентификатор сегмента разделяемой памяти
	char c, *shm, *s;
	// shm - указатель на разделяемую память
	// s - временный указатель

	// Создание сегмента разделяемой памяти
	if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0){
		perror("shmget fail");
		exit(1);}
	// Подключение сегмента разделяемой памяьт к процессу
	if ((shm = (char *)shmat(shmid, 0, 0)) == (char *)-1){
		perror("shmat : parent ");
		exit(2);}
	// Вывод адресов различных сегментов памяти
	printf("Addresses in parent\n\n");
	printf("shared mem: %10p\n program text (etext): %10p\n initialized data (edata): %10p\n uninitialized data (end): %10p\n\n", shm, &etext, &edata, &end);
	s = shm;					 /* s теперь указатель на начало раздельной памяти */
	for (c = 'A'; c <= 'Z'; ++c) /* Заполнение раздельной памяти символами от A до Z */
		*s++ = c;
	*s = 0; 
	printf("In parent before fork, memory is : %s \n", shm); //Выводим содержимое

	
	pid = fork(); // Создаём дочерний процесс
	switch (pid){
	case -1:
		perror("fork ");  // Процесс не удалось создать
		exit(3);
	default:	  // Родительский процесс
		sleep(3); /* Позволяем дочернему завершить работу */
		printf("\nIn parent after fork, memory is  : %s\n", shm); // Вывод содержимого после работы дочернего процесса
		printf("Parent removing shared memory\n");
		shmdt(shm);									   // Отключение раздельной памяти
		shmctl(shmid, IPC_RMID, (struct shmid_ds *)0); // Удаление сегмента раздельной памяти
		exit(0);
	case 0: // Дочерний процесс
		printf("In child after fork, memory is : %s \n", shm); // Вывод содержимого в дочернем процессе
		for (; *shm; ++shm) /*  Переводим строку в нижний регистр   */
			*shm += 32;
		shmdt(shm); // Отключаем раздельную память
		exit(0);
	}
}
