#include <iostream>
#include <stdexcept>
#include "tmatrix.h"
#include <locale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "========== 1. ТЕСТИРОВАНИЕ ВЕКТОРА ==========\n";
    TDynamicVector<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    TDynamicVector<int> v2(3);
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    cout << "Вектор v1: " << v1 << endl;
    cout << "Вектор v2: " << v2 << endl;

    cout << "v1 + v2 = " << v1 + v2 << endl;
    cout << "v1 - v2 = " << v1 - v2 << endl;
    cout << "v1 * 2  = " << v1 * 2 << endl;
    cout << "Скалярное произведение v1 * v2 = " << (v1 * v2) << endl;

    try {
        cout << "Пытаемся взять v1[5]: ";
        cout << v1[5] << endl;
    }
    catch (const std::out_of_range& e) {
        cout << "Поймано исключение: " << e.what() << endl;
    }

    cout << "\n========== 2. ТЕСТИРОВАНИЕ ТРЕУГОЛЬНОЙ МАТРИЦЫ ==========\n";
    TDynamicMatrix<int> tr1(3);
    
    tr1[0][0] = 1; tr1[0][1] = 2; tr1[0][2] = 3;
    tr1[1][0] = 4; tr1[1][1] = 5;
    tr1[2][0] = 6;

    TDynamicMatrix<int> tr2(3);
    tr2[0][0] = 1; tr2[0][1] = 0; tr2[0][2] = 0;
    tr2[1][0] = 1; tr2[1][1] = 0;
    tr2[2][0] = 1;

    cout << "Треугольная матрица tr1 (выводятся только существующие элементы):\n" << tr1;
    cout << "Треугольная матрица tr2 (единичная):\n" << tr2;

    cout << "tr1 + tr2:\n" << (tr1 + tr2);
    cout << "tr1 * 10:\n" << (tr1 * 10);

    
    cout << "tr1 * tr2 (матричное умножение):\n" << (tr1 * tr2);

    
    TDynamicVector<int> v3(3);
    v3[0] = 1; v3[1] = 1; v3[2] = 1;
    cout << "tr1 * v3 (где v3 это {1, 1, 1}):\n" << (tr1 * v3);

    
    try {
        cout << "\nПытаемся прочитать tr1[1][2] (это нижний треугольник, его нет в памяти):\n";
        cout << tr1[1][2] << endl;
    }
    catch (const std::out_of_range& e) {
        cout << "Поймано исключение: " << e.what() << " (как и ожидалось, ведь там 0)" << endl;
    }

    return 0;
}