#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <ctime>
#include <atomic>

// Атомарный флаг для корректного завершения
std::atomic<bool> should_exit(false);

// Обработчик сигналов
void signal_handler(int sig) {
    if (sig == SIGUSR1) {
        std::cout << "Process " << getpid() << " received SIGUSR1" << std::endl;
    } else if (sig == SIGUSR2) {
        std::cout << "Process " << getpid() << " received SIGUSR2" << std::endl;
    } else if (sig == SIGINT || sig == SIGTERM) {
        std::cout << "Process " << getpid() << " received signal to exit (" << sig << ")" << std::endl;
        should_exit.store(true);  // Устанавливаем флаг для завершения
    }
}

// Функция для отправки случайного сигнала
void send_random_signal(pid_t target_pid, int signal) {
    kill(target_pid, signal);  // Отправка сигнала целевому процессу
    std::cout << "Process " << getpid() << " sent signal " << (signal == SIGUSR1 ? "SIGUSR1" : "SIGUSR2") << " to process " << target_pid << std::endl;
}

int main() {
    // Инициализация генератора случайных чисел
    srand(time(nullptr));

    // Настройка обработчика сигналов с использованием sigaction
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_RESTART;  // Восстанавливаем системные вызовы после обработки сигнала
    sigemptyset(&sa.sa_mask);

    // Устанавливаем обработчики для SIGUSR1, SIGUSR2, SIGINT и SIGTERM
    if (sigaction(SIGUSR1, &sa, nullptr) == -1) {
        std::cerr << "Failed to set up SIGUSR1 handler!" << std::endl;
        return 1;
    }
    if (sigaction(SIGUSR2, &sa, nullptr) == -1) {
        std::cerr << "Failed to set up SIGUSR2 handler!" << std::endl;
        return 1;
    }
    if (sigaction(SIGINT, &sa, nullptr) == -1) {
        std::cerr << "Failed to set up SIGINT handler!" << std::endl;
        return 1;
    }
    if (sigaction(SIGTERM, &sa, nullptr) == -1) {
        std::cerr << "Failed to set up SIGTERM handler!" << std::endl;
        return 1;
    }

    // Создание процесса-потомка
    pid_t pid = fork();

    if (pid == 0) {
        // Код для процесса-потомка
        std::cout << "Child process started with PID: " << getpid() << std::endl;
        pid_t parent_pid = getppid();  // Получаем PID родительского процесса

        while (!should_exit.load()) {
            sleep(2);  // Задержка 2 секунды
            send_random_signal(parent_pid, SIGUSR1);  // Отправка сигнала родителю
        }

        std::cout << "Child process exiting..." << std::endl;
    } else if (pid > 0) {
        // Код для процесса-родителя
        std::cout << "Parent process started with PID: " << getpid() << std::endl;

        while (!should_exit.load()) {
            sleep(2);  // Задержка 2 секунды
            send_random_signal(pid, SIGUSR2);  // Отправка сигнала потомку
        }

        std::cout << "Parent process exiting..." << std::endl;
    } else {
        // Ошибка при создании процесса
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    return 0;
}