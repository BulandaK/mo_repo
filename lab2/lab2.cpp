#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
double taylor(double val, double exact_result);
int main() {
	ifstream plik;
	ofstream wykres;
	plik.open("dane.txt");
	wykres.open("wykres.txt");
	double logx, x, wyr, wynik;
	/*while (plik.good()) {
		plik >> logx >> x >> wyr;
		double wynik = (1 - exp(-x)) / x;
		double blad_wzgledny = abs((wynik - wyr) / wyr);
		wykres << logx << " \t\t" << log10(blad_wzgledny) << endl;
	}*/

	while (plik.good()) {
		plik >> logx >> x >> wyr;
		if (logx < 0) {
			wynik = taylor(x, wyr);
		}
		else {
			wynik = (1 - exp(-x)) / x;
		}
		double blad_wzgledny = abs((wynik - wyr) / wyr);
		wykres << logx << " \t" << log10(blad_wzgledny) << endl;
	}
}
double taylor(double val, double exact_result) {
	double result = 1.0, previous = 1.0, i = 1.0;
	while ((fabs(result - exact_result) > DBL_EPSILON)) {
		previous *= -val / (i + 1.0);
		result += previous;
		i += 1.0;
		if (previous == 0) {
			break;
		}
	}
	return result;
}
