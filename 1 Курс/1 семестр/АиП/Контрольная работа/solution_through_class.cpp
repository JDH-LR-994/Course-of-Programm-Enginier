#include <iostream>
#include <fstream>

class Matrix{
    private :
    std::size_t rows, cols;
    double** matrix;
    
    public:
    //Конструктор для создания матрицы
    Matrix(std::size_t r, std::size_t c) {
        rows = r;
        cols = c;
        //Выделение памяти для матрицы
        matrix = new double*[rows] {nullptr};
        for (std::size_t i = 0; i < rows; i++) {
            matrix[i] = new double[cols] {0};
            }
    }
    
    // Задание значения элементам матрицы
    void set_matrix(std::ifstream& file){
        for (std::size_t i = 0; i < rows; i++) {
            for (std::size_t j = 0; j < cols; j++) {
                file >> matrix[i][j];
            }
        }
    }
    // Вывести матрицу в файл
    void print_matrix(std::ofstream& file) const {
        for (std::size_t i = 0; i < rows; i++) {
            for (std::size_t j = 0; j < cols; j++) {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }
    }
    // Вывод матрицы в консоль
    void print_matrix() const {
        for (std::size_t i = 0; i < rows; i++) {
            for (std::size_t j = 0; j < cols; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl; 
        }
    }
    //Переопределение оператора умножения
    Matrix operator*(const Matrix& right){
        //Если перемножить нельзя, то кидаем ошибку
        if (cols != right.rows){
            std::cerr << "Error: Matrices are not compatible for multiplication." << std::endl;
            exit(1);
        }
        //Создаём ссылку на матрицу произведения
        Matrix new_matrix(rows, right.cols);
        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < right.cols; ++j) {
                for (std::size_t k = 0; k < cols; ++k) {
                    *(*(new_matrix.matrix + i) + j) += (*(*(matrix + i) + k)) * (*(*(right.matrix + k) + j));
                }
            }
        }
        return new_matrix;
    }
    
    //Деконструктор 
   ~Matrix() {
    for (std::size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];  // Освобождаем память для каждой строки
    }
    delete[] matrix;  // Освобождаем память для массива указателей
}

};

int main(){
    //Файл ввода
    std::ifstream file("input.txt");
    //Файл вывода
    std::ofstream file_out("output.txt");
    // Проверка на существование файла
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    
    int rows_1, cols_1;
    file >> rows_1 >> cols_1;
    Matrix a = Matrix(rows_1, cols_1);
    a.set_matrix(file);
    
    int rows_2, cols_2;
    file >> rows_2 >> cols_2;
    Matrix b = Matrix(rows_2, cols_2);
    b.set_matrix(file);

    std::cout << "Matrix A:" << std::endl;
    a.print_matrix();
    std::cout << "Matrix B:" << std::endl;
    b.print_matrix();
    Matrix c = a * b;
    std::cout << "Matrix C (A * B):" << std::endl;
    c.print_matrix(file_out);
    c.print_matrix();

}