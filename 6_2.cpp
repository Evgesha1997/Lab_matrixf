#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

//создаёт в файле inputL.txt левую матрицу
void create_LR_matrix(const double numbers[]){
    int i, j;
    ofstream fout("input.txt");
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
            if (j == 0)
                fout << 1 << " ";
            else
                fout << pow(numbers[i], j % 3 + 1) << " ";
        fout << endl;
    }
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
            if (j == 0)
                fout << 1 << " ";
            else
                fout << pow(numbers[i], j) << " ";
        fout << endl;
    }
}

//создаёт в файле inputR.txt правую матрицу
/*void create_R_matrix(const double numbers[]){
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
}*/

void readf_matrixs(const int size, double left_matrix[3][3], double right_matrix[3][3]){
    int i, j;
    ifstream fin("inputL.txt");
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            fin >> left_matrix[i][j];
    ifstream fin_r("input.txt");
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            fin >> right_matrix[i][j];
}

//вычисляет определитель квадратной матрицы 3x3
double calc_determinant(double matrix[3][3]){
    int i, j;
    double result = 0;
    result += matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[1][0] * matrix[2][1] * matrix[0][2] + matrix[0][1] * matrix[1][2] * matrix[2][0];
    result -= matrix[2][0] * matrix[1][1] * matrix[0][2] + matrix[1][0] * matrix[0][1] * matrix[2][2] + matrix[2][1] * matrix[1][2] * matrix[0][0];
    return result;
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

int main()
{
    double left_matrix[3][3] = {0}, right_matrix[3][3] = {0}, numbers[3];
    cin >> numbers[0] >> numbers[1] >> numbers[2];
    create_LR_matrix(numbers);
    readf_matrixs(3, left_matrix, right_matrix);
    if (eqils_check(numbers, left_matrix, right_matrix))
        cout << "Равенство верно";
    else
        cout << "Равенство неверно";
    
    return 0;
}
