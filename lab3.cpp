#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define TOLX 1.0e-10 // tolerancja b�edu
#define TOLF 1.0e-10// tolerancja reziduum
#define ITERACJE 20

double funkcja_1(double x) {
	return sin(x / 4.0) * sin(x / 4.0) - x;
}
double funkcja_1_Picarda(double x) {
	return sin(x / 4.0) * sin(x / 4.0);
}
double funkcja_1_Picarda_Pochodna(double x) {
	return cos(x / 4.0) * sin(x / 4.0) / 2.0;
}
double funkcja_1_Pochodna(double x) {
	return (cos(x / 4.0) * sin(x / 4.0) / 2.0) - 1.0;
}
double funkcja_1_Newtona(double x) {
	return x - (funkcja_1(x) / funkcja_1_Pochodna(x));
}

double funkcja_2(double x) {
	return tan(2.0 * x) - x - 1.0;
}
double funkcja_2_Picarda(double x) {
	return tan(2.0 * x) - 1.0;
}
double funkcja_2_Picarda_Pochodna(double x) {
	return 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}
double funkcja_2_Pochodna(double x) {
	return 2.0 / (cos(2.0 * x) * cos(2.0 * x)) - 1;
}
double funkcja_2_Newtona(double x) {
	return x - funkcja_2(x) / funkcja_2_Pochodna(x);
}

void interfejst1() {
	cout << "nr.\t" << "xn\t\t" << "estymator bledu\t\t" << "reziduum rownania" << endl;
}

void interfejst2(int i, double xn, double estymator, double reziduum) {
	cout << i + 1 << fixed << setprecision(10) << ".\t" << xn << "\t" << estymator << "\t\t" << reziduum << endl;
}

void Picarda(double (*f1)(double), double (*f2)(double), double(*f3)(double), double p_pocztk) {
	
	double p_nastepny, estymator, reziduum;
	
	cout << "Picarda" << endl;
	if (abs(f3(p_pocztk)) >= 1) {
		cout << "Metoda jest rozbiezna" << endl;
		return;
	}
	interfejst1();

	for (int i = 0; i < ITERACJE; i++) {
		if (abs(f3(p_pocztk)) >= 1) {
			cout << "Metoda jest rozbiezna" << endl;
			return;
		}
		p_nastepny = f2(p_pocztk);
		estymator = fabs(p_nastepny - p_pocztk);
		reziduum = fabs(f1(p_nastepny));
		
		interfejst2(i, p_nastepny, estymator, reziduum);
		
		if (estymator <= TOLX && reziduum <= TOLF) {
			break;
		}
		p_pocztk = p_nastepny;
	}
	cout << "Obliczone miejsce zerowe: " << p_nastepny << endl << endl << endl;
}

void Bisekcja(double (*f)(double), double a, double b) {
	
	double fa, fb, estymator, reziduum;
	double xn = (a + b) / 2.0;
	double fxn = f(xn);
	cout  << "Bisekcja\nnr.\t" << "a\t\t" << "b\t\t" << "xn\t\t" << "estymator bledu\t\t" << "reziduum rownania" << endl;
	for (int i = 0; i < ITERACJE; i++) {

		fa = f(a);
		fb = f(b);

		cout << i+1 << ".\t"  << fixed << a << "\t" << b;

		if (fa > 0 && fb < 0) {
			if (fxn > 0) {
				a = xn;
			}
			else {
				b = xn;
			}
		}
		else if (fa < 0 && fb > 0) {
			if (fxn > 0) {
				b = xn;
			}
			else {
				a = xn;
			}
		}
		estymator = (b - a) / 2.0;
		reziduum = fabs(fxn);
		cout << "\t"<< xn << "\t" << estymator << "\t\t" << reziduum << endl;

		xn = (a + b) / 2.0;
		fxn = f(xn);
		if (estymator <= TOLX && reziduum <= TOLF) {
			break;
		}
	}
	cout << "Obliczone miejsce zerowe: "<< xn << endl << endl << endl;
}

void Newtona(double (*f1)(double), double (*f2)(double), double xn1) {

	cout << "Newtona" << endl;
	interfejst1();
	double xn2, estymator, residuum;

	for (int i = 0; i < ITERACJE; i++) {
		if (funkcja_1_Pochodna(xn1) != 0) {
			xn2 = f2(xn1);
			estymator = fabs(xn2 - xn1);
			residuum = fabs(f1(xn2));
			interfejst2(i, xn2, estymator, residuum);

			if (estymator <= TOLX && residuum <= TOLF) {
				break;
			}
			xn1 = xn2;
		}
	}
	cout << "Obliczone miejsce zerowe: " << xn2 << endl << endl << endl;
}

void Siecznych(double (*f)(double), double xn1, double xn2) {

	cout << "Siecznych" << endl;
	interfejst1();
	double xn3, estymator, residuum;
	for (int i = 0; i < ITERACJE; i++) {
			xn3 = xn2 - (f(xn2) / ((f(xn2) - f(xn1)) / (xn2 - xn1)));
			estymator = fabs(xn2 - xn1);
			residuum = fabs(f(xn2));
			interfejst2(i, xn3, estymator, residuum);

			if (estymator <= TOLX && residuum <= TOLF) {
				break;
			}
			xn1 = xn2;
			xn2 = xn3;
	}
	cout << "Obliczone miejsce zerowe: " << xn3 << endl << endl << endl;
}

int main()
{
	cout << "Dla f1" << endl;
	Picarda(funkcja_1, funkcja_1_Picarda, funkcja_1_Picarda_Pochodna, 2.0);
	Bisekcja(funkcja_1, -5.0, 2.0);
	Newtona(funkcja_1, funkcja_1_Newtona, -5.0);
	Siecznych(funkcja_1, -1.0, -10.0);

	cout << endl << endl;
	
	cout << "Dla f2" << endl;
	Picarda(funkcja_2, funkcja_2_Picarda, funkcja_2_Picarda_Pochodna, 1.0);
	Bisekcja(funkcja_2, 0.1, 0.5);
	Newtona(funkcja_2, funkcja_2_Newtona, 0.6);
	Siecznych(funkcja_2, 0.6, 0.5);
}