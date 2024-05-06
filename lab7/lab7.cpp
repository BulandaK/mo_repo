#include <iostream>
#include <Windows.h>
#include <math.h>
#define dokladnosc 1.0e-6
#define N 4
const int N_MAX = 100;
using namespace std;
void wypiszMacierz(double A[4][4]);
void wypiszWektor(double c[4]);
double estymator(double x[4], double x_nowe[4]);
double residuum(double A[4][4], double b[4], double x_nowe[4]);
void Jacobiego(double A[4][4], double b[4], double x[4]);
void Gauss_Seidel(double A[4][4], double b[4], double x[4]);
void SOR(double A[4][4], double b[4], double x[4]);
void clear(double vector[4]);
int main()
{
	/*double A[4][4] = new double* [N];
	for (int i = 0; i < N; i++)
		A[i] = new double[N];*/
	double A[N][N] = {
		{100.0,-1.0,2.0,-3.0},
		{1.0,200.0,-4.0,5.0},
		{-2.0,4.0,300.0,-6.0},
		{3.0,-5.0,6.0,400.0}
	};
	double b[N] = {116.0,-226.0,912.0,-1174.0};
	double x[N] = {2.0,2.0, 2.0, 2.0};
	//zapis(A, b, x);
	wypiszMacierz(A);
	cout << endl << endl;
	cout << " Wektor b:" << endl << endl;
	wypiszWektor(b);
	cout << endl;
	cout << " Wektor x:" << endl << endl;
	wypiszWektor(x);
	Jacobiego(A, b, x);
	clear(x);
	Gauss_Seidel(A, b, x);
	clear(x);
	SOR(A, b, x);
	return 0;
}

void clear(double vector[4]) {
	for (int i = 0; i < 4; i++) {
		vector[i] = 2.0;
	}
}

//wypisuje macierz
void wypiszMacierz(double A[4][4])
{
	cout << "Macierz:" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout.width(3);
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}
//wypisuje wektor
void wypiszWektor(double c[4])
{
	for (int i = 0; i < N; i++)
	{
		cout.width(3);
		cout << c[i] << endl;
	}
}
double estymator(double x[4], double x_nowe[4])
{
	x[0] = fabs(x[0] - x_nowe[0]);
	x[1] = fabs(x[1] - x_nowe[1]);
	x[2] = fabs(x[2] - x_nowe[2]);
	x[3] = fabs(x[3] - x_nowe[3]);
	double maximum = x[0];
	for (int z = 0; z < N; z++)
	{
		if (x[z] > maximum)
			maximum = x[z];
	}
	return maximum;
}
double residuum(double A[4][4], double b[4], double x_nowe[4])
{
	double Ax[N];
	Ax[0] = fabs((A[0][0] * x_nowe[0] + A[0][1] * x_nowe[1] + A[0][2] * x_nowe[2] + A[0][3] * x_nowe[3]) - b[0]);
	Ax[1] = fabs((A[1][0] * x_nowe[0] + A[1][1] * x_nowe[1] + A[1][2] * x_nowe[2] + A[1][3] * x_nowe[3]) - b[1]);
	Ax[2] = fabs((A[2][0] * x_nowe[0] + A[2][1] * x_nowe[1] + A[2][2] * x_nowe[2] + A[2][3] * x_nowe[3]) - b[2]);
	Ax[3] = fabs((A[3][0] * x_nowe[0] + A[3][1] * x_nowe[1] + A[3][2] * x_nowe[2] + A[3][3] * x_nowe[3]) - b[3]);
	double maximum = Ax[0];
	for (int z = 0; z < N; z++)
	{
		if (Ax[z] > maximum)
			maximum = Ax[z];
	}
	return maximum;
}
void Jacobiego(double A[4][4], double b[4], double x[4])
{
	double est = 0.0, res = 0.0;
	double* x_ = new double[N];
	double suma = 0.0;
	cout << endl << endl << "metoda Jacobiego" << endl;
	cout << " n | x0 | EST| RES | " << endl << endl;
		for (int iter = 0; iter < N_MAX; iter++)
		{
			for (int i = 0; i < N; i++)
			{
				suma = 0.0;
				for (int j = 0; j < N; j++)
					if (j != i)
						suma += A[i][j] * x[j];
				x_[i] = (1.0 / A[i][i]) * (b[i] - suma);
			}
			est = estymator(x, x_);
			res = residuum(A, b, x_);
			for (int i = 0; i < N; i++)
				x[i] = x_[i];
			cout.width(4);
			cout << iter << "|";
			cout.width(15);
			cout << x_[0] << " ";
			cout.width(15);
			cout << x_[1] << " ";
			cout.width(15);
			cout << x_[2] << " ";
			cout.width(15);
			cout << x_[3] << "|";
			cout.width(15);
			cout << est << "|";
			cout.width(15);
			cout << res << "|" << endl;
			if (est < dokladnosc && res < dokladnosc)
				break;
		}
}
void Gauss_Seidel(double A[4][4], double b[4], double x[4])
{
	double* x_poprz = new double[N];
	double suma = 0.0;
	double est = 0.0, res = 0.0;
	cout << endl << endl << "Gauss_Seidel" << endl;
	cout << " n | x0 | EST | RES |"<<endl<<endl;
	
		for (int iter = 0; iter < N_MAX; iter++)
		{
			for (int i = 0; i < N; i++)
			{
				suma = 0.0;
				for (int j = 0; j < N; j++)
					if (j != i)
						suma += A[i][j] * x[j];
				x_poprz[i] = x[i];
				x[i] = (1.0 / A[i][i]) * (b[i] - suma);
			}
			est = estymator(x_poprz, x);
			res = residuum(A, b, x);
			cout.width(4);
			cout << iter << "|";
			cout.width(15);
			cout << x[0] << " ";
			cout.width(15);
			cout << x[1] << " ";
			cout.width(15);
			cout << x[2] << " ";
			cout.width(15);
			cout << x[3] << "|";
			cout.width(15);
			cout << est << "|";
			cout.width(15);
			cout << res << "|" << endl;
			if (est < dokladnosc && res < dokladnosc)
				break;
		}
}
void SOR(double A[4][4], double b[4], double x[4])
{
	double* x_ = new double[N];
	double* x_poprz = new double[N];
	double suma = 0.0, omega = 0.5;
	double EST = 0.0, RESIDUUM = 0.0;
	cout << endl << endl << "SOR" << endl;
	cout << " n | x0 | EST| RES | " << endl << endl;
		for (int iter = 0; iter < N_MAX; iter++)
		{
			for (int i = 0; i < N; i++)
			{
				suma = 0.0;
				for (int j = 0; j < N; j++)
					if (j != i)
						suma += A[i][j] * x[j]; //(L+U)*X
				x_poprz[i] = x[i];
				x_[i] = (1.0 - omega) * x[i] + (omega / A[i][i]) * (b[i] - suma);
				x[i] = x_[i];
			}
			EST = estymator(x_poprz, x_);
			RESIDUUM = residuum(A, b, x_);
			cout.width(4);
			cout << iter << "|";
			cout.width(15);
			cout << x[0] << " ";
			cout.width(15);
			cout << x[1] << " ";
			cout.width(15);
			cout << x[2] << " ";
			cout.width(15);
			cout << x[3] << "|";
			cout.width(15);
			cout << EST << "|";
			cout.width(15);
			cout << RESIDUUM << "|" << endl;
			if (EST < dokladnosc && RESIDUUM < dokladnosc)
				break;
		}
}