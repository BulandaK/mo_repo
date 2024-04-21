#include <iostream>
#include <cmath>
using namespace std;
#define TOLX 0.0000001 // tolerancja b�edu
#define TOLF 0.0000001 // tolerancja reziduum
#define ITERACJE 15
double f1(double x, double y, double z) {
	return x * x + y * y + z * z - 2.0;
}

double f2(double x, double y) {
	return x * x + y * y - 1.0;
}

double f3(double x, double y) {
	return x * x - y;
}

double biggest(double tab[]) {
	double max = tab[0];

	for (int i = 1; i < 3; i++) {
		if (tab[i] > max) {
			max = tab[i];
		}
	}
	return abs(max);
}

int main() {
	cout.setf(ios::scientific);
	cout.precision(16);
	double x = 2, y = 1, z = 5, estymator, reziduum, macierz_f[3], macierz_delta[3];
	macierz_f[0] = f1(x, y, z);
	macierz_f[1] = f2(x, y);
	macierz_f[2] = f3(x, y);
	cout << "Poczatkowe\nx: " << x << "\ty: " << y << "\tz: " << z << endl << endl;

	for (int i = 0; i < ITERACJE; i++) {
		macierz_delta[0] = (2.0 * x * x * y + x * x - y * y - 1.0) / (4.0 * x * y + 2.0 * x);
		macierz_delta[1] = (y * y + y - 1.0) / (2.0* y + 1.0);
		macierz_delta[2] = (z * z - 1.0) / (2.0 * z);
		
		x = x - macierz_delta[0];
		y = y - macierz_delta[1];
		z = z - macierz_delta[2];
		
		macierz_f[0] = f1(x, y, z);
		macierz_f[1] = f2(x, y);
		macierz_f[2] = f3(x, y);

		estymator = biggest(macierz_delta);
		reziduum = biggest(macierz_f);
		
		cout << "Iteracja " << i + 1 << endl << "x: " << x << "\ty: " << y << "\tz: " << z << endl;
		cout << "Estymator: " << estymator << endl << "Reziduum: " << reziduum << endl << endl;
		if (reziduum < TOLF && estymator < TOLX) {
			break;
		}
	}
	cout.unsetf(ios::scientific);

	cout << fixed << "x: " << x << endl;
	cout << "y: " << y << endl;
	cout <<  "z: " << z << endl;

	cout << "x^2 + y^2 + z = " << x * x + y * y + z << endl;
	cout << "x^2 + y^2 = " << x * x + y * y << endl;
}