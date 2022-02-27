#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;
#define SIZE 100

void readf_matrix(int &n, double (&matrix)[SIZE][SIZE]){
    int i, j;
    ifstream fin("input.txt");
    fin >> n;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fin >> matrix[i][j];
}

void multiplication_by_number(const int n, const double factor, double (matrix)[SIZE][SIZE], double (&new_matrix)[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            new_matrix[i][j] = matrix[i][j] * factor;
}

void copy_matrix(const int n, double (matrix)[SIZE][SIZE], double (&new_matrix)[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            new_matrix[i][j] = matrix[i][j];
}

double calc_elem_of_matrix_multiplication(const int n, const int str_indx, const int col_indx, double (matrix_1)[SIZE][SIZE], double (matrix_2)[SIZE][SIZE]){
    int i, j;
    double result = 0;
    for (i = 0; i < n; i++)
        result += matrix_1[str_indx][i] * matrix_2[i][col_indx];
    return result;
}

//ищет произведение двух матриц (работает только в паре с функцией calc_elem_of_matrix_multiplication)
void multiplication_of_two_matrix(const int n, double (matrix_1)[SIZE][SIZE], double (matrix_2)[SIZE][SIZE], double (&new_matrix)[SIZE][SIZE]){
    int i, j, k;
    for (i = 0; i < n; i++){
        for (j  = 0; j < n; j++){
            new_matrix[i][j] = calc_elem_of_matrix_multiplication(n, i, j, matrix_1, matrix_2);
        }
    }
}

//универсальная функция по поиску матрицы произведения двух матриц
void univeresal_multiplication_of_two_matrix(const int n, double (matrix_1)[SIZE][SIZE], double (matrix_2)[SIZE][SIZE], double (&new_matrix)[SIZE][SIZE]){
    int i, j, k;
    double element;
    for (i = 0; i < n; i++){
        for (j  = 0; j < n; j++){
            element = 0;
            for (k = 0; k < n; k++)
                element += matrix_1[i][k] * matrix_2[k][j];
            new_matrix[i][j] = element;
        }
    }
}

/*void copy_matrix(const int n, double (matrix)[SIZE][SIZE], double (&new_matrix)[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            new_matrix[i][j] = matrix[i][j];
}*/

//возводит квадратную матрицу в целочисленную степень (показатель будет запрошен на ввод с клавиатуры)
void power_of_matrix(const int n, double (matrix)[SIZE][SIZE], const int power, double (&first_append)[SIZE][SIZE]){
    int i, j, k, l, m, len_str, power;
    double element, temp_matrix[SIZE][SIZE];
    copy_matrix(n, matrix, temp_matrix);
    for (k = 0; k < power - 1; k++){
        for (i = 0; i < n; i++)
            for (j  = 0; j < n; j++){
                element = 0;
                for (len_str = 0; len_str < n; len_str++)
                    element += temp_matrix[i][len_str] * matrix[len_str][j];
                first_append[i][j] = element;
            }
        //проверка конечная ли это степень матрицы
        if (k + 1 != power - 1)
            copy_matrix(n, first_append, temp_matrix);
    }
}

/* //ОНО РАБОТАЕТ возводит квадратную матрицу в целочисленную степень (показатель будет запрошен на ввод с клавиатуры)
void universal_power_of_matrix(const int n, double (matrix)[SIZE][SIZE], double (&first_append)[SIZE][SIZE]){
    int i, j, k, l, m, len_str, power;
    double element, temp_matrix[SIZE][SIZE];
    cout << "Введите степень матрицы в выражении:" << endl;
    cin >> power;
    for (l = 0; l < n; l++)
        for (m = 0; m < n; m++)
            temp_matrix[l][m] = matrix[l][m];
    for (k = 0; k < power - 1; k++){
        for (i = 0; i < n; i++)
            for (j  = 0; j < n; j++){
                element = 0;
                for (len_str = 0; len_str < n; len_str++)
                    element += temp_matrix[i][len_str] * matrix[len_str][j];
                first_append[i][j] = element;
            }
        //проверка конечная ли это степень матрицы
        if (k + 1 != power - 1)
            for (l = 0; l < n; l++)
                for (m = 0; m < n; m++)
                    temp_matrix[l][m] = first_append[l][m];
    }
}*/

//вычисление суммы двух матриц
void calc_sum_two_matrix(const int n, double (matrix_1)[SIZE][SIZE], double (matrix_2)[SIZE][SIZE], double (&result_matrix)[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            result_matrix[i][j] = matrix_1[i][j] + matrix_2[i][j];
}

//вывод матрицы
void output_matrix(const int n, double (matrix)[SIZE][SIZE]){
    int i, j;
    ofstream fout("output.txt");
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            fout << matrix[i][j] << " ";
        fout << endl;
    }
}

int main()
{
    setlocale(LC_ALL,"Rus");
    int i, j, n, power;
    double factor, matrix[SIZE][SIZE];
    double first_append[SIZE][SIZE], second_append[SIZE][SIZE], temp_matrix[SIZE][SIZE];
    readf_matrix(n, matrix);
    cout << "Введите коэффициент умножения матрицы:" << endl;
    cin >> factor;
    
    //блок программы вычисляет f(A) (результат будет занесён в исходную матрицу)
    universal_power_of_matrix(n, matrix,first_append);
    multiplication_by_number(n, factor, matrix, second_append);
    calc_sum_two_matrix(n, first_append, second_append, matrix);
    
    //блок программы вычисляет f(f(A))
    universal_power_of_matrix(n, matrix,first_append);
    multiplication_by_number(n, factor, matrix, second_append);
    calc_sum_two_matrix(n, first_append, second_append, matrix);
    
    //вывод результата в файл output.txt
    output_matrix(n, matrix);
    
    return 0;
}