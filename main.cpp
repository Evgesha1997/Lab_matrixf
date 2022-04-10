#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include "matrix.h"
using namespace std;
#define SIZE 100

//прибавляет к матрице число (не меняет исходную матрицу)
void addition_by_number(const int size, const double factor, double matrix[SIZE][SIZE], double result_matrix[SIZE][SIZE]) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i == j)
                result_matrix[i][j] = matrix[i][j] + factor;
            else
                result_matrix[i][j] = matrix[i][j];
}

// Удаление памяти, занимаемой матрицей
void clear(const int size, double matrix[SIZE][SIZE]) {
    for (int i = 0; i < size; i++)
        delete[] matrix[i];
    delete[] matrix;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int size_A, size_B;
    double matrix_A[SIZE][SIZE] = { 0 };
    cout << "Введите название файла, в котором хранится матрица А:\n";
    readf_matrix(size_A, matrix_A);
    if (size_A == 0) {
        cout << "Вычисления не могут быть произведены";
        clear(SIZE, matrix_A);
        return 0;
    }
    double matrix_B[SIZE][SIZE] = { 0 }, new_A[SIZE][SIZE] = { 0 }, new_B[SIZE][SIZE] = { 0 },
    first_element[SIZE][SIZE] = { 0 }, second_element[SIZE][SIZE] = { 0 }, result_matrix[SIZE][SIZE] = { 0 };
    cout << "\nВведите название файла, в котором хранится матрица В:\n";
    readf_matrix(size_B, matrix_B);
    cout << "\n";

    // Задание 1
    // Вычисление f(A)'
    addition_by_number(size_A, 3, matrix_A, new_A);
    multiplication_of_two_matrix(size_A, new_A, new_A, first_element);
    multiplication_of_two_matrix(size_A, new_A, first_element, second_element);
    multiplication_by_number(size_A, -3, new_A, first_element);
    calc_sum_two_matrix(size_A, second_element, first_element, result_matrix);
    output_matrix(size_A, result_matrix);
    copy_matrix(size_A, result_matrix, new_A);
    cout << "\n";
    if (size_A != size_B)
        cout << "Невозможно получить матрицу В', т.к. изначальные матрицы разного размера";
    else {
        // Вычисление f(B)'
        multiplication_of_two_matrix(size_A, matrix_A, matrix_B, new_B);
        multiplication_of_two_matrix(size_B, new_B, new_B, first_element);
        multiplication_of_two_matrix(size_B, first_element, new_B, second_element);
        multiplication_by_number(size_B, -3, new_B, first_element);
        calc_sum_two_matrix(size_B, second_element, first_element, result_matrix);
        output_matrix(size_B, result_matrix);
        copy_matrix(size_B, result_matrix, new_B);
    }

    // Задание 2
    double left_matrix[SIZE][SIZE] = { 0 }, right_matrix[SIZE][SIZE] = { 0 }, numbers[3];
    int size_L, size_R;
    cout << "\nВведите числа a, b, c для уравнения:\n";
    cin >> numbers[0] >> numbers[1] >> numbers[2];
    create_L_matrix(numbers);
    create_R_matrix(numbers);
    cout << "Введите название файла, в котором хранится матрица L (inputL.txt):\n";
    readf_matrix(size_L, left_matrix);
    cout << "Введите название файла, в котором хранится матрица R (inputR.txt):\n";
    readf_matrix(size_R, right_matrix);
    if (eqils_check(numbers, left_matrix, right_matrix))
        cout << "\nРавенство верно";
    else
        cout << "\nРавенство неверно";

    // Задание 3
    if (size_A != size_B) 
        cout << "\nНевозможно решить уравнение, т.к. нет матрицы В'";
    else {
        int size_C;
        double matrix_C[SIZE][SIZE];
        cout << "\nВведите название файла, в котором хранится матрица C:" << endl;
        readf_matrix(size_C, matrix_C);
        cout << "\n";
        if (size_A == size_B  &&  size_B == size_C)
            solve_matrix_equation(size_A, size_B, size_C, new_A, new_B, matrix_C);
        else 
            cout << "\nУравнение решений не имеет" << endl;
        clear(SIZE, matrix_C);
    }

    clear(SIZE, matrix_A);
    clear(SIZE, matrix_B);
    clear(SIZE, new_A);
    clear(SIZE, new_A);
    clear(SIZE, first_element);
    clear(SIZE, second_element);
    clear(SIZE, result_matrix);
    clear(SIZE, left_matrix);
    clear(SIZE, right_matrix);
    delete[] numbers;
    return 0;
}