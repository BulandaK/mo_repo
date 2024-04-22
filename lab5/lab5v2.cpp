#include <iostream>
#include <iomanip>
#define TOL 1.0e-7
#define N 4
using namespace std;
double matrix_A[N][N] = {
 1.0, -20.0, 30.0, -4.0,
 2.0, -40.0, -6.0, 50.0,
 9.0, -180.0, 11.0, -12.0,
 -16.0, 15.0, -140.0, 13.0
};
double vector_b[N] = { 35.0, 104.0, -366.0, -354.0 };
double matrix_L[N][N];
double vector_x[N];
double vector_y[N];
int vector_indexes[N] = { 0,1,2,3 };

void show_matrix(double matrix[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setw(10) << matrix[i][j];
		}
		cout << endl;
	}

}
void show_matrixU(double matrix[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			
			if (i <= j) {
				cout << setw(10) << matrix[i][j];
			}
			else if (i > j) {
				cout << setw(10) << 0;
			}

		}
		cout << endl;
	}

}
void show_matrixL(double matrix[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j) {
				cout << setw(10) << 1;
			}
			else if (i > j) {
				cout << setw(10) << matrix[i][j];
			}
			else if (i < j) {
				cout << setw(10) << 0;
			}
		
		}
		cout << endl;
	}

}

void print_vector(double vector[N])
{
	for (int i = 0; i < N; i++)
	{
		cout << setw(10) << vector[i];
	}
	cout << endl;
}


void change_row(double A[N][N], double B[N], int vector_idx[N], int idx) {
	double tempRow[N];
	int temp;
	int tempVectorIdx;
	double tempValue = 0;
	for (int j = idx + 1; j < N; j++) {
		if (abs(A[j][idx]) > tempValue)
		{
			temp = j;
			tempValue = abs(A[j][idx]);
		}
	}
	for (int j = 0; j < N; j++)
	{
		tempRow[j] = A[temp][j];
		A[temp][j] = A[idx][j];
		A[idx][j] = tempRow[j];
	}
	tempVectorIdx = vector_idx[idx];
	vector_idx[idx] = vector_idx[temp];
	vector_idx[temp] = tempVectorIdx;
}

void gaussianEliminate(double A[N][N], int indx)
{	
	double temp;
	for (int k = indx + 1; k < N; k++)
	{
		if (A[k][indx] == 0)
		{
			continue;
		}
		else
		{
			temp = A[k][indx] / A[indx][indx];
			for (int j = indx; j < N; j++)
			{
				A[k][j] = A[k][j] - temp * A[indx][j];
			}
			
			A[k][indx] = temp; // z rozkladu LU zapisujemy w tym miejscu macierz L
			
		}
	}
}
void calculate_y(double A[N][N], double y[N], double b[N])
{
	for (int i = 0; i < N; i++)
	{
		double sum = 0.0;
		for (int j = 0; j <= i - 1; j++)
		{
			sum += A[i][j] * y[j];
		}
		y[i] = (b[i] - sum);
	}
}
void calculate_x(double A[N][N], double x[N], double y[N])
{
	for (int i = N - 1; i >= 0; i--)
	{
		double sum = 0.0;
		for (int j = i + 1; j < N; j++)
		{
			sum += A[i][j] * x[j];
		}
		x[i] = (y[i] - sum) / A[i][i];
	}
}

void decompositionLU(double A[N][N],double B[N]) {
	
	
	cout << "A:" << endl;
	show_matrix(A);
	for (int i = 0; i < N; i++)
	{
		if (abs(A[i][i]) < TOL)
		{
			change_row(A, B, vector_indexes , i);
		}
		gaussianEliminate(A, i);
	}
	cout << "Po gaussie:" << endl;
	show_matrix(A);
	cout << "U:" << endl;
	show_matrixU(A);
	cout << "L:" << endl;
	show_matrixL(A);
}
void solve_x_y(double b[N], double A[N][N], double y[N], double x[N]) {


}
void changeVector(double b[N], int vector_idx[N])
{
	int temp;
	double tempVector[N];
	for (int i = 0; i < N; i++)
	{
		tempVector[i] = b[i];
	}
	for (int i = 0; i < N; i++) {
		temp = vector_idx[i];
		b[i] = tempVector[temp];
	}
}
void checkResult(double a[N][N], double x[N], double b[N])
{
	cout << endl << "Checking results " << endl;
	double sum = 0.0;
	double result_ax[N], result_ax_b[N];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			sum += a[i][j] * x[j];
		}
		result_ax[i] = sum;
		sum = 0.0;
	}
	for (int i = 0; i < N; i++) {
		result_ax_b[i] = result_ax[i] - b[i];
	}
	cout << "Ax-b" << endl;
	print_vector(result_ax_b);
}
int main()
{
	decompositionLU( matrix_A, vector_b);
	cout << "b:" << endl;
	print_vector(vector_b);
	changeVector(vector_b,vector_indexes);
	cout << endl;
	cout << "b po zastosowaniu dekompozycji:" << endl;
	print_vector(vector_b);
	cout << "rozwiazanie x i y" << endl;
	calculate_y(matrix_A, vector_y, vector_b);
	cout << "Y:" << endl;
	print_vector(vector_y);
	calculate_x(matrix_A, vector_x, vector_y);
	cout << "X:" << endl;
	print_vector(vector_x);


	double matrix_A_check[N][N] = {
	1.0, -20.0, 30.0, -4.0,
	2.0, -40.0, -6.0, 50.0,
	9.0, -180.0, 11.0, -12.0,
	-16.0, 15.0, -140.0, 13.0
	};
	double vector_b_check[N] = { 35.0, 104.0, -366.0, -354.0 };
	checkResult(matrix_A_check, vector_x, vector_b_check);

	return 0;
}