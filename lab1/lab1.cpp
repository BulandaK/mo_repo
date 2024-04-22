#include <iostream>
#include <cfloat>

using namespace std;
void zbadaj_float();
void zbadaj_double();
int main() {
	zbadaj_float();
	cout << endl;
	zbadaj_double();
	return 0;
}
void zbadaj_float() {
	cout << "Float" << endl;
	float x = 1.0f;
	float eps = 1.0f;
	int mantysa = 0;
	while (x + (eps / 2.0f) > x) {
		eps /= 2.0f;
		mantysa++;
	}
	cout << "Mantysa wynosi " << mantysa << endl;
	cout << "Epsilon wynosi " << eps << endl;
	cout << "Rzeczywista wartosc epsylona maszynowego dla typu float wynosi "
		<< FLT_EPSILON << endl;
}
void zbadaj_double() {
	cout << "Double" << endl;
	double x = 1.0;
	double eps = 1.0;
	int mantysa = 0;
	while (x + (eps / 2.0) > x) {
		eps /= 2.0;
		mantysa++;
	}
	cout << "Mantysa wynosi " << mantysa << endl;
	cout << "Epsilon wynosi " << eps << endl;
	cout << "Rzeczywista wartosc epsylona maszynowego dla typu double wynosi "
		<< DBL_EPSILON << endl;
}
