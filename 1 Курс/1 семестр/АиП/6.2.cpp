#include <iostream>
#include <stdexcept>
#include <limits>

void inputSizeArray(std::size_t& nRows, std::size_t& nColums);
void allocateMemoryArray(std::size_t nRows, std::size_t nColums, int**& ddMatrix);
void inputElementsArray(int** ddMatrix, std::size_t nRows, std::size_t nColums);
double arithmeticMeanOfPositive(int* nRows, int nColums) {
    int count = 0;
    int sum = 0;
    for (int i = 0; i < nColums; ++i) {
        if (nRows[i] > 0) {
            sum += nRows[i];
            count++;
        }
    }
    if (count == 0) {
        throw std::invalid_argument("ERROR: It is impossible to construct a vector");
    }
    return static_cast<double>(sum) / count;
}
void arithmeticMeansOfPositive(int** dMatrix, int nRows, int nColums, double* vector) {
    for (int i = 0; i < nRows; ++i) {
        try {
            vector[i] = arithmeticMeanOfPositive(dMatrix[i], nColums);
        }
        catch (const std::invalid_argument& e) {
            throw;
        }
    }
}
int main() {
    std::size_t nRows, nColums;
    inputSizeArray(nRows, nColums);
    int** dMatrix = nullptr;
    try {
        allocateMemoryArray(nRows, nColums,dMatrix);
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "ERROR: Memory not allocated for array" << std::endl;
        exit(1);
    }
    inputElementsArray(dMatrix,nRows, nColums);
    double* vector = nullptr;
    try {
        vector = new double[nRows];
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "ERROR: Memory not allocated for array" << std::endl;
        for (int i = 0; i <nRows; ++i) {
            delete[] dMatrix[i];
        }
        delete[] dMatrix;
        exit(1);
    }
    try {
        arithmeticMeansOfPositive(dMatrix,nRows, nColums, vector);
        std::cout << "Vector of arithmetic means = ";
        for (int i = 0; i <nRows; ++i) {
            std::cout << vector[i] << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        delete[] vector;
        for (int i = 0; i <nRows; ++i) {
            delete[] dMatrix[i];
        }
        delete[] dMatrix;
        exit(1);
    }
    delete[] vector;
    for (int i = 0; i <nRows; ++i) {
        delete[] dMatrix[i];
    }
    delete[] dMatrix;
}

void inputSizeArray(std::size_t& nRows, std::size_t& nColums) {
    int nRows;
    std::cin >> nRows;
    if ((!std::cin) || (nRows <= 0)) {
        std::cout << "ERROR: Invalid number of rows specified";
        exit(1);
    }
    nRows =nRows;
    int Colums;
    std::cin >> Colums;
    if ((!std::cin) || (Colums <= 0)) {
        std::cout << "ERROR: Invalid number of columns specified";
        exit(1);
    }
    nColums = Colums;
}
void allocateMemoryArray(std::size_t nRows, std::size_t nColums, int**& dMatrix) {
    dMatrix = new int* [nRows] { nullptr };
    for (std::size_t i = 0; i < nRows; i++) {
        dMatrix[i] = new int[nColums] {0};
    }
}
void inputElementsArray(int** dMatrix, std::size_t nRows, std::size_t nColums) {
    std::size_t totalElements = 0;
    std::size_t countElements = nRows * nColums;
    for (std::size_t i = 0; i < nRows; i++) {
        for (std::size_t j = 0; j < nColums; j++) {
            int value;
            std::cin >> value;
            totalElements++;
            if ((!std::cin) && (not(std::cin.eof()))) {
                std::cout << "ERROR: Invalid dMatrix element";
                exit(1);
            }
            if ((totalElements != countElements) && (std::cin.eof())) {
                std::cout << "ERROR: Not enough dMatrix elements ";
                exit(1);
            }
            dMatrix[i][j] = value;
        }
    }
}