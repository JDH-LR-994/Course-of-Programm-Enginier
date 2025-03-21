#include "pipe_local.h"
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <cstring>  // Для memset и strncmp
#include <unistd.h> // Для read, write, close, unlink

// Глобальная переменная для хранения имени FIFO
struct message msg;

// Обработчик сигнала SIGINT
void sigint_handler(int sig) {
    std::cout << "\nClient is shutting down..." << std::endl;
    unlink(msg.fifo_name);  // Удаляем private FIFO
    exit(0);  // Завершаем программу
}

int main(void) {
    // Устанавливаем обработчик для SIGINT
    signal(SIGINT, sigint_handler);

    // Проверка доступности сервера
    if (access(PUBLIC, F_OK) == -1) {
        std::cerr << "Server is not available. Please start the server first." << std::endl;
        exit(1);
    }

    // Объявляем переменные
    int n, privatefifo, publicfifo;
    static char buffer[PIPE_BUF];

    // Make the name for the private FIFO
    sprintf(msg.fifo_name, "/tmp/fifo%d", getpid());

    // Generate the private FIFO
    if (mknod(msg.fifo_name, S_IFIFO | 0666, 0) < 0) {
        perror(msg.fifo_name);
        exit(1);
    }

    // OPEN the public FIFO for writing
    if ((publicfifo = open(PUBLIC, O_WRONLY)) == -1) {
        perror(PUBLIC);
        exit(2);
    }

    while (1) {  // FOREVER
        write(fileno(stdout), "\ncmd>", 6);
        memset(msg.cmd_line, 0x0, B_SIZ);  // Clear first
        n = read(fileno(stdin), msg.cmd_line, B_SIZ);  // Get cmd
        if (!strncmp("quit", msg.cmd_line, n - 1))
            break;  // EXIT?

        write(publicfifo, (char*)&msg, sizeof(msg));  // to PUBLIC

        // OPEN private FIFO to read returned command output
        if ((privatefifo = open(msg.fifo_name, O_RDONLY)) == -1) {
            perror(msg.fifo_name);
            exit(3);
        }

        // READ private FIFO and display on standard error
        while ((n = read(privatefifo, buffer, PIPE_BUF)) > 0) {
            write(fileno(stderr), buffer, n);
        }
        close(privatefifo);
    }

    close(publicfifo);
    unlink(msg.fifo_name);  // Удаляем private FIFO при нормальном завершении
    return 0;
}