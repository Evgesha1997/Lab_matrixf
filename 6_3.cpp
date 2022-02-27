/*Программа решает матричное или скалярное уравнение вида XAB - XC = 2C*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;
#define SIZE 100



//решает матричное уравнение вида XAB - XC = 2C
void solve_matrix_equation(const int size_A, const int size_B, const int size_C, double matrix_A[SIZE][SIZE], double matrix_B[SIZE][SIZE], double matrix_C[SIZE][SIZE]){
    double temp_determ, temp_matrix[SIZE][SIZE];
    
    multiplication_of_two_matrix(size_A, matrix_A, matrix_B, temp_matrix);
    copy_matrix(size_A, temp_matrix, matrix_A);
    multiplication_by_number(size_A, -1, matrix_C, temp_matrix);
    calc_sum_two_matrix(size_A, matrix_A, temp_matrix, matrix_B);
    temp_determ = calc_determ(size_A, matrix_B);
    if (temp_determ != 0){
        multiplication_by_number(size_A, 2, matrix_C, temp_matrix);
        calc_inverse_matrix(size_A, matrix_B, matrix_A);
        multiplication_of_two_matrix(size_A, temp_matrix, matrix_A, matrix_B);
        output_matrix(size_A, matrix_B);
    }
    else{
        cout << "Уравнение решений не имеет" << endl;
        exit;
    }
}

int main()
{
    int size_A = 0, size_B = 0, size_C = 0;
    double matrix_A[SIZE][SIZE], matrix_B[SIZE][SIZE], matrix_C[SIZE][SIZE];
    
    cout << "Введите название файла для считывания матрицы A:" << endl;
    readf_matrix(size_A, matrix_A);
    cout << "Введите название файла для считывания матрицы B:" << endl;
    readf_matrix(size_B, matrix_B);
    cout << "Введите название файла для считывания матрицы C:" << endl;
    readf_matrix(size_C, matrix_C);
    
    // if (size_A == 1 and size_B == 1 and size_C ==1){
    //     solve_scalar_equation(matrix_A[0][0], matrix_B[0][0], matrix_C[0][0]);
    //     return 0;
    // }
    if (size_A == size_B and size_B == size_C)
        solve_matrix_equation(size_A, size_B, size_C, matrix_A, matrix_B, matrix_C);
    else{
        cout << "Уравнение решений не имеет" << endl;
        return 0;
    }
    
    return 0;
} // XAB - XC = 2C
