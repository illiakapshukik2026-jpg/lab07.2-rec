// Lab_7_2_Rec.cpp
// Капшук Ілля Віталійович
// Лабораторна робота № 7.2. 
// Опрацювання багатовимірних масивів рекурентним способом.
// Варіант 6.

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

void CreateRow(int** a, const int rowNo, const int n, const int Low, const int High, int colNo = 0);
void CreateRows(int** a, const int k, const int n, const int Low, const int High, int rowNo = 0);
void PrintRow(int** a, const int rowNo, const int n, int colNo = 0);
void PrintRows(int** a, const int k, const int n, int rowNo = 0);
int RowMax(int** a, const int rowNo, const int n, int colNo = 1, int maxVal = 0);
int MinOfMaxRows(int** a, const int k, const int n, int rowNo = 0, int minOfMax = 0);

int main()
{
    srand((unsigned)time(NULL));

    const int Low = -15;
    const int High = 35;
    const int k = 6; // кількість рядків
    const int n = 5; // кількість стовпчиків

    int** a = new int* [k];
    for (int i = 0; i < k; i++)
        a[i] = new int[n];

    CreateRows(a, k, n, Low, High, 0);
    cout << "Initial Matrix (Recursive):" << endl;
    PrintRows(a, k, n, 0);

    int firstRowMax = RowMax(a, 0, n, 1, a[0][0]);
    int result = MinOfMaxRows(a, k, n, 0, firstRowMax);
    cout << "Min of max elements in rows (Recursive) = " << result << endl;

    for (int i = 0; i < k; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void CreateRow(int** a, const int rowNo, const int n, const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < n - 1)
        CreateRow(a, rowNo, n, Low, High, colNo + 1);
}

void CreateRows(int** a, const int k, const int n, const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, n, Low, High, 0);
    if (rowNo < k - 1)
        CreateRows(a, k, n, Low, High, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int n, int colNo)
{
    cout << setw(6) << a[rowNo][colNo];
    if (colNo < n - 1)
        PrintRow(a, rowNo, n, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int k, const int n, int rowNo)
{
    PrintRow(a, rowNo, n, 0);
    if (rowNo < k - 1)
        PrintRows(a, k, n, rowNo + 1);
    else
        cout << endl;
}

int RowMax(int** a, const int rowNo, const int n, int colNo, int maxVal)
{
    if (colNo == 1 && maxVal == 0)
        maxVal = a[rowNo][0];

    if (a[rowNo][colNo] > maxVal)
        maxVal = a[rowNo][colNo];

    if (colNo < n - 1)
        return RowMax(a, rowNo, n, colNo + 1, maxVal);
    else
        return maxVal;
}

int MinOfMaxRows(int** a, const int k, const int n, int rowNo, int minOfMax)
{
    int currentMax = RowMax(a, rowNo, n, 1, a[rowNo][0]);
    if (rowNo == 0 || currentMax < minOfMax)
        minOfMax = currentMax;

    if (rowNo < k - 1)
        return MinOfMaxRows(a, k, n, rowNo + 1, minOfMax);
    else
        return minOfMax;
}
