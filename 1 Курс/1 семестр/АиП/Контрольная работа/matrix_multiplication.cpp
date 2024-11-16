#include <iostream>
#include <fstream>

// Функция для размещения матрицы в динамической памяти
int** allocateMatrix(std::size_t rows, std::size_t cols) {
    int** matrix = new int* [rows];
    for (std::size_t i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

// Функция для ввода матрицы из файла
void inputMatrix(std::ifstream& file, int** matrix, std::size_t rows, std::size_t cols) {
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            file >> matrix[i][j];
        }
    }
}

// Функция для вывода матрицы в файл
void outputMatrix(std::ofstream& file, int** matrix, std::size_t rows, std::size_t cols, const std::string& name) {
    file << name << ":\n";
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            file << matrix[i][j] << " ";
        }
        file << "\n";
    }
    file << "\n";
}

// Функция для перемножения матриц
int** MatrixMultiplication(int** A, int** B, std::size_t rowsA, std::size_t colsA, std::size_t colsB) {
    int** result = allocateMatrix(rowsA, colsB);
    for (std::size_t i = 0; i < rowsA; ++i) {
        for (std::size_t j = 0; j < colsB; ++j) {
            *(*(result + i) + j) = 0; // Инициализация элемента результирующей матрицы
            for (std::size_t k = 0; k < colsA; ++k) {
                *(*(result + i) + j) += *(*(A + i) + k) * *(*(B + k) + j);
            }
        }
    }
    return result;
}

// Функция для удаления матрицы из динамической памяти
void deleteMatrix(int** matrix, std::size_t rows) {
    for (std::size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Ошибка открытия файла input.txt\n";
        return 1;
    }

    std::size_t rowsA, colsA, rowsB, colsB;

    inputFile >> rowsA >> colsA;
    int** A = allocateMatrix(rowsA, colsA);
    inputMatrix(inputFile, A, rowsA, colsA);

    inputFile >> rowsB >> colsB;
    int** B = allocateMatrix(rowsB, colsB);
    inputMatrix(inputFile, B, rowsB, colsB);

    inputFile.close();

    if (colsA != rowsB) {
        outputFile << "Невозможно перемножить матрицы.\n";
        deleteMatrix(A, rowsA);
        deleteMatrix(B, rowsB);
        return 1;
    }

    int** C = MatrixMultiplication(A, B, rowsA, colsA, colsB);

    //Матрица A
    outputMatrix(outputFile, A, rowsA, colsA, "Матрица A");

    //Матрица B
    outputMatrix(outputFile, B, rowsB, colsB, "Матрица B");

    //Матрицс C
    outputMatrix(outputFile, C, rowsA, colsB, "Результат");

    outputFile.close();

    deleteMatrix(A, rowsA);
    deleteMatrix(B, rowsB);
    deleteMatrix(C, rowsA);

    return 0;
}