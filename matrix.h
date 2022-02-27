#ifndef _MATRIX_
#define _MATRIX_

void readf_matrix(int &size, double matrix[SIZE][SIZE]);

//умножает матрицу на число (не мен€ет исходную матрицу)
void multiplication_by_number(const int size, const double factor, double matrix[SIZE][SIZE], double result_matrix[SIZE][SIZE]);

void copy_matrix(const int size, double matrix[SIZE][SIZE], double result_matrix[SIZE][SIZE]);

//функци€ по поиску матрицы произведени€ двух матриц
void multiplication_of_two_matrix(const int size, double matrix_1[SIZE][SIZE], double matrix_2[SIZE][SIZE], double result_matrix[SIZE][SIZE]);

//вычисление суммы двух матриц
void calc_sum_two_matrix(const int size, double matrix_1[SIZE][SIZE], double matrix_2[SIZE][SIZE], double result_matrix[SIZE][SIZE]);

//составл€ет минор входной матрицы по i-ому j-ому элементу 
void make_minor(const int size, double matrix[SIZE][SIZE], const int str, const int col, double result_matrix[SIZE][SIZE]);

//вычисл€ет определитель квадратной матрицы
double calc_determ(const int size, double matrix[SIZE][SIZE]);

//вычисл€ет обратную матрицу (проверить отличность определител€ от 0 при вызове)
bool calc_inverse_matrix(const int size, double matrix[SIZE][SIZE], double result_matrix[SIZE][SIZE]);

//вывод матрицы
void output_matrix(const int n, double matrix[SIZE][SIZE]);

//создаЄт в файле inputL.txt левую матрицу
void create_L_matrix(const double numbers[]);

//создаЄт в файле inputR.txt правую матрицу
void create_R_matrix(const double numbers[]);

//провер€ет истинность указанного равенства
bool eqils_check(const double numbers[], double (left_matrix)[3][3], double (right_matrix)[3][3]);

//решает матричное уравнение вида XAB - XC = 2C
void solve_matrix_equation(const int size_A, const int size_B, const int size_C, double matrix_A[SIZE][SIZE], double matrix_B[SIZE][SIZE], double matrix_C[SIZE][SIZE]);

#endif //_MATRIX_