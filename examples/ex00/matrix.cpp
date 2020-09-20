//подключаемые файлы
#include <iostream>
#include <math.h>
#include <omp.h>
#include <locale.h>
#include <time.h>
#include <iomanip>  

using namespace std;

int Size;

void mul_matrix(double* pAMatrix, double* pBMatrix, double* pCMatrix, int Size) 
{
	int ThreadNum = 4;//количество потоков
	int GridSize = int(sqrt((double)ThreadNum));//размер сетки 
	int BlockSize = Size / GridSize;//размер блока
//последовательное умножение
	omp_set_num_threads(ThreadNum); // указания количества потоков для OpenMP

#pragma omp parallel //начало параллельного блока
	{
		int ThreadID = omp_get_thread_num(); //получение номера потока
		int RowIndex = ThreadID / GridSize; //номер строки
		int ColIndex = ThreadID % GridSize; //номер столбца
		//подсчет итераций
		for (int iter = 0; iter<GridSize; iter++) 
		{ 
			//процедура умножения (аналогичная последовательной)
			for (int i = RowIndex*BlockSize; i<(RowIndex + 1)*BlockSize; i++) 
				for (int j = ColIndex*BlockSize; j<(ColIndex + 1)*BlockSize; j++)
					for (int k = iter*BlockSize; k<(iter + 1)*BlockSize; k++)
						pCMatrix[i*Size + j] += pAMatrix[i*Size + k] * pBMatrix[k*Size + j];
		}
	} // pragma omp parallel
}

//формирование матриц случайных элементов заданных размеров
void set_random(double ** Matr, int Size) 
{ 
	for (int i=0; i < Size; i++)
		for (int j = 0; j < Size; j++)
			Matr[i][j] = rand()%100; //датчик случайных чисел
}

//инициализация результирующей матрицы - заполнение нулями
void set_zero(double ** Matr, int Size) 
{  
	for (long int i = 0; i<Size; i++)
		for (int j = 0; j < Size; j++)
			Matr[i][j] = 0;// rand() % 100;
}

//преобразования матрицы в одномерный массив (для блочного умножения)
void matrix_to_vector(double **Matr,double *Line, int Size) { 
	int l=0;

	for (int i=0;i<Size;i++)
		for (int j = 0; j < Size; j++) 
		{
			Line[l] = Matr[i][j]; 
			l++;
		}
}

//преобразование одномерного массива в матрицу (для результата обработки)
void vector_to_matrix(double *Line, double **Matr, int Size) { 
	int i = 0;
	int j = 0;
	for (int l = 0; l < Size*Size; l++)
	{
		Matr[i][j] = Line[l];
		j++; 
		if (j == Size) 
		{ 
			j = 0; 
			i++; 
		}
	}
}

int main(void)
{
	system("cls");//очистка экрана
	// setlocale(LC_ALL, "Rus");//использование русских символов

	int sp,vv; //объявление переменных для запросов пользователю
	cout << "Enter a size of square matrix" << endl;//запросы пользователю
	cin >> Size;
	cout << "Select a method" << endl;
	cout << "  sequantal (0)" << endl;
	cout << "  parallel (1)" << endl;
	cout << "  exit (other)" << endl;
	cin >> sp;
	
	if ((sp == 0) || (sp == 1)) 
	{
		cout << "do matrix output (yes - 1, no - 0)?" << endl;		
		cin >> vv;

		//объявление динамических двумерных массивов
		double **MatrixA = new double*[Size];//объявление массива
		double **MatrixB = new double*[Size];
		double **MatrixC = new double*[Size];
		
		//выделение памяти под массивы
		for (int count = 0; count < Size; count++) 
		{
			MatrixA[count] = new double[Size];
			MatrixB[count] = new double[Size];
			MatrixC[count] = new double[Size];
		}

		set_random(MatrixA, Size);//заполнение случайными числами
		set_random(MatrixB, Size);//заполнение случайными числами
		set_zero(MatrixC, Size);  //инициализации матрицы нулями

		//если пользователь выбрал вывод матриц
		if (vv == 1) 
		{ 
			cout << "Matrix A" << endl;
			for (int i = 0; i < Size; i++) 
			{
				for (int j = 0; j < Size; j++)
					cout << setw(2) << MatrixA[i][j] << " ";
				cout << endl;
			}
			
			cout << "Matrix B" << endl;

			for (int i = 0; i < Size; i++) 
			{
				for (int j = 0; j < Size; j++)
					cout << setw(2) << MatrixB[i][j] << " ";
				cout << endl;
			}
			cout << "Matrix C" << endl;
		}

		//объявление одномерных массивов
		double *LA = new double[Size*Size];
		double *LB = new double[Size*Size];
		double *LC = new double[Size*Size];
		
		//преобразование матрицы в одномерный массив
		matrix_to_vector(MatrixA, LA, Size);
		matrix_to_vector(MatrixB, LB, Size);
		matrix_to_vector(MatrixC, LC, Size);
		
		//начало отсчета времени выполнения
		int S = clock();

		if (sp == 0) 
		{
			//последовательное умножение
			for (int i = 0; i < Size; i++) 
				for (int j = 0; j < Size; j++) 
				{
					MatrixC[i][j] = 0;
					for (int k = 0; k < Size; k++) 
						MatrixC[i][j] = MatrixC[i][j] + MatrixA[i][k] * MatrixB[k][j];
				}
		}
		else if (sp == 1) 
			mul_matrix(LA, LB, LC, Size); //вызов функции параллельного умножения			

		//расчёт времени выполнения
		int E = clock() - S; 

		if (vv == 1) 
		{
			vector_to_matrix(LC, MatrixC, Size); //преобразование одномерного массива к двумерному
		
			//вывод полученной матрицы
			for (int i = 0; i < Size; i++) 
			{
				for (int j = 0; j < Size; j++)
					cout << setw(5) << MatrixC[i][j] << " ";
				cout << endl;
			}
		}

		//вывод времени выполнения
		cout << "Execution time " << setw(5) << E << " ms " << endl;
		system("pause");
	}

	return 0;	
}

