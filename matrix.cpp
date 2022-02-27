#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;
#define SIZE 100

// Считывает матрицу из файла
void readf_matrix(int &size, double matrix[SIZE][SIZE]){
    int i, j;
    string fname;
    
    cin >> fname;
    ifstream fin(fname.c_str());
    
    fin >> size;
    if (size != 0)
        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++)
                fin >> matrix[i][j];
    else{
        cout << "Файлы пусты или хотябы одна из матриц размера 0х0" << endl;
        exit;
    }
}

//умножает матрицу на число (не меняет исходную матрицу)
void multiplication_by_number(const int size, const double factor, double matrix[SIZE][SIZE], double result_matrix[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            result_matrix[i][j] = matrix[i][j] * factor;
}

void copy_matrix(const int size, double matrix[SIZE][SIZE], double result_matrix[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            result_matrix[i][j] = matrix[i][j];
}

//универсальная функция по поиску матрицы произведения двух матриц
void multiplication_of_two_matrix(const int size, double matrix_1[SIZE][SIZE], double matrix_2[SIZE][SIZE], double result_matrix[SIZE][SIZE]){
    int i, j, k;
    double element;
    for (i = 0; i < size; i++){
        for (j  = 0; j < size; j++){
            element = 0;
            for (k = 0; k < size; k++)
                element += matrix_1[i][k] * matrix_2[k][j];
            result_matrix[i][j] = element;
        }
    }
}

//вычисление суммы двух матриц
void calc_sum_two_matrix(const int size, double matrix_1[SIZE][SIZE], double matrix_2[SIZE][SIZE], double result_matrix[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            result_matrix[i][j] = matrix_1[i][j] + matrix_2[i][j];
}

//составляет минор входной матрицы по i-ому j-ому элементу 
void make_minor(const int size, double matrix[SIZE][SIZE], const int str, const int col, double result_matrix[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++){
            if (i < str){
                if (j < col)
                    result_matrix[i][j] = matrix[i][j];
                if (j > col)
                    result_matrix[i][j-1] = matrix[i][j];
            }
            if (i > str){
                if (j < col)
                    result_matrix[i-1][j] = matrix[i][j];
                if (j > col)
                    result_matrix[i-1][j-1] = matrix[i][j];
            }
        }
}

//вычисляет определитель квадратной матрицы
double calc_determ(const int size, double matrix[SIZE][SIZE]){
    double det = 0;
    int degree = 1;
    //Условие выхода из рекурсии
    if(size == 1) 
        return matrix[0][0];
    //Условие выхода из рекурсии
    else if(size == 2) 
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else{
        double temp_matrix[SIZE][SIZE];
        for (int j=  0; j < size; j++){
            make_minor(size, matrix, 0, j, temp_matrix);
            det = det + (degree * matrix[0][j] * calc_determ(size-1, temp_matrix));
            degree = -degree;
        }
    }
    return det;
}

//вычисляет обратную матрицу (проверить отличность определителя от 0 при вызове)
bool calc_inverse_matrix(const int size, double matrix[SIZE][SIZE], double result_matrix[SIZE][SIZE]){
    int i, j;
    if (size == 1)
        if (matrix[0][0] != 0){
            result_matrix[0][0] = 1.0 / matrix[0][0];
            return true;
        }
        else{
            cout << "Не существует обратной матрицы" << endl;
            return false;
        }
    
    double determ = 0, temp_matrix[SIZE][SIZE];
    determ = calc_determ(size, matrix);
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++){
            make_minor(size, matrix, j, i, temp_matrix);
            result_matrix[i][j] = pow(-1, i+j) * calc_determ(size-1, temp_matrix) / determ;
        }
    return true;
}

//вывод матрицы
void output_matrix(const int n, double matrix[SIZE][SIZE]){
    int i, j;
    string fname;
    cout << "Введите название файла для вывода результата: " << endl;
    cin >> fname;
    ofstream fout(fname.c_str());
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            fout << matrix[i][j] << " ";
        fout << endl;
    }
}

//создаёт в файле inputL.txt левую матрицу
void create_L_matrix(const double numbers[]){
    int i, j;
    ofstream fout("inputL.txt");
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
            if (j == 0)
                fout << 1 << " ";
            else
                fout << pow(numbers[i], j % 3 + 1) << " ";
        fout << endl;
    }
}

//создаёт в файле inputR.txt правую матрицу
void create_R_matrix(const double numbers[]){
    int i, j;
    ofstream fout("inputR.txt");
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
            if (j == 0)
                fout << 1 << " ";
            else
                fout << pow(numbers[i], j) << " ";
        fout << endl;
    }
}

//проверяет истинность указанного равенства
bool eqils_check(const double numbers[], double (left_matrix)[3][3], double (right_matrix)[3][3]){
    double factor = 0;
    int i;
    for (i = 0; i < 3; i++)
        factor += numbers[i] * numbers[(i + 1) % 3];
    if (calc_determinant(left_matrix) == factor * calc_determinant(right_matrix))
        return true;
    else
        return false;
}

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