#include <iostream>
#include <iomanip>
#define N 6
using namespace std;

double D[N] = { 10.0, 20.0, 30.0, 30.0, 20.0, 10.0 };
double U[N - 1] = { 0.5, 0.25, 1.0 / 6.0, 0.125, 0.1 };
double L[N - 1] = { 1.0 / 3.0, 0.2, 1.0 / 7.0, 1.0 / 9.0, 1.0 / 11.0 };
double R[N] = { 31.0, 165.0 / 4.0, 917.0 / 30.0, 851.0 / 28.0, 3637.0 / 90.0, 332.0 / 11.0 };
double x[N], eta[N], r[N];


void printLDUMatrix() {
    cout << "Macierz LDU:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                cout << setw(10) << D[i];  // Diagonalne elementy z D
            }
            else if (i == j - 1) {
                cout << setw(10) << U[j - 1];  // Górna diagonalna z U
            }
            else if (j == i - 1) {
                cout << setw(10) << L[i - 1];  // Dolna diagonalna z L
            }
            else {
                cout << setw(10) << 0.0;  // Wypełnienie zerami pozostałej części macierzy
            }
        }
        cout << endl;
    }
}
void thomasEta() {
    eta[0] = D[0];
    for (int i = 1; i < N; i++) {
        eta[i] = D[i] - L[i - 1] * U[i - 1] / eta[i - 1];
    }
}

void thomasR() {
    r[0] = R[0];
    for (int i = 1; i < N; i++) {
        r[i] = R[i] - L[i - 1] * r[i - 1] / eta[i - 1];
    }
}

void thomasX() {
    x[N - 1] = r[N - 1] / eta[N - 1];
    for (int i = N - 2; i >= 0; i--) {
        x[i] = (r[i] - U[i] * x[i + 1]) / eta[i];
    }
}
void printVector(double vec[N]) {
    cout << endl;
    for (int j = 0; j < N; j++) {
        cout << setw(15);
        cout << vec[j];
    }
    cout << endl;
}
void sprawdzenie(double l[N - 1], double d[N], double u[N - 1], double x[N], double b[N]) {
    double sum_l = 0, sum_d = 0, sum_u = 0;
    double wynik_ax[N], wynik_ax_b[N];
    for (int j = 0; j < N; j++) {
        sum_d = d[j] * x[j];
        if (j > 0) {
            sum_l = l[j - 1] * x[j - 1];
        }
        if (j < N - 1) {
            sum_u = u[j] * x[j + 1];
        }
        wynik_ax[j] = sum_l + sum_d + sum_u;
        sum_l = sum_u = 0;
    }
    cout << "A*x = ";
    printVector(wynik_ax);
    for (int i = 0; i < N; i++) {
        wynik_ax_b[i] = wynik_ax[i] - b[i];
    }
    cout << "Ax-b = ";
    printVector(wynik_ax_b);
}

int main() {

    printLDUMatrix();
    cout << "Vector b";
    printVector(R);

    thomasEta();
    thomasR();
    thomasX();

    cout << "Vector eta";
    printVector(eta);
    cout << "Vector r";
    printVector(r);
    cout << "Vector x";
    printVector(x);

    sprawdzenie(L, D, U, x, R);
}
