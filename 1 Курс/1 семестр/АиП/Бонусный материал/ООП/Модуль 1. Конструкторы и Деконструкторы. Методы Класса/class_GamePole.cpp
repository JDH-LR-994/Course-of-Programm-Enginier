#include <iostream>
#include <random>
#include "class_Cell.cpp"

// Создание игрового поля
class GamePole {
    private:
    
    std::size_t width, height; // Ширина и высота игрового поля
    Cell** pole; // Двумерный массив клеток

    // Метод для случайной генерации мин на поле
    void generate_mines() {}

    //Метод для получения информации о количестве мин, вокруг клетки
    std::size_t get_mines_counter(size_t i, size_t j) { }
    
    public:
    // Конструктор класса GamePole
    GamePole(std::size_t w, std::size_t h) {
        width = w; 
        height = h; 
        pole = new Cell*[width]; // Выделяем память для строк
        for (std::size_t i = 0; i < width; i++) {
            pole[i] = new Cell[height]; // Выделяем память для столбцов
        }
        generate_mines(); //Генерируем поле
    }
};

void GamePole::generate_mines() {
        std::random_device rd; // Получаем случайное устройство
        std::mt19937 gen(rd()); // Инициализация генератора случайных чисел
        std::uniform_int_distribution<> dis(0, width * height - 1); // Генерация случайных чисел в диапазоне

        std::size_t mines = 0; // Счетчик для количества размещенных мин
        while (mines < width * height / 5) { // Устанавливаем 1/5 от общего количества клеток как мины
            std::size_t x = dis(gen) % width; // Генерация случайной координаты x
            std::size_t y = dis(gen) % height; // Генерация случайной координаты y
            // Проверяем, не установлена ли уже мина в данной клетке
            if (!this->pole[x][y].is_mine) {
                this->pole[x][y].is_mine = true; // Устанавливаем мину
                mines++; // Увеличиваем счетчик мин
            }
        }
}

std::size_t GamePole::get_mines_counter(size_t i, size_t j) {
    std::size_t count = 0;
    // Проверяем соседние клетки
    for (size_t x = -1; x <= 1; x++) {
        for (size_t y = -1; y <= 1; y++) {
            // Проверяем, не выходит ли за пределы поля
            if (i + x >= 0 && i + x < width && j + y >= 0 && j + y < height) {
                // Проверяем, установлена ли мина в соседней клетке
                if (this->pole[i + x][j + y].is_mine) {
                    count++;
                    }
                }
            }
        return count;
    }
}

