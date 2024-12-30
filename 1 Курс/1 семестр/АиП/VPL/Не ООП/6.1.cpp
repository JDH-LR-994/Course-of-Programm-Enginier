#include <iostream>
void inputSizeArray(std::size_t& nRows, std::size_t& nColums);
void allocateMemoryArray(std::size_t nRows, std::size_t nColums, int**& dMatrix);
void inputElementsArray(int** dMatrix, std::size_t nRows, std::size_t nColumns);
std::size_t getNumberOfOrderedRows(int**& dMatrix, std::size_t nRows, std::size_t nColumns);
bool isOrderedArray(int*& array, std::size_t count);
int main() {
    std::size_t nRows;
    std::size_t nColums;
    inputSizeArray(nRows, nColums);
    int** dMatrix = nullptr;
    try {
        allocateMemoryArray(nRows, nColums, dMatrix);
    }
    catch (std::bad_alloc) {
        std::cout << "ERROR: Memory not allocated for array";
        exit(1);
    }
    inputElementsArray(dMatrix, nRows, nColums);
    std::cout << "Number of ordered rows = " << getNumberOfOrderedRows(dMatrix, nRows, nColums);
}

void inputSizeArray(std::size_t& nRows, std::size_t& nColums) {
    int Rows;
    std::cin >> Rows;
    if ((!std::cin) || (Rows <= 0)) {
        std::cout << "ERROR: Invalid number of rows specified";
        exit(1);
    }
    nRows = Rows;
    int Colums;
    std::cin >> Colums;
    if ((!std::cin) || (Colums <= 0)) {
        std::cout << "ERROR: Invalid number of columns specified";
        exit(1);
    }
    nColums = Colums;
}
void allocateMemoryArray(std::size_t nRows, std::size_t nColumns, int**& dMatrix) {
    dMatrix = new int* [nRows] { nullptr };
    for (std::size_t i = 0; i < nRows; i++) {
        dMatrix[i] = new int[nColumns] {0};
    }
}
void inputElementsArray(int** dMatrix, std::size_t nRows, std::size_t nColumns) {
    std::size_t totalElements = 0;
    std::size_t countElements = nRows * nColumns;
    for (std::size_t i = 0; i < nRows; i++) {
        for (std::size_t j = 0; j < nColumns; j++) {
            //std::cout << "stroke " << i + 1 << " number " << j + 1 << '\n';
            int value;
            std::cin >> value;
            totalElements++;
            if ((!std::cin) && (not(std::cin.eof()))) {
                std::cout << "ERROR: Invalid matrix element";
                exit(1);
            }
            if ((totalElements != countElements) && (std::cin.eof())) {
                std::cout << "ERROR: Not enough matrix elements ";
                exit(1);
            }
            dMatrix[i][j] = value;
        }
    }
}
std::size_t getNumberOfOrderedRows(int**& dMatrix, std::size_t nRows, std::size_t nColumns) {
    std::size_t count = 0;
    for (std::size_t i = 0; i < nRows; i++) {
        if (isOrderedArray(dMatrix[i], nColumns)) count++;
    }
    return count; 
}
bool isOrderedArray(int*& array, std::size_t count) {
    bool order = true;
    for (std::size_t i = 1; i < count; i++) {
        if (array[i] <= array[i - 1]) {
            order = false;
        }
    }
    return order;
}