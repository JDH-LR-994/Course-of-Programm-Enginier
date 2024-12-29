#include <iostream>
void inputSizeArray(std::size_t &nRows, std::size_t &nColums);
void allocateMemoryArray(int **& dMatrix, std::size_t nRows, std::size_t nColumns);
void inputElementsArray(int ** dMatrix, std::size_t nRows, std::size_t nColumns);
std::size_t calculateNumberOfRowsNoNull(const int* const* dMatrix, std::size_t nRows, std::size_t nColumns);
void outputResult(std::size_t number);
void deleteArrayMemory(int **& dMatrix, std::size_t nRows);

int main(){
    std::size_t nRows {0};
    std::size_t nColumns {0};

    inputSizeArray(nRows, nColumns);

    int** dMatrix = nullptr;

    allocateMemoryArray(dMatrix, nRows, nColumns);

    inputElementsArray(dMatrix, nRows, nColumns);

    std::size_t number = calculateNumberOfRowsNoNull(dMatrix, nRows, nColumns);

    outputResult(number);

    deleteArrayMemory(dMatrix, nRows);

    return 0;
}

void inputSizeArray(std::size_t &nRows, std::size_t &nColums){
    nRows = 3;
    nColums = 2;
}

void allocateMemoryArray(int **& dMatrix, std::size_t nRows, std::size_t nColumns){
    dMatrix = new int*[nRows]{ nullptr }; // инициализация массива указателей нулями 
    for (int i = 0; i < nRows; ++i) {
        dMatrix[i] = new int[nColumns]{0}; // здесь возможно исключение bad_alloc
    }
}

void inputElementsArray(int ** dMatrix, std::size_t nRows, std::size_t nColumns){
     for (std::size_t i = 0; i < nRows; i++){
        for (std::size_t j = 0; j < nColumns; j++){
            dMatrix[i][j] = i * j;
        }
     }
}

std::size_t calculateNumberOfRowsNoNull(const int* const* dMatrix, std::size_t nRows, std::size_t nColumns){
    return 128;
}

void outputResult(std::size_t number){
    std::cout << number << '\n';
}

void deleteArrayMemory(int **& dMatrix, std::size_t nRows){
    if (dMatrix != nullptr) {
        for (int i = 0; i < nRows; ++i) {
            delete[] dMatrix[i]; //Освобождение памяти i-ой строки матрицы
        }
    }
    delete[] dMatrix; //Освобождение памяти массива указателей на строки матрицы
    dMatrix = nullptr;
}